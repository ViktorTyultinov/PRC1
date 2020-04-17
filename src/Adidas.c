
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
    *byte ^= 1UL << randomNumber;

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
    printf("initial bit: %x\n", *byte);
    int bits[8];
    for (int i = 7; i >= 0; --i)
    {
        bits[i] = getSingleBit(*byte, i);
    }

    int sum1odd = bits[3]^bits[4]^bits[5]^bits[2];
    int sum2odd = bits[4]^bits[5]^bits[6]^bits[1];
    int sum3odd = bits[5]^bits[6]^bits[3]^bits[0];

    // printf("Start fix\n");

    // printf("Sum 1: %d\n", sum1odd);
    // printf("Sum 2: %d\n", sum2odd);
    // printf("Sum 3: %d\n", sum3odd);
    // printf("End fix\n");


    if (sum1odd && sum2odd && sum3odd)
        bits[5] = (bits[5] != 1);
    else if (sum1odd && sum2odd)
        bits[4] = (bits[4] != 1);
    else if (sum2odd && sum3odd)
        bits[6] = (bits[6] != 1);
    else if (sum1odd && sum3odd)
        bits[3] = (bits[3] != 1);

    for (int i = 7; i >= 0; --i)
    {
        if (bits[i] == 1)
        {
            *byte |= 1UL << i;
        }
        else
        {
            *byte &= ~(1UL << i);
        }
    }
    printf("final bit: %x\n", *byte);
}