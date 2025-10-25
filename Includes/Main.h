#pragma once
/**
 * Debug Toggle
 */
#define PyDebugCompiler /*Uncomment for Debug*/

/**
 * PyErrors
 */
typedef
enum
{

	PyExitOK,

}PyErrors;

/**
 * Constanats
 */
#define LimFiles	  255	/*uint8_t*/
#define LimFlags	  255
#define LimLineBuffer 4096

/**
 * Prototypes
 */
int main(int ArgumentsCount, char *ArgumentArray[]);