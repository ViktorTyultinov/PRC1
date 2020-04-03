#include <stdio.h>

#include "../include/Adidas.h"
#include "../include/FileManager.h"

static const char startFile[] = "output/start.txt";
static const char corruptedFile[] = "output/corrupted.txt";
static const char endFile[] = "output/end.txt";

int main(int argc, char **argv)
{
    int k = 0;
    printf("Main has started \n");

    char character;
    scanf("%c", &character);

    char doubleBits[2];

    Encode(character, doubleBits);
    printf("%s\n", "Done encoding");
    WriteFromFile(startFile, doubleBits);

    char decoded = 0;

    Decode(&decoded, doubleBits);
    printf("%s\n", "Done decoding");
    WriteFromFile(endFile, doubleBits);

    for (int i = 0; i < 8; i++)
    {
        printf("%d", !!((doubleBits[0] << i) & 0x80));
    }
    printf("\n");
    for (int i = 0; i < 8; i++)
    {
        printf("%d", !!((doubleBits[1] << i) & 0x80));
    }
    printf("\n");

    scanf("%d", &k);
    return 0;
}