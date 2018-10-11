/* 
 * CS:APP Data Lab 
 * 
 * <Andrew Nguyen, W01183647>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 8.0.0.  Version 8.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2014, plus Amendment 1 (published
   2015-05-15).  */
/* We do not support C11 <threads.h>.  */

/* 
 *
 *
 * 
 *   reproduce the functionality of the following C function
 *   with the given restrictions
 *
 * int test_dl10(int parameter1, int parameter2)
 * {
 *   int result = 0;
 *   int i;
 *   for (i = parameter2; i <= parameter1; i++)
 *   result |= 1 << i;
 *   return result;
 *  } 
 *
 *   Assume 0 <= parameter2 <= 31, and 0 <= parameter1 <= 31
 *   If parameter2 > parameter1, then return 0
 *   Legal ops: ~ & + << 
 *   Max ops: 12
 *   Rating: 3
 */
//DONE
int dl10(int highbit, int lowbit) {
    int x = (~0 << highbit) << 1;
    int y = (~0 << lowbit);
    return ((~(x & y)) & (~(~x & ~y)) & y);
}
/* 
 *
 *   reproduce the functionality of the following C function
 *   with the given restrictions
 *
 *   int test_dl11(int x, int y)
 *   {
 *       return ~(x|y);
 *   }
 *
 *
 *   Legal ops: ~ &
 *   Max ops: 5
 *   Rating: 1
 *   Rating: 1
 */
//DONE: 3 total ops
int dl11(int x, int y) {
    return ((~x)&(~y));
}

/* 
 * int test_dl12(int x, int y)
 * {
 *    return x|y;
 * }
 *
 *
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
//DONE: 4 total ops
int dl12(int x, int y) {
    return ~((~x)&(~y));
}

/*
 *
 *  int test_dl13(int x) {
 *  int result = 0;
 *  int i;
 *  for (i = 0; i < 32; i++)
 *  result ^=  (x >> i) & 0x1;
 *  return result; }
 *
 *   Legal ops: ! & ^  >>
 *   Max ops: 20
 *   Rating: 4
 */
//DONE:
int dl13(int x) {
    //Program seems to be checking using an XOR to determine how many active bits
    //there are. If there's an odd number of active bits, it returns 1, if there's
    //an even number it returns 0.
    //Way too many ops, I just brute forced this one as trying to copy bits like
    //y = 0xFF etc etc didn't seem to give me a solution past 16 bits
    int y = 0;

    y ^= (x & 1);
    y ^= ((x >> 1) & 1);
    y ^= ((x >> 2) & 1);
    y ^= ((x >> 3) & 1);

    y ^= ((x >> 4) & 1);
    y ^= ((x >> 5) & 1);
    y ^= ((x >> 6) & 1);
    y ^= ((x >> 7) & 1);

    y ^= ((x >> 8) & 1);
    y ^= ((x >> 9) & 1);
    y ^= ((x >> 10) & 1);
    y ^= ((x >> 11) & 1);

    y ^= ((x >> 12) & 1);
    y ^= ((x >> 13) & 1);
    y ^= ((x >> 14) & 1);
    y ^= ((x >> 15) & 1);

    y ^= ((x >> 16) & 1);
    y ^= ((x >> 17) & 1);
    y ^= ((x >> 18) & 1);
    y ^= ((x >> 19) & 1);

    y ^= ((x >> 20) & 1);
    y ^= ((x >> 21) & 1);
    y ^= ((x >> 22) & 1);
    y ^= ((x >> 23) & 1);

    y ^= ((x >> 24) & 1);
    y ^= ((x >> 25) & 1);
    y ^= ((x >> 26) & 1);
    y ^= ((x >> 27) & 1);

    y ^= ((x >> 28) & 1);
    y ^= ((x >> 29) & 1);
    y ^= ((x >> 30) & 1);
    y ^= ((x >> 31) & 1);
    return y;
}

/* 
 *
 * 
 *   reproduce the functionality of the following C function
 *   with the given restrictions
 *
 *
 * int test_dl14(int x, int y)
 * {
 *   return x^y; }
 *
 *
 *
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
//DONE: 6 total ops
int dl14(int x, int y) {
    return ~(x & y) & ~((~x) & (~y));
}

/* 
 *
 *
 *
 *
 * 
 *   reproduce the functionality of the following C function
 *   with the given restrictions
 * 
 * asumming a little endiamachine 
 * least significant byte stored first 
 *
 * int test_dl15(int x, int n, int m)
 * {
 *
 *   unsigned int nmask, mmask;
 *
 *   switch(n) {
 *   case 0:
 *     nmask = x & 0xFF;
 *     x &= 0xFFFFFF00;
 *     break;
 *   case 1:
 *     nmask = (x & 0xFF00) >> 8;
 *     x &= 0xFFFF00FF;
 *     break;
 *   case 2:
 *     nmask = (x & 0xFF0000) >> 16;
 *     x &= 0xFF00FFFF;      
 *     break;
 *   default:
 *     nmask = ((unsigned int)(x & 0xFF000000)) >> 24;
 *     x &= 0x00FFFFFF;
 *     break;
 *    }
 *
 *   switch(m) {
 *   case 0:
 *     mmask = x & 0xFF;
 *     x &= 0xFFFFFF00;
 *     break;
 *   case 1:
 *     mmask = (x & 0xFF00) >> 8;
 *     x &= 0xFFFF00FF;
 *     break;
 *   case 2:
 *     mmask = (x & 0xFF0000) >> 16;
 *     x &= 0xFF00FFFF;      
 *     break;
 *   default:
 *     mmask = ((unsigned int)(x & 0xFF000000)) >> 24;
 *     x &= 0x00FFFFFF;
 *     break;
 *   }
 *
 *   nmask <<= 8*m;
 *   mmask <<= 8*n;
 *
 *   return x | nmask | mmask;
 * }
 *
 *
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
//DONE: 19 total ops
int dl15(int x, int n, int m) {
    /*
     *  x << 3 == x * 8. nShift and mShift store the num of bits to shift
     * n and m are either 0, 1, or 2. Assume a number is A B C D. If n and m are 0,
     * then nothing changes. If n is 1 or m is 1, the order changes to A B D C.
     * If n is 2 or m is 2, the order changes to A D C B.
     * If both m and n are equal, nothing changes,
     * If n is 3 or m is 3 (or greater), the default operation becomes D B C A.
     * Again, if they're equal, no change.
     * Finally, if m is 2 and n is 1, or vice versa, the order changes to A C B D
     *
     *
     * In summary, if n = m, no change, if n|m = 1, A B D C,
     * if n|m = 2, A D C B, if n and m != 0 && n != m, (n=2,m=1; n=1,m=2), then A C B D
     * if n|m = 3, D B C A/
     *
     * n and m can be thought of as a a right cycle or left cycle.
     * n "spins" two bytes to the left, and its number determines which bytes are spun. So
     * when n and m are equal, there is an equal amount of left circular and right circular shifts,
     * and nothing ends up happening.
     */

    //Single byte of just 1s.
    int a = 0xFF;
    int leftCycle = n << 3;
    int rightCycle = m << 3;

    int leftB = (a << leftCycle) & x;
    int rightB = (a << rightCycle) & x;
    int rightAndLeft = (a << leftCycle) | (a << rightCycle);

    leftB = (leftB >> leftCycle) & a;
    rightB = (rightB >> rightCycle) & a;

    leftB = leftB << rightCycle;
    rightB = rightB << leftCycle;

    rightAndLeft = ~rightAndLeft & x;

    return (rightAndLeft | leftB | rightB);
}

/* 
 *
 *
 * 
 *   reproduce the functionality of the following C function
 *   with the given restrictions
 *
 *
 *
 *
 * int test_dl16(int x, int y, int z)
 * {
 *   return x?y:z;
 *  }
 *
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
//DONE: 7 total ops
int dl16(int x, int y, int z) {
    //(x==0) gives 0 if false, 1 if true.
    //We could use !x but this saves us an op slot
    int a = ((((x != 0) << 31) >> 31) & y) | ((((x == 0) << 31) >> 31) & z);
    return a;
}

/* 
 *
 *
 * 
 *   reproduce the functionality of the following C function
 *   with the given restrictions
 *
 *
 *
 *  int test_dl17(int x)
 *  {
 *   return (x & 0x1) ? -1 : 0;
 *  }
 *
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
//DONE: 4 total ops
int dl17(int x) {
    return !(x & 1) + ~0;
}

/* 
 *
 * 
 *   reproduce the functionality of the following C function
 *   with the given restrictions
 *
 *
 *
 * int test_dl18(int x, int n)
 * {
 *    int p2n = 1<<n;
 *    return x/p2n;
 *		
 * }
 *
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
//DONE: 7 total ops
int dl18(int x, int n) {
    int xSign = x >> 31;
    int power = (1 << n) + ~0;
    return (x + (xSign & power)) >> n;
}

/* 
 *
 *
 *
 * 
 *   reproduce the functionality of the following C function
 *   with the given restrictions
 *
 *
 *
 *
 *
 *  int test_dl19(void) {
 *  int result = 0;
 *  int i;
 *  for (i = 0; i < 32; i+=2)
 *    result |= 1<<i;
 *  return result; }
 *
 *   Legal ops: |  << 
 *   Max ops: 6
 *   Rating: 1
 */
//DONE: 5 total ops
int dl19(void) {
    int x = 85; int y = 85;
    y = (x|y) << 8;
    y = (x|y);
    x = y;
    return (x|(y<<16));
}

/* 
 *   reproduce the functionality of the following C function
 *   with the given restrictions
 *
 *   int dl1(int x) {return (x < 0) ? -x : x; }
 *
 *   Example: dl1(-1) = 1.
 *   You may assume -TMax <= x <= TMax
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
//DONE: 7 total ops
int dl1(int x) {
    //need a way to check if x is negative first
    int xSign = x >> 31;
    int y = (~x + 1);
    y = y & xSign;
    xSign = ~xSign & x;
    return y | xSign;
}

/*
 *
 *
 * 
 *   reproduce the functionality of the following C function
 *   with the given restrictions
 *
 *  
 *
 *
 *   int test_dl20(int x)
 *   {
 *      return (x*3)/4;
 *   }
 *
 *   Legal ops: ! ~ & + << >>
 *   Max ops: 10
 *   Rating: 3
 */
//DONE: 6 total ops
int dl20(int x) {
    int xSign; int y;

    x = ((x << 1) + x); //multiply by 3
    xSign = x >> 31;
    y = 3 & xSign; //use y for division. 3 = (1<<2)-1
    return ((x + y) >> 2);
}

/* 
 * Reproduce the functionality of the following C function
 * unsigned test_dl21(unsigned uf) {
 * float f = u2f(uf);
 * float hf = 0.5*f;
 * if (isnan(f))
 *   return uf;
 * else
 *   return f2u(hf);
 * }
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
//DONE
unsigned dl21(unsigned uf) {
    //using 1071600962 as an example
    //Unsigned 1071600962 ==
    //0 0111111 1 1011111 01010101 01000010
    //1.7447894 = 0x3FDF553F

    //Unsigned 1063212354 ==
    //0 0111111 0 1011111 01010101 01000010
    //0.8723947 = 0x3F5F5542
    /*
     * From this comparison, we can see that division by two of a FP num can be performed simply by
     * decreasing the exponent portion by 1.
     * 0111 1111 ——> 0111 1110
     */

    unsigned sign = uf & (0x80 << 24);                  //Copies sign bit
    unsigned exp = (uf >> 23) & 0xFF;                   //Copies exp portion
    unsigned m = uf & (0x7F << 16 | 0xFF << 8 | 0xFF);  //Copies mantissa

    if (exp == 0xFF) { //If exponent is all 1s, is infinity
        return uf;
    } else if (exp > 1) { //Normalized nums, exponent is not 0000 0001
        return sign | --exp << 23 | m;
    } else {  //Denormalized nums and case 0000 0001 for exp.
        //Can't simply decrement exp by 1 if the exponent value would drop to 0
        if (exp == 1) { //if exp is of form 0000 0001
            m |= 1 << 23;
        }

        if ((m & 0x03) == 0x03) { //0000000 00000000 00000000 00000011
            m++;            //changes it to 00000100
        }
        m = m >> 1;         //shift over to 00000010
    }
    //Return only sign | m, due to the fact that denormalized nums, and exp == 1,
    //will have all 0s for exp (second ase is due to division requiring a -1 on the exp
    return sign | m;
}

/* 
 * reproduce the functionality of the following C function
 * unsigned test_dl22(int x) {
 * float f = (float) x;
 * return f2u(f);
 * }
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
//DONE
unsigned dl22(int x) {
    //Again, I'll use the same number as an example for the float functions
    //Unsigned 1071600962 ==
    //0 0111111 1 1011111 01010101 01000010
    //1.7447894 = 0x3FDF553F

    int e = 158;    //158 = 127 + 31, 127 for the exp of a float, 31 for a signed int
    int sign = x & 0x01 << 31;
    int m;

    if (x == 0x01 << 31) {
        return 0x01 << 31 | (158 << 23);
    } else if (!x) {
        return 0;
    }

    if (sign) {
        x = ~x + 1;
    }

    while (!(x & 0x01 << 31)) {
        x <<= 1;
        e -= 1;
    }

    m = (x & ~(0x01 << 31)) >> 8;

    if (x & 0x80 && ((x & 0x7F) > 0 || m & 1)) {
        m += 1;
    }

    return sign + (e << 23) + m;
}

/* 
 * reproduce the functionality of the following C function
 * unsigned test_dl23(unsigned uf) {
 *  float f = u2f(uf);
 *  float tf = 2*f;
 *  if (isnan(f))
 *    return uf;
 *  else
 *    return f2u(tf);
 * }
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
//DONE
unsigned dl23(unsigned uf) {
    //...Same number
    //Unsigned 1071600962 ==
    //0 0111111 1 1011111 01010101 01000010
    //1.7447894 = 0x3FDF553F

    //Unsigned 1079989570 ==
    //0 1000000 0 1011111 01010101 01000010
    //3.4895787 = 0x405F5542
    unsigned sign = uf & (0x80 << 24);                  //Copies sign bit
    unsigned exp = (uf >> 23) & 0xFF;                   //Copies exp portion
    unsigned m = uf & (0x7F << 16 | 0xFF << 8 | 0xFF);  //Copies mantissa

    //if the exp is all 1s, OR the exp + mantissa portions are all 1s, is NaN or infinite
    if ((exp & 0xFF) == 0xFF || !((exp << 23 | m) & (0x7F << 23 | 0xFF << 16 | 0xFF << 8 | 0xFF))) {
        return uf;
    } else if (exp == (0x7F << 24)) {
        //Eval to infinite, if the exp == 0111 1111, ie all 1s
        return (sign) | (0x7F << 24) | (0x80 << 16);
    } else if (exp & 0xFF) {
        //is not denormalized, so simply add another power of 2 to the exponent portion,
        //This is the inverse of dl21 which simply removes 1 (only in normalized cases)
        return uf + (0x80 << 16);
    } else {
        //Denormalized num
        return (uf & 0x80 << 24) | uf << 1;
    }
}

/*dl24 - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples:dl24(12) = 5
 *           dl24(298) = 10
 *           dl24(-5) = 4
 *           dl24(0)  = 1
 *           dl24(-1) = 1
 *           dl24(0x80000000) = 32
 * Here is a C function that accomplishes this. Reproduce the functionality
 * of this function using only the legal operations described below. 
 * int test_dl24(int x) {
 *   unsigned int a, cnt;
 *   
 *   x = x<0 ? -x-1 : x;
 *   a = (unsigned int)x;
 *   for (cnt=0; a; a>>=1, cnt++)
 *       ;
 *   return (int)(cnt + 1);
 * }
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
//DONE:
int dl24(int x) {
    //Function determines the number of bits required to represent x
    //As a signed int

    int sign = ~((x >> 31) & 1) + 1;
    int temp = 0;   //Random var
    int count = 2;  //The count of how many bits. Start at 0 because 0 needs 2 minimum
    //1 sign bit and 1 other bit for 0 itself : 00

    int pow = x;
    int zero = x;

    int intMin = x ^(1 << 31); //set all bits to 1 except the sign bit
    intMin = !intMin;
    intMin = ~intMin + 1;

    //check if input was zero,
    zero = !zero;
    zero = ~zero + 1;
    count += ~((intMin) & 1);

    //Check for pwr of 2. If so, then all bits will match except the 1.
    pow = pow & (pow + ~0);
    count += !pow;

    //Check negative/positive, incrementing each time
    x = (x & ~sign) | ((~x + 1) & sign);
    x += ~0;            //effectively x - 1
    x |= (x >> 1);
    x |= (x >> 2);
    x |= (x >> 4);
    x |= (x >> 8);
    x |= (x >> 16);
    x += 1;             //Go up to the next multiple of 2^n

    //0xFF is just 8 bits of 1s, made to 16 bits of 1s, checking byte 1 against byte 2
    temp = !(x & (255 | 255 << 8));   //temp = any matching bits in the first 16
    temp = ~temp + 1;
    count += (temp & 16);
    //same as above, checking bytes 1 against byte 3 and incrementing
    temp = !(x & (255 | 255 << 16));
    temp = ~temp + 1;
    count += (temp & 8);
    //Again, same check as above except it now checks 00001111 x4 instead of a full byte of 1s
    temp = (15 | 15 << 8);
    temp = (temp | temp << 16);
    temp = !(x & temp);
    temp = (~temp + 1);
    count += (temp & 4);
    //Alternating 00110011 bytes
    temp = (51 | 51 << 8);
    temp = (temp | temp << 16);
    temp = !(x & temp);
    temp = (~temp + 1);
    count += (temp & 2);
    //Alternating 01010101 bytes
    temp = (85 | 85 << 8);
    temp = (temp | temp << 16);
    temp = !(x & temp);
    temp = (~temp + 1);
    count += (temp & 1);

    return (count & ~zero) | (zero & 1);
}

/*
 *
 *   reproduce the functionality of the following C function
 *   with the given restrictions
 *
 *   int test_dl2(int x, int y)
 *   { long long lsum = (long long) x + y;
 *    return lsum == (int) lsum;}
 *
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
//DONE: 11 total ops
int dl2(int x, int y) {
    //After some testing, this function is intended to return 1 if true, 0 if false
    //The boolean condition is based on whether or not the integer overflows or not
    //ie: if a long is the sum of two integers, is it still the same if casted back
    //to an int?
    int xSign = (x >> 31) & 1;
    int ySign = (y >> 31) & 1;
    int totalSign = ((x + y) >> 31) & 1;
    return ((xSign ^ ySign) | !(xSign ^ totalSign));
}

/* 
 *   reproduce the functionality of the following C function
 *   with the given restrictions
 *
 *   int test_dl3(int x) {
 *    int i;
 *    for (i = 0; i < 32; i+=2)
 *       if ((x & (1<<i)) == 0)
 *	  return 0;
 *    return 1; }
 *
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
//DONE: 5 total ops
int dl3(int x) {
    //very similar to dl6. Instead of testing using 0x55555555, it
    //tests to see if the number is in fact 0x55555555
    int y = 0x55 | (0x55 << 8);
    y |= (y<<16);
    x = (x & y);
    return !(x + (~y + 1));
}

/* 
 *   reproduce the functionality of the following C function
 *   with the given restrictions
 *
 *   int test_dl4(int x) {
 *   int i;
 *   for (i = 1; i < 32; i+=2)
 *     if ((x & (1<<i)) == 0)
 *	  return 0;
 *    return 1; }
 *
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
//DONE: 6 total ops
int dl4(int x) {
    //very similar to dl6. Instead of testing using 0xAAAAAAAA, it
    //tests to see if the number is in fact 0xAAAAAAAA
    int y = 0xAA | (0xAA << 8);
    y |= (y<<16);
    x = (x & y);
    return !(x + (~y + 1));
}

/* 
 *   reproduce the functionality of the following C function
 *   with the given restrictions
 *
 *   int test_dl5(int x) {
 *   int i;
 *   for (i = 0; i < 32; i+=2)
 *     if (x & (1<<i))
 *	  return 1;
 *   return 0; }
 *
 *   Legal ops: ! ~ &  | + << >>
 *   Max ops: 10
 *   Rating: 2
 */
//DONE 7 total ops
int dl5(int x) {
    int y = 0x55 | (0x55 << 8);
    y |= (y<<16);
    x = (x & y);
    return !(!x);
}

/* 
 * 
 *   reproduce the functionality of the following C function
 *   with the given restrictions
 *
 *  int test_dl6(int x) {
 *   int i;
 *   for (i = 1; i < 32; i+=2)
 *       if (x & (1<<i))
 *	     return 1;
 *   return 0; }
 *
 *   Legal ops: ! &  | << 
 *   Max ops: 10
 *   Rating: 2
 */
//DONE: 7 total ops
int dl6(int x) {
    //After some analysis, this checks if every other bit (power of 2) is
    //Active. For example, 14 = 1110. This would check the 2^1 bit on
    //the first loop, the 2^3 bit on the next, etc. And if any of those
    //Bits is active it will return 1, else returns 0.
    //32 alternating bit number starting with 1:
    //10101010 10101010 10101010 10101010
    //This number is 0xAAAAAAAA. NOTE: Same concept applies to dl5, just with
    //0x55555555 instead
    int y = 0xAA | (0xAA << 8);
    y |= (y<<16);
    x = (x & y);
    return !(!x);
}

/* 
* 
 *   reproduce the functionality of the following C function
 *   with the given restrictions
 *
 *   int test_dl7(int x)
 *   {
 *      return !x;
 *   }
 *
 *   Legal ops: ~ & ^ | + >>
 *   Max ops: 10
 *   Rating: 4 
 */
//DONE: 7 total ops
int dl7(int x) {
    int result = x + ~0; //Because the - sign isn't allowed, but ~0 is effectively -1 for signed ints
    result = result & ~x;
    //Right shifts are arithmetic, preserving the MSB or the sign bit in this case
    return (~result >> 31) + 1;
}

/* 
 *
 *  
 *   reproduce the functionality of the following C function
 *   with the given restrictions
 *
 *   int test_dl8(int x, int y)
 *   {
 *      return x&y;
 *   }
 *
 *   Legal ops: ~ |
 *   Max ops: 6
 *   Rating: 1
 */
//DONE: 4 total ops
int dl8(int x, int y) {
    return ~((~x)|(~y));
}

/*
 *   
 *   reproduce the functionality of the following C function
 *   with the given restrictions
 *
 *   int test_dl9(int x) {
 *   int result = 0;
 *   int i;
 *   for (i = 0; i < 32; i++)
 *   result +=  (x >> i) & 0x1;
 *       return result;
 *   }
 *
 *   Legal ops: & | + << >>
 *   Max ops: 38
 *   Rating: 4
 */
//DONE:
int dl9(int x) {
    //After some testing, determined that the program counts the number of active bits (# of 1's)
    //in the input number's binary form. Original loops 32 times checking all 32 bits,
    //but the assignment guidelines state only positive numbers from 0-255 will be used. Simply check first 8 bits

    //The below only works for ints from 0 - 255; brute force approach. Instead will try checking all 4 bytes at once
    //Instead of one bit at a time.
//    int result = 0;
//    result += ((x) & 1);
//    result += ((x >> 1) & 1);
//    result += ((x >> 2) & 1);
//    result += ((x >> 3) & 1);
//
//    result += ((x >> 4) & 1);
//    result += ((x >> 5) & 1);
//    result += ((x >> 6) & 1);
//    result += ((x >> 7) & 1);
//
//    return result;

    int copy;
    int byte;
    int result;
    copy = ((17 << 24) | (17 << 16) |(17 << 8) | 17); //32 bits of 000000001, 4 times

    byte = x & copy;
    byte += ((x >> 1) & copy);
    byte += ((x >> 2) & copy);
    byte += ((x >> 3) & copy);

    result = byte & 0x0F;   //Would = byte & 0000... 1111.
    result += ((byte >> 4) & 0x0F); //Repeat for every "slot"
    result += ((byte >> 8) & 0x0F);
    result += ((byte >> 12) & 0x0F);
    result += ((byte >> 16) & 0x0F);
    result += ((byte >> 20) & 0x0F);
    result += ((byte >> 24) & 0x0F);
    result += ((byte >> 28) & 0x0F);

    return result;
}
