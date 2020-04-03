
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
    // int lbyte[8];
    // for (int i = 7; i >= 0; --i)
    // {
    //     lbyte[i] = getSingleBit(byte, i);
    // }
    return 0;
}

int PairityFix(char *byte)
{
    int lbyte[8];
    for (int i = 7; i >= 0; --i)
    {
        lbyte[i] = getSingleBit(*byte, i);
    }

    int sum1 = lbyte[3] + lbyte[4] + lbyte[5] + lbyte[2];
    int sum2 = lbyte[4] + lbyte[5] + lbyte[6] + lbyte[1];
    int sum3 = lbyte[5] + lbyte[6] + lbyte[3] + lbyte[0];

    // 0 - false, 1-true
    int sum1odd = (sum1 % 2 == 0);
    int sum2odd = (sum2 % 2 == 0);
    int sum3odd = (sum3 % 2 == 0);

    if (sum1odd && sum2odd && sum3odd)
    {
        if (lbyte[5] == 1)
        {
            lbyte[5] = 0;
        }
        else
        {
            lbyte[5] = 1;
        }
    }
    else if (sum1odd && sum2odd)
    {
        if (lbyte[4] == 1)
        {
            lbyte[4] = 0;
        }
        else
        {
            lbyte[4] = 1;
        }
    }
    else if (sum2odd && sum3odd)
    {
        if (lbyte[6] == 1)
        {
            lbyte[6] = 0;
        }
        else
        {
            lbyte[6] = 1;
        }
    }
    else if (sum1odd && sum3odd)
    {
        if (lbyte[3] == 1)
        {
            lbyte[3] = 0;
        }
        else
        {
            lbyte[3] = 1;
        }
    }
    else if (sum1odd)
    {
        if (lbyte[2] == 1)
        {
            lbyte[2] = 0;
        }
        else
        {
            lbyte[2] = 1;
        }
    }
    else if (sum2odd)
    {
        if (lbyte[1] == 1)
        {
            lbyte[1] = 0;
        }
        else
        {
            lbyte[1] = 1;
        }
    }
    else if (sum3odd)
    {
        if (lbyte[0] == 1)
        {
            lbyte[0] = 0;
        }
        else
        {
            lbyte[0] = 1;
        }
    }

    for (int i = 7; i >= 0; --i)
    {
        if (lbyte[i] == 1)
        {
            *byte |= 1UL << i;
        }
        else
        {
            *byte &= ~(1UL << i);
        }
    }
    return 0;
}

int Decode(char *decoded, char encoded[])
{
    printf("Decode()\n");

    printf("Decoding encoded[0]: ");
    for (int i = 0; i < 8; i++)
    {
        printf("%d", !!((encoded[0] << i) & 0x80));
    }
    printf("\n");
    printf("Decoding encoded[1]: ");
    for (int i = 0; i < 8; i++)
    {
        printf("%d", !!((encoded[1] << i) & 0x80));
    }
    printf("\n");

    char byte1 = (encoded[0] << 1) & mask1;
    char byte2 = (encoded[1] >> 3) & mask2;

    printf("Decoding byte1: ");
    for (int i = 0; i < 8; i++)
    {
        printf("%d", !!((byte1 << i) & 0x80));
    }
    printf("\n");
    printf("Decoding byte2: ");
    for (int i = 0; i < 8; i++)
    {
        printf("%d", !!((byte2 << i) & 0x80));
    }
    printf("\n");

    for (int i = 0; i < 4; i++)
    {
        int bitValue = getSingleBit(byte2, i);
        if (bitValue)
        {
            *decoded |= 1UL << i;
        }
        else
        {
            *decoded &= ~(1UL << i);
        }
    }
    printf("Processed byte1.\n");

    for (int i = 5; i < 8; i++)
    {
        int bitValue = getSingleBit(byte1, i);
        if (bitValue)
        {
            *decoded |= 1UL << i;
        }
        else
        {
            *decoded &= ~(1UL << i);
        }
    }
    printf("Processed byte2.\n");

    printf("Decoding byte: ");
    for (int i = 0; i < 8; i++)
    {
        printf("%d", !!((*decoded << i) & 0x80));
    }
    printf("\n");

    return 0;
}