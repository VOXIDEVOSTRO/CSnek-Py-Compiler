#define _POSIX_C_SOURCE 200809L/*for strndup*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <PyTokens.h>
#include <Main.h>

/**
 * Emit a token
 */
void
Emit(PyTokenList *Output, PyTokenCat TokenClass, const char *Lexeme, int EmitLine, int EmitColumn)
{
    if (Output->Count >= LimToken) {
#ifdef PyDebugCompiler
        printf("DEBUG: token list full at Count=%d\n", Output->Count);
#endif
        return;
    }

#ifdef PyDebugCompiler
    printf("DEBUG: Emit start: '%s' type=%d line=%d col=%d\n", Lexeme ? Lexeme : "<null>", TokenClass, EmitLine, EmitColumn);
#endif

    Output->Tokens[Output->Count].Type   = TokenClass;
    Output->Tokens[Output->Count].Value  = strdup(Lexeme);
    Output->Tokens[Output->Count].Line   = EmitLine;
    Output->Tokens[Output->Count].Column = EmitColumn;

#ifdef PyDebugCompiler
    printf("DEBUG: Emit stored at index %d\n", Output->Count);
#endif

    Output->Count++;

#ifdef PyDebugCompiler
    printf("DEBUG: Emit Exited, Count=%d\n", Output->Count);
#endif
}

/**
 * Tokenize to lexemes
 */
void
LexOutFile(FILE *File, PyTokenList *Output)
{
#ifdef PyDebugCompiler
    fprintf(stderr, "DEBUG: LexOutFile entered\n");
#endif

    char LineBuffer[LimLineBuffer];
    int Line = 0;
	int IndentStack[LimLineBuffer];
	int IndentTop = 0;
	IndentStack[0] = 0;  /* base */


    while (fgets(LineBuffer, sizeof(LineBuffer), File))
	{
        Line++;
#ifdef PyDebugCompiler
        fprintf(stderr, "DEBUG: line %d read: %s", Line, LineBuffer);
#endif

		/* measure indentation at start of this line */
    	int Indent = 0;
    	int FIndex = 0;
    	while (LineBuffer[FIndex] == ' ' || LineBuffer[FIndex] == '\t')
		{
    	    Indent += (LineBuffer[FIndex] == ' ') ? 1 : TabSpace;
    	    FIndex++;
    	}
		/* Indent */
    	if (Indent > IndentStack[IndentTop])
		{
    	    IndentTop++;
    	    IndentStack[IndentTop] = Indent;
    	    Emit(Output, INDENT, "<INDENT>", Line, 1);
    	}
		/* Dedent */
		else
		{
    	    while (Indent < IndentStack[IndentTop])
			{
    	        IndentTop--;
    	        Emit(Output, DEDENT, "<DEDENT>", Line, 1);
    	    }
    	}

        int Index = 0;
        int Column = 1;

        while (LineBuffer[Index] != '\0') {
            unsigned char Character = (unsigned char)LineBuffer[Index];

#ifdef PyDebugCompiler
            printf("DEBUG: scan line=%d index=%d col=%d char='%c' (0x%02X)\n",
                   Line, Index, Column,
                   (Character >= 32 && Character < 127) ? Character : '.',
                   Character);
#endif

            /* whitespace */
            if (Character == ' ' || Character == '\t' || Character == '\r')
			{
#ifdef PyDebugCompiler
                printf("DEBUG: whitespace skip\n");
#endif
                Index++; Column++;
                continue;
            }

            /* newline */
            if (Character == '\n')
			{
#ifdef PyDebugCompiler
                printf("DEBUG: newline emit\n");
#endif
                Emit(Output, NEWLINE, "\\n", Line, Column);
                Index++; Column++;
                continue;
            }

			/* comments */
            if (Character == '#')
			{
#ifdef PyDebugCompiler
                printf("DEBUG: comment start at line=%d col=%d\n", Line, Column);
#endif
                while (LineBuffer[Index] != '\0' && LineBuffer[Index] != '\n')
				{
                    Index++; Column++;
                }
                continue;
            }

            /* float or integer */
            if (isdigit(Character))
			{
                int Start = Index;
#ifdef PyDebugCompiler
                printf("DEBUG: number/float start at index=%d\n", Start);
#endif
                while (LineBuffer[Index] != '\0' &&
      			(isdigit((unsigned char)LineBuffer[Index]) || LineBuffer[Index] == '_'))
				{
                    Index++; Column++;
                }

				/* Floats */
				int isFloat = 0;
				if (LineBuffer[Index] == '.' && isdigit((unsigned char)LineBuffer[Index+1]))
				{
				    isFloat = 1;
				    Index++; Column++; /* consume '.' */
				    while (LineBuffer[Index] != '\0' &&
				    (isdigit((unsigned char)LineBuffer[Index]) || LineBuffer[Index] == '_'))
				    {
				        Index++; Column++;
				    }
				}

				/* Exponenta */
				if (LineBuffer[Index] == 'e' || LineBuffer[Index] == 'E')
				{
				    int expIndex = Index + 1;
				    if (LineBuffer[expIndex] == '+' || LineBuffer[expIndex] == '-')
					{
				        expIndex++;
				    }
				    if (isdigit((unsigned char)LineBuffer[expIndex]))
					{
				        isFloat = 1;
				        Index++; Column++; /* consume 'e' or 'E' */
				        if (LineBuffer[Index] == '+' || LineBuffer[Index] == '-')
						{
				            Index++; Column++;
				        }
				        while (isdigit((unsigned char)LineBuffer[Index]) || LineBuffer[Index] == '_')
						{
				            Index++; Column++;
				        }
				    }
				}

                int Length = Index - Start;
                if (Length > 0)
				{
                    char *Lexeme = strndup(&LineBuffer[Start], Length);
#ifdef PyDebugCompiler
                    printf("DEBUG: %s lexeme='%s'\n", isFloat ? "float" : "integer", Lexeme ? Lexeme : "<alloc-failed>");
#endif
                    if (Lexeme)
					{
                        Emit(Output, isFloat ? FLOAT : INTEGER, Lexeme, Line, Column - Length);
                        free(Lexeme);
                    }
                }
                continue;
            }

            /* string literals with optional prefixes */
			if (Character == '"' || Character == '\'' ||
			    ((tolower(Character) == 'f' || tolower(Character) == 'r' ||
			      tolower(Character) == 'b' || tolower(Character) == 'u') &&
			     (LineBuffer[Index+1] == '"' || LineBuffer[Index+1] == '\'' || strchr("fFbBrRuU", LineBuffer[Index+1]))))
			{
				
			    int Start = Index;
			    PyTokenCat tokenType = STRING;
				
			    /* detect prefix(es) */
			    if (tolower(Character) == 'f' || tolower(Character) == 'r' ||
			        tolower(Character) == 'b' || tolower(Character) == 'u')
				{
			        char FirstPrefix = tolower(LineBuffer[Index]);
			        char SecondPrefix = tolower(LineBuffer[Index+1]);

					/* prefix list*/
					
			        if 		((FirstPrefix == 'f' && (SecondPrefix == '"' || SecondPrefix == '\''))) 	tokenType = FSTRING;
			        else if ((FirstPrefix == 'r' && (SecondPrefix == '"' || SecondPrefix == '\''))) 	tokenType = RSTRING;
			        else if ((FirstPrefix == 'b' && (SecondPrefix == '"' || SecondPrefix == '\''))) 	tokenType = BYTES;
			        else if ((FirstPrefix == 'u' && (SecondPrefix == '"' || SecondPrefix == '\''))) 	tokenType = USTRING;
					
			        /* Combos */
			        if ((FirstPrefix == 'f' && SecondPrefix == 'r') ||
						(FirstPrefix == 'r' && SecondPrefix == 'f'))
					{
			            tokenType = FRSTRING;
			            Index++; Column++; /* consume both letters */
			        }
			        if ((FirstPrefix == 'r' && SecondPrefix == 'b') ||
						(FirstPrefix == 'b' && SecondPrefix == 'r'))
					{
			            tokenType = RBSTRING;
			            Index++; Column++;
			        }
				
			        Index++; Column++; /* consume prefix */
			        Character = LineBuffer[Index];
			    }
			
			    /* now Character is the opening quote */
			    char quote = Character;
			    Index++; Column++;
			
			    /* check for Triple quotes (Does Python support that?)*/
			    int Triple = 0;
			    if (LineBuffer[Index] == quote &&
				    LineBuffer[Index+1] == quote)
				{
				    Triple = 1;
				    Index += 2;
					Column += 2;
				}
			
			    /* consume until closing quote(s) */
			    while (LineBuffer[Index] != '\0')
				{
			        if (!Triple && LineBuffer[Index] == quote) break;
			        if (Triple && LineBuffer[Index] == quote &&
			            LineBuffer[Index+1] == quote &&
			            LineBuffer[Index+2] == quote)
					{
			            Index += 3; Column += 3;
			            goto Done;
			        }
			        if (LineBuffer[Index] == '\\' && LineBuffer[Index+1] != '\0')
					{
			            Index += 2; Column += 2;
			        } 
					else
					{
			            if (LineBuffer[Index] == '\n' && !Triple) break;
			            Index++; Column++;
			        }
			    }
			
			    if (!Triple && LineBuffer[Index] == quote)
				{
			        Index++; Column++;
			    }
			
			Done:
			    {
			        int Length = Index - Start;
			        if (Length > 0)
					{
			            char *Lexeme = strndup(&LineBuffer[Start], Length);
#ifdef PyDebugCompiler
			            printf("DEBUG: %s lexeme='%s'\n",
			                   (tokenType == STRING ? "STRING" :
			                    tokenType == FSTRING ? "FSTRING" :
			                    tokenType == RSTRING ? "RSTRING" :
			                    tokenType == FRSTRING ? "FRSTRING" :
			                    tokenType == BYTES ? "BYTES" :
			                    tokenType == RBSTRING ? "RBSTRING" :
			                    tokenType == USTRING ? "USTRING" : "UNKNOWN"),
			                   Lexeme ? Lexeme : "<alloc-failed>");
#endif
			            if (Lexeme)
						{
			                Emit(Output, tokenType, Lexeme, Line, Column - Length);
			                free(Lexeme);
			            }
			        }
			    }
			    continue;
			}

			/* identifier or keyword */
            if (isalpha(Character) || Character == '_')
			{
                int Start = Index;
#ifdef PyDebugCompiler
                printf("DEBUG: identifier start at index=%d\n", Start);
#endif
                while (LineBuffer[Index] != '\0' && (isalnum((unsigned char)LineBuffer[Index]) || LineBuffer[Index] == '_'))
				{
                    Index++; Column++;
                }
                int Length = Index - Start;
#ifdef PyDebugCompiler
                printf("DEBUG: identifier length=%d\n", Length);
#endif
                if (Length > 0)
				{
                    char *Lexeme = strndup(&LineBuffer[Start], Length);
#ifdef PyDebugCompiler
                    printf("DEBUG: identifier lexeme='%s'\n", Lexeme ? Lexeme : "<alloc-failed>");
#endif
                    if (Lexeme)
					{
                        Emit(Output, MirrorCheckToken(Lexeme), Lexeme, Line, Column - Length);
                        free(Lexeme);
                    }
                }
                continue;
            }

            /* multi-char operators */
            if (LineBuffer[Index] != '\0' && LineBuffer[Index+1] != '\0')
			{
                if (LineBuffer[Index] == '=' && LineBuffer[Index+1] == '=')
				{
#ifdef PyDebugCompiler
                    printf("DEBUG: match '==' at line=%d col=%d\n", Line, Column);
#endif
                    Emit(Output, EQ, "==", Line, Column); Index += 2; Column += 2; continue;
                }
                if (LineBuffer[Index] == '!' && LineBuffer[Index+1] == '=')
				{
#ifdef PyDebugCompiler
                    printf("DEBUG: match '!=' at line=%d col=%d\n", Line, Column);
#endif
                    Emit(Output, NEQ, "!=", Line, Column); Index += 2; Column += 2; continue;
                }
                if (LineBuffer[Index] == '<' && LineBuffer[Index+1] == '=')
				{
#ifdef PyDebugCompiler
                    printf("DEBUG: match '<=' at line=%d col=%d\n", Line, Column);
#endif
                    Emit(Output, LTE, "<=", Line, Column); Index += 2; Column += 2; continue;
                }
                if (LineBuffer[Index] == '>' && LineBuffer[Index+1] == '=')
				{
#ifdef PyDebugCompiler
                    printf("DEBUG: match '>=' at line=%d col=%d\n", Line, Column);
#endif
                    Emit(Output, GTE, ">=", Line, Column); Index += 2; Column += 2; continue;
                }
                if (LineBuffer[Index] == '-' && LineBuffer[Index+1] == '>')
				{
#ifdef PyDebugCompiler
                    printf("DEBUG: match '->' at line=%d col=%d\n", Line, Column);
#endif
                    Emit(Output, ARROW, "->", Line, Column); Index += 2; Column += 2; continue;
                }
                /* need 3-char lookahead for ellipsis */
                if (LineBuffer[Index+2] != '\0' &&
                    LineBuffer[Index] == '.' && LineBuffer[Index+1] == '.' && LineBuffer[Index+2] == '.')
					{
#ifdef PyDebugCompiler
                    printf("DEBUG: match '...' at line=%d col=%d\n", Line, Column);
#endif
                    Emit(Output, ELLIPSIS, "...", Line, Column); Index += 3; Column += 3; continue;
                }
            }

            /* single-char */
            {
                char Lexeme[2] = { LineBuffer[Index], '\0' };
#ifdef PyDebugCompiler
                printf("DEBUG: single-char lexeme='%s' at line=%d col=%d\n", Lexeme, Line, Column);
#endif
                Emit(Output, MirrorCheckToken(Lexeme), Lexeme, Line, Column);
                Index++; Column++;
            }
        }
    }

#ifdef PyDebugCompiler
    printf("DEBUG: emit EOF token\n");
#endif
    while (IndentTop > 0)
	{
	    IndentTop--;
	    Emit(Output, DEDENT, "<DEDENT>", Line+1, 1);
	}
	Emit(Output, EndOF, "<EOF>", Line+1, 1); /* Emit a End of File */

#ifdef PyDebugCompiler
    fprintf(stderr, "DEBUG: LexOutFile exit, total tokens=%d\n", Output->Count);
#endif
}