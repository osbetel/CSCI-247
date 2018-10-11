#include <stdio.h>
#include <limits.h>
#include <math.h>

void bPrintInt(int num, int bit) {
    if ( bit >= 8*sizeof(num) )
    {
        return;
    }

    bPrintInt(num/2, bit+1);
    printf("%d", num%2);

    if ( bit%8 == 0 )
    {
        printf(" ");
    }
    if ( bit == 0 )
    {
        printf("\n");
    }
}

void bPrintLong(long num, int bit) {
    if ( bit >= 8*sizeof(num) )
    {
        return;
    }

    bPrintLong(num/2, bit+1);
    printf("%ld", num%2);

    if ( bit%8 == 0 )
    {
        printf(" ");
    }
    if ( bit == 0 )
    {
        printf("\n");
    }
}

void intPrint(int n) {
    printf("%d", n);
    printf(" = ");
    bPrintInt(n,0);
}

void longPrint(long n) {
    printf("%ld", n);
    printf(" = ");
    bPrintInt(n,0);
}

unsigned float_half(unsigned uf){
    unsigned sign = uf & (0x80 << 24);
    unsigned exp = uf >> 23 & 0xff;
    unsigned m = uf & (0x7f << 16 | 0xff << 8 | 0xff);

    if(exp == 0xff)
        return uf;
    else if (exp > 1)
        return sign | --exp << 23 | m;
    else {
        if (exp == 1)
            m |= 1 << 23;
        if ((m & 3) == 3)
            m++;
        m >>= 1;
        return sign | m;
    }
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
unsigned dl21(unsigned uf) {

    //using 1071600962 as an example
    //1071600962 ==
    //0 0111111 1 1011111 01010101 01000010
    //1.7447894 = 0x3fdf553f

    //1063212354 ==
    //0 0111111 0 1011111 01010101 01000010
    //0.8723947 = 0x3f5f5542
    /*
     * From this comparison, we can see that division by two of a FP num can be performed simply by
     * decreasing the exponent portion by 1.
     * 0111 1111 ——> 0111 1110
     */

    unsigned sign = uf & (0x80 << 24);
    unsigned exp = uf >> 23 & 0xff;
    unsigned m = uf & (0x7f << 16 | 0xff << 8 | 0xff);

    if(exp == 0xff)
        return uf;
    else if (exp > 1)
        return sign | --exp << 23 | m;
    else {
        if (exp == 1)
            m |= 1 << 23;
        if ((m & 3) == 3)
            m++;
        m >>= 1;
        return sign | m;
    }
}

unsigned dl23(unsigned uf) {

    //Again, I'll use the same number as an example for the float functions
    //1071600962 ==
    //0 0111111 1 1011111 01010101 01000010
    //1.7447894 = 0x3fdf553f

    //1063212354 ==
    //0 0111111 0 1011111 01010101 01000010
    //0.8723947 = 0x3f5f5542
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

int main() {

    unsigned x = 1071600962; unsigned y = 1063212354; int z = INT_MIN;
//    printf("%d", x - y);
//    float a = 1.744789;
//    printf("%f", a);
//    printf("%x", y); printf("\n");


    printf("%x",dl23(1071600962));
    unsigned real = dl21(x);


    return 0;
}