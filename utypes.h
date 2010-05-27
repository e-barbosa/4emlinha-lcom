#ifndef _UTYPES_H_
#define _UTYPES_H_

#include <stdio.h>
#include <dpmi.h>
#include <go32.h>
#include <dos.h>
#include <sys/nearptr.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/** @defgroup UserTypes UserTypes
 * @{
 *
 * Typedefs for lazzy programmers
 */

typedef unsigned char uchar;   ///< uchar is shorter to type than unsigned char
typedef unsigned short ushort; ///< ushort is an unsigned short
typedef unsigned int uint;     ///< uint is an unsigned int
typedef unsigned long ulong;   ///< ulong is an unsigned long

typedef unsigned char Byte;    ///< 8 bits, only on i386
typedef unsigned short Word;   ///< 16 bits, only on i386 

/** User defined boolean type
* <pre>
* usage example:
* Bool done = false;
* while (done == false) {...}
* </pre>
*/
typedef enum {
  false = 0, ///< the false value
  true = 1 ///< the true value
} Bool; ///< user defined boolean type

/**@} end of user types */

#endif
