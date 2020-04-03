
#include "../include/Adidas.h"
#include "../include/FileManager.h"
#include <string.h>
#include <stdio.h>

const int mask1 = 0xF0;
const int mask2 = 0xF;

int getSingleBit(char byte, int pos)
{
    return (byte >> pos) & 1;
}

int Encode(char byte, char *res)
{
    int lbyte[8];
    for (int i = 7; i >= 0; --i)
    {
        lbyte[i] = getSingleBit(byte, i);
    }

    int first[3] = {lbyte[4], lbyte[5], lbyte[6]};
    int second[3] = {lbyte[5], lbyte[6], lbyte[7]};
    int third[3] = {lbyte[6], lbyte[7], lbyte[4]};

    int forth[3] = {lbyte[0], lbyte[1], lbyte[2]};
    int fifth[3] = {lbyte[1], lbyte[2], lbyte[3]};
    int six[3] = {lbyte[2], lbyte[3], lbyte[0]};

    int firstSum = 0;
    int secondSum = 0;
    int thirdSum = 0;
    int forthSum = 0;
    int fifthSum = 0;
    int sixSum = 0;

    int sums[] = {firstSum, secondSum, thirdSum, forthSum, fifthSum, sixSum};
    int *arrays[] = {first, second, third, forth, fifth, six};
    int pb[] = {0, 0, 0, 0, 0, 0};

    for (int i = 0; i < (sizeof(sums) / sizeof(int)); i++)
    {
        for (int n = 0; n < (sizeof(first) / sizeof(int)); n++)
        {
            sums[i] += arrays[i][n];
        }
    }

    for (int l = 0; l < sizeof(sums) / sizeof(int); l++)
    {
        pb[l] = (sums[l] % 2 == 0) ? 0 : 1;
    }

    char byte1 = (byte & mask1) >> 1;
    char byte2 = (byte & mask2) << 3;

    if (pb[0] == 1)
    {
        byte1 ^= 1UL << 2;
    }
    if (pb[1] == 1)
    {
        byte1 ^= 1UL << 1;
    }
    if (pb[2] == 1)
    {
        byte1 ^= 1UL;
    }

    if (pb[3] == 1)
    {
        byte2 ^= 1UL << 2;
    }
    if (pb[4] == 1)
    {
        byte2 ^= 1UL << 1;
    }
    if (pb[5] == 1)
    {
        byte2 ^= 1UL;
    }

    res[0] = byte1;
    res[1] = byte2;
    return 0;
}

int SwapValue(char *byte)
{
    return 0;
}

int Decode(char *byte)
{
    int lbyte[9];
    for (int i = 7; i >= 0; --i)
    {
        lbyte[i] = getSingleBit(byte, i);
    }
    return 0;
}
