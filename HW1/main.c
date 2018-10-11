#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

void print_bytes(const void *object, size_t size) {
    const unsigned char * const bytes = object;
    size_t i;

    printf("[ ");
    for(i = 0; i < size; i++) {
        printf("%02x ", bytes[i]);
    }
    printf("]\n");
}

/*
 * ASSIGNMENT 2.58
 */
int is_little_endian() {
    /*
     * Primary difference between big endian and little endian machines is the ordering of the bytes by significance.
     * Big endian stores the most significant byte first, in the smallest address.
     * Little endian stores the least significant byte first, in the smallest address.
     *
     * e.g.: if we have a hexadecimal number, 4A 3B 2C 1D, then big endian would be:
     *          Byte    |   Mem. Addr.
     *          4A      |   1000
     *          3B      |   1001
     *          2C      |   1002
     *          1D      |   1003
     *
     * and little endian would be:
     *          Byte    |   Mem. Addr.
     *          1D      |   1000
     *          2C      |   1001
     *          3B      |   1002
     *          4A      |   1003
     *
     * Note the opposite orders.
     * */

    //to determine endian-ness, make a number, get the memory address
    int x = 0x4a3b2c1d;

    //cast pointer to be interpreted as a char at the 1st address of x
    char *c = (char*) &x; //why can't you use c instead of *c? *c is an integer, see notes
//    printf("%d\n",*c);

    //little endian will have 1d which is 29 at the first address, otherwise it will have 4a for big endian
    if (*c == 29) {
        return 1;
    } else {
        return 0;
    }
}

/*
 * ASSIGNMENT 2.59
 */
int swap_significance(int x, int y) {
    /*
     * Will take two words, and swap the least significant bytes of x and y
     * and then return z as the final word. Note, returns the pointer to z
     */

    //Creation of a char array to hold the bytes for a new integer
    unsigned char zBytes[4];

    //I couldn't figure this out without reading the bits directly into the zBytes array via shifts
    zBytes[3] = (y >> 24);
    zBytes[2] = (y >> 16);
    zBytes[1] = (y >> 8);
    zBytes[0] = (x >> 0);   //all bytes are the same as y except the least significant one which comes from x
    //this part depends on endianness – intel processors are generally little endian today

    int* z = &zBytes;   //integer pointer to the array
//    printf("%d\n", *z);

    //wrote function to print individual hexadecimal bytes of an object
//    print_bytes(&x, sizeof(x));
//    print_bytes(&y, sizeof(y));
//    print_bytes(&*z, sizeof(*z));

    int result = *z;

    return result;
}

/*
 * ASSIGNMENT 2.73
 */
int saturating_add(int x, int y) {
    /*
     * Returns sum of x and y unless there is overflow, then returns INT_MIN or INT_MAX
     * No conditional statements allowed... Overflow only occurs if adding two numbers with the same sign,
     * purely due to the limits of an int data type, a positive number + a negative can't result in overflow.
     *
     * So if conditional statements like if, else, <, >, and so on aren't allowed, I need to find a  way to get a
     * boolean return somewhere. == and != is allowed, all logic and bitwise operations are allowed,
     * maybe an XOR could be used?
     *
     * 1) compare the signs of x and y,
     * 2) if opposite signs, return x + y,
     * 3) if same signs, add x + y and check the result's sign against the sign of x
     * 4) if the sign is opposite to x, i.e.: overflow occursed and sign reversed, return min/max
     */

    /*
    int x = 10;
    int y = -10;
    print_bytes(&x, sizeof(x));
    print_bytes(&y, sizeof(y));
                   Hex                        Binary
              LSB =====> MSB  MSB ==============================> LSB
     10     = [ 0a 00 00 00 ] 0000 0000 0000 0000 0000 0000 0000 1010
    -10     = [ f6 ff ff ff ] 1111 1111 1111 1111 1111 1111 1111 0110
    INT_MAX = [ ff ff ff 7f ] 0111 1111 1111 1111 1111 1111 1111 1111
    INT_MIN = [ 00 00 00 80 ] 1000 0000 0000 0000 0000 0000 0000 0000
     */

    //integers are 4 bytes / 32 bits, in binary form, the most significant bit is the sign bit.
    //sign_x/y then becomes 0 for positive numbers and 1 for negative numbers because of the (& 1)
    //1000 0000 0000 0001 ===> 0000 0000 0000 0001 because +1 and -1 only share the 1 at the beginning
    int sign_x = (x >> 31) & 1;
    int sign_y = (y >> 31) & 1;
//    printf("%d\n", sign_x);
//    printf("%d\n", sign_y);
//    print_bytes(&x, sizeof(x));
//    print_bytes(&y, sizeof(y));

    //Gives 0 if signs are the same, and 1 if signs are different
    int sameSign = (sign_x - sign_y)*(sign_x - sign_y);
//    printf("%d\n", sameSign);

    int result, sign_result = -1;   //If it's never used, it will remain -1

    //if sameSign == 1, then signs are different, return x + y, if signs are same, set result to -1 (as a flag for later)
    (sameSign == 1 && (result = x + y) || ((result = x + y)
                                           & (sign_result = (result >> 31) & 1)
                                           & (sameSign = (sign_x - sign_result)*(sign_x-sign_result))));

    //if sign_result changes to 1, result overflowed to INT_MAX
    ((sign_result == 1) & (sameSign == 1) && (result = INT_MAX));

    //if sign_result changes to 0, result overflowed to INT_MIN
    ((sign_result == 0) & (sameSign == 1) && (result = INT_MIN));

//    printf("%d\n", sign_result);
//    printf("%d\n", sameSign);

    return result;
    //I REALLY DID NOT LIKE THIS PROBLEM. Coulda been done with a simple if x < 0 to check for overflow! Just sayin.
}

/*
 *  ASSIGNMENT 2.85
 *  A) 7.0      Divide integer part: 7/2 = 3r1
 *                                   3/2 = 1r1
 *                                   1/2 = 0r1
 *     7 b10 = 111 b2. = 1.11 b2 * 2^2
 *     So, sign bit = 0, M = 1.11 b2, E = 2
 *
 *     Adjust E for bias, E + 2^(k-1)-1
 *     2 + 2^7 - 1 = 129 b10.
 *     129 b10 = (1000 0001) b2 //Exponent part of single precision fp num
 *
 *     Mantissa = 1.11 --> remove the 1 and decimal point and extend to 23 bits
 *     Mantissa = 110 0000 0000 0000 0000 0000
 *
 *     Put it all together, sign + exp + mantissa:
 *     0 1000 0001 110 0000 0000 0000 0000 0000 = 7.0
 *
 *     E = 2
 *     M = 1.11 b2 = 7/4
 *     f = 0.11 b2 = 3/4
 *     V = 7
 *
 *
 * B) Largest odd integer in floating point has only 1s in the mantissa
 *      So E = 23 (number of fraction bits) because we know that M is maxed out on 1s.
 *      M must be 1.11.....1111, because all 23 bits of the mantissa will be 1.
 *
 *      23 + 2^7 - 1 = 150 b10 = 1001 0110 b2
 *
 *      Mantissa = 111 1111 1111 1111 1111 1111
 *
 *      Final number = 0 1001 0110 111 1111 1111 1111 1111 1111
 *
 *      E = 23
 *      M = 1.111111..... b2 = 2 - 2^(-23) (which is ~2)
 *      f = 0.111111..... b2 = 1 - 2^(-23) (~1)
 *      //^^ M and f are calculated because 1.0 = 1 * 2^0, 0.1 = 1 * 2^(-1), etc.
 *
 *      V = 2^24 - 1 = 16,777,215
 *
 */

/*
 * 2.86
 * An 80 bit word looks like:
 *
 * |S|    Exp (15bit)    |I|         Frac (63bit)         |
 *
 * For a total of 80 bits. Thus with 1 sign bit, 15 exp bits, 1 integer bit (ignore for calculation, just use regular
 * normalised/denormalised rules), and 63 fractional bits:
 *
 * Smallest positive denormalized   :   2^-16382 * 2^-63                = 2^-16445
 * Smallest positive normalized     :   2^-16382 * 1                    = 2^16382
 * Largest normalized               :   2^49149 * ((2^63)-1) / (2^63)
 */

/*
 * 2.90
 */
float fpwr2(int x) {

    //Problem specifies IEEE single precision, 32 bits

    unsigned exp, frac;
    unsigned u;

    if (x < -149) {
        exp = 0;
        frac = 0;
    }

    else if (x < -126) {
        exp = 1;
        frac = 1 << (23 - (-126 - x));
    }

    else if (x < 128) {
        exp = x + 127;
        frac = 0;
    }

    else {
        exp = 255;
        frac = 0;
    }

    u = exp << 23 | frac;
}

/*
 * 2.91
 *
 * If π has a hex value of 0x40490FDB... Left to right, sign bit first etc. due to endianness inside this comp
 *
 * A) the fractional binary number for pi is 0 10000000 10010010000111111011011
 *      Separated by sign bit, exp, fractional
 *
 * B) Binary representation of 22/7 is 11 . 0010 0100 0011 1111 0101 1 ....
 *      This can be gotten using the regular method to convert decimal to binary (not the same as decimal to float)
 *      ie: 11 = 3, followed by the decimal form of 1/7
 *
 * C)   0 0100100 10000111111011011
 *      0 0100100 0011111101011
 *
 *      After 8 bits, the two approximations diverge. So on the 9th bit
 */

/*
 * Andrew Nguyen
 * W0118 3647
 * Spring 2017, CSCI 247
 * Prof. Julian Rrushi
 */

/*
 * 2.61
 */

int ch2_61_A(int x) {
    return !!x; //Essentially if x != 0
}
int ch2_61_B(int x) {
    return !!(~x); //Exact inverse of A
}
int ch2_61_C(int x) {
    int y = ((sizeof(x) - 1) << 3);    //Least significant byte of x
    return !!(x & (1 << y));   //If any == 1, returns !!
}
int ch2_61_D(int x) {
    !!(~x & 0xFF);  //not-x & 1111 1111, !! determines if result != 0
}

/*
 * 2.64
 */
int any_odd_one(unsigned x) {
    //1010 ... For all 8 bytes
    return !!(x & 0xAAAAAAAA);
}

/*
 * 2.65
 * Allowed to assume x is size of 32 bits
 * So we can run it logarithmically:
 * 32/2 = 16
 * 16/2 = 8... Etc. Until reaching the last bit
 */
int odd_ones(unsigned x) {
    x ^= x >> 16;   //Compares first half and second half
    x ^= x >> 8;    //Compares first half and second half of the above
    x ^= x >> 4;
    x ^= x >> 2;
    x ^= x >> 1;
    return x & 1;   //final comparison, is last bit 1?
}

/*
 * 3.68
 * A = 9
 * B = 5
 *
 * 180b ≤ AB ≤ 184b
 * 7b ≤ A ≤ 10b
 * 5b ≤ B ≤ 8b
 *
 * str2.t = int @ 8 bytes, %rsi
 * str2.u = long @ 32 bytes, %rsi
 * str1.y = long @ 184 bytes, %rdi
 *
 * We can use a system of equations and a martix to find the values of A and B
 */

/*
 * 3.69
 *
 * CNT = 9
 *
 * typedef struct{
 *    int idx;
 *    int x[4];
 * } a_struct;
 */

/*
 * Andrew Nguyen, CSCI 247, Spring 2017, Julian Rrushi
 * 6.23
 *
 * Average time to access a sector on a disk:
 * = (Avg. Seek Time) + (Rotational Latency) + (Transfer/Sector Read Time)
 * All in milliseconds,
 *
 * Avg. seek given as 4ms
 * Rotational speed given as 15000rpm, which is equivalent to (15000rot/1min) * (1min/60s) * (1s/1000ms)
 *      = 15000rot / 60000ms = 1rot / 4ms
 * Transfer time is the time to read the sector,
 * which is defined as (time for 1 rotation) / (avg sectors per track)
 * In this case, avg sectors per track is given as 800.
 * So Transfer time = 4ms / 800 SPT = 0.005ms
 *
 * Total average time to access sector on the given disk is:
 * = 4ms + 4ms + 0.005ms = 8.005ms
 */




int main() {
    float x = ;
    printf("%f", x);


    /*
    printf("%d\n", is_little_endian());                         //Returns 1 if little endian
    printf("%x\n", swap_significance(0x89abcdef, 0x76543210));  //Should return 0x765432df (the 0x padding doesn't show)

    printf("%d\n",saturating_add(9992344324,-9994798099));      //Returns -2,453,775
    printf("%d\n",saturating_add(-9992344324,-9994798099));     //INT_MIN overflow
    printf("%d\n",saturating_add(9992344324,9994798099));       //INT_MAX overflow
    */

//    int x = random();
//    int y = random();
//    int z = random();
//
//    double dx = (double) x;
//    double dy = (double) y;
//    double dz = (double) z;
//
//    printf("%d\n", ((float) x == (float) dx));
//    printf("%d\n", ((dx - dy) == (double) (x-y)));
//    printf("%d\n", (((dx+dy)+dz) == (dx + (dy +dz))));
//    printf("%d\n", (((dx*dy)*dz) == (dx * (dy *dz))));
//    printf("%d\n", ( (dx/dx) == (dz/dz)));
//
//    print_bytes(&x, sizeof(x));
//    print_bytes(&dx, sizeof(dx));
//    printf("\n");
//
//    print_bytes(&y, sizeof(y));
//    print_bytes(&dy, sizeof(dy));
//    printf("\n");
//
//    print_bytes(&z, sizeof(z));
//    print_bytes(&dz, sizeof(dz));
//    printf("\n");

    return 0;
}