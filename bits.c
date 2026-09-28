/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~(~x | ~y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(x & y) & ~(~x & ~y);
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    return !( !x ^ !y ) && !((x >> 31) ^ (y >> 31));
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int res = 0;
    int shift;

    shift = (0xFFFF < v) << 4;
    v = v >> shift;
    res = res | shift;

    shift = (0xFF < v) << 3;
    v = v >> shift;
    res = res | shift;

    shift = (0xF < v) << 2;
    v = v >> shift;
    res = res | shift;

    shift = (0x3 < v) << 1;
    v = v >> shift;
    res = res | shift;

    shift = 0x1 < v;
    res = res | shift;

    return res;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int n8 = n << 3;
    int m8 = m << 3;
    int n_byte = (x >> n8) & 0xFF;
    int m_byte = (x >> m8) & 0xFF;
    int mask = (0xFF << n8) | (0xFF << m8);
    return (x & ~mask) | (n_byte << m8) | (m_byte << n8);
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    unsigned reversed = 0;
    for (int i = 32; i; i--) {
        reversed = (reversed << 1) | (v & 1);
        v = v >> 1;
    }
    return reversed;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
 int logicalShift(int x, int n) {
    int mask = ~(((1 << 31) >> n) << 1);
    return (x >> n) & mask;
}


/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int cnt = 0;
    int t;

    t = (!(~x >> 16)) << 4;
    cnt = cnt + t;
    x = x << t;

    t = (!(~x >> 24)) << 3;
    cnt = cnt + t;
    x = x << t;

    t = (!(~x >> 28)) << 2;
    cnt = cnt + t;
    x = x << t;

    t = (!(~x >> 30)) << 1;
    cnt = cnt + t;
    x = x << t;

    t = !(~x >> 31);
    cnt = cnt + t;
    x = x << t;

    t = !(~x >> 31);
    cnt = cnt + t;

    return cnt;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    unsigned sign, exp, frac;
    unsigned absX;
    unsigned hp = 1 << 31;
    unsigned shiftLeft = 0;
    unsigned round;
    unsigned result;
    if (0 == x) return 0;
    absX = x;
    sign = 0;
    if (x < 0) {
        absX = -x;
        sign = hp;
    }
    while (0 == (hp & absX)) {
        absX = absX << 1;
        shiftLeft += 1;
    }
    exp = 127 + 31 - shiftLeft;
    round = absX & 0xff;
    frac = (~(hp >> 8)) & (absX >> 8);
    result = sign | (exp << 23) | frac;

    if (round > 0x80) {
        result += 1;
    } else if (0x80 == round) {
        if (frac & 1) {
            result += 1;
        }
    }
    return result;
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned sign = uf >> 31;
    unsigned exp = (uf >> 23) & 0xff;
    unsigned frac = uf & 0x7fffff;
    unsigned result;
    
    if (exp == 0xff) {
        result = uf;
    } else if (exp == 0x00) {
        frac = frac << 1;
        result = (sign << 31) | (exp << 23) | frac;
    } else {
        exp++;
        result = (sign << 31) | (exp << 23) | frac;
    }
    return result;
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    unsigned sign = uf2 >> 31;
    unsigned exp = (uf2 >> 20) & 0x7FF;
    unsigned val = 0x80000000 | ((uf2 & 0xFFFFF) << 11) | (uf1 >> 21);
    if (exp < 1023)
        return 0;
    if (exp > 1054)
        return 0x80000000;
    val = val >> (1054 - exp);
    if (sign) {
        if (val > 0x80000000)
            return 0x80000000;
        return -val;
    } else {
        if (val > 0x7FFFFFFF)
            return 0x80000000;
        return val;
    }
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if (x > 127)
        return 0x7f800000;
    if (x < -149)
        return 0;
    if (x < -126)
        return 1 << (x + 149);
    return (x + 127) << 23;
}
