/**
 * Main Entry Point of The Command Line
 */

/*Standard Headers*/
#include <stdio.h>
#include <strings.h>
/*Main Header*/
#include "!Main.h"

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

#ifdef PyDebugCompiler
    printf("Source Files (%d):\n", FileCount);
    for (int i = 0; i < FileCount; i++)
	{
        printf("  %s\n", 
		SourceFiles[i]);
    }

    printf("Flags (%d):\n", FlagCount);
    for (int i = 0; i < FlagCount; i++)
	{
        printf("  %s\n",
		Flags[i]);
    }
#endif
    return PyExitOK;
}