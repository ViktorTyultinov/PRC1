
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
    int bits[8];
    for (int i = 7; i >= 0; --i)
    {
        bits[i] = getSingleBit(byte, i);
    }

    int pb[] = {0, 0, 0, 0, 0, 0};

    pb[1] = bits[4] ^ bits[5] ^ bits[6];
    pb[2] = bits[5] ^ bits[6] ^ bits[7];
    pb[3] = bits[6] ^ bits[7] ^ bits[4];

    pb[4] = bits[0] ^ bits[1] ^ bits[2];
    pb[5] = bits[1] ^ bits[2] ^ bits[3];
    pb[6] = bits[2] ^ bits[3] ^ bits[0];

    char MSB = (byte & mask1) >> 1;
    char LSB = (byte & mask2) << 3;

    for (int i = 0; i < 3; i++)
    {
        MSB ^= 1UL << 2 - i;
    }

    for (int i = 3; i < 6; i++)
    {
        LSB ^= 1UL << 5 - i;
    }

    res[0] = MSB;
    res[1] = LSB;
    return 0;
}

int SwapValue(char *byte)
{
    int randomNumber = (rand() % (7 - 0 + 1)) + 0;
    *byte ^= 1UL << 2 - randomNumber;
    return 0;
}

int Decode(char *decoded, char encoded[])
{
    char MSB = (encoded[0] << 1) & mask1;
    char LSB = (encoded[1] >> 3) & mask2;

    for (int i = 0; i < 4; i++)
    {
        if (getSingleBit(LSB, i))
            *decoded |= 1UL << i;
        else
            *decoded &= ~(1UL << i);
    }

    for (int i = 4; i < 7; i++)
    {
        if (getSingleBit(MSB, i))
            *decoded |= 1UL << i;
        else
            *decoded &= ~(1UL << i);
    }

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
}