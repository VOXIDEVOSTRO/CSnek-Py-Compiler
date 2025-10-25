/**
 * Main Entry Point of The Command Line
 */

/*Standard Headers*/
#include <stdio.h>
#include <string.h>
/*Main Header*/
#include <Main.h>
#include <PyTokens.h>

/*

	csnekpy Files.py -Flags 

*/

int
/*csnekpy*/main(int ArgumentsCount, char *ArgumentArray[ /*Files.py*/ /*-Flags*/ ])
{
	const char *SourceFiles[LimFiles];
    const char *Flags[LimFlags];
    int FileCount = 0;
    int FlagCount = 0;

    for (int i = 1; i < ArgumentsCount; i++)
	{
        if (ArgumentArray[i][0] == '-')
		{
            if (FlagCount < LimFlags)
			{
                Flags[FlagCount++] = ArgumentArray[i];
            }
        } 
		else
		{
            if (FileCount < LimFiles)
			{
                SourceFiles[FileCount++] = ArgumentArray[i];
            }
        }
    }

    for (int i = 0; i < FileCount; i++)
	{
        FILE *PythonFile = fopen(SourceFiles[i], "r"/*Readonly*/);
        if (!PythonFile)
		{
#ifdef PyDebugCompiler
            fprintf(stderr, "Could not open %s\n", SourceFiles[i]);
#endif
            continue;
        }

#ifdef PyDebugCompiler
        printf("Lexing file: %s\n", SourceFiles[i]);
#endif

        PyTokenList PyListTokens = { .Count = 0 };
        LexOutFile(PythonFile, &PyListTokens);
        fclose(PythonFile);
#ifdef PyDebugCompiler
        for (int t = 0; t < PyListTokens.Count; t++)
		{
            PyToken *Token = &PyListTokens.Tokens[t];
            printf("%s -> %d (line %d, col %d)\n",
                   Token->Value ? Token->Value : "<null>",
                   Token->Type,
                   Token->Line,
                   Token->Column);
        }
#endif
    }
#ifdef PyDebugCompiler
    printf("Flags (%d):\n", FlagCount);
    for (int i = 0; i < FlagCount; i++)
	{
        printf("  %s\n",
		Flags[i]);
    }
#endif
    return PyExitOK;
}