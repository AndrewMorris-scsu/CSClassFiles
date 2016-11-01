
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#ifndef NUMBERBASE_H
#define NUMBERBASE_H

#ifdef HEX
#define BASE 16
#else
#define BASE 2
#endif
#if (BASE == 16)
    #define SHIFTL(x) (x << 4 | x >> 28)
    #define SHIFTR(x) (x >> 4 | x << 28)
    #define KILLR(x) (x >> 4)
#else
    #define SHIFTL(x) ((x << 1) | (x >> 31))
    #define SHIFTR(x) ((x >> 1) | (x << 31))
    #define KILLR(x) (x >> 1)
#endif
#define BINARYSIZE 32

#endif
