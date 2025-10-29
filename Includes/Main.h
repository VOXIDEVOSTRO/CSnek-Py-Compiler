#pragma once
#include <__Debug__.h>

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
#define TabSpace	  8		/*8 Spaces?*/

/**
 * Prototypes
 */
int main(int ArgumentsCount, char *ArgumentArray[]);