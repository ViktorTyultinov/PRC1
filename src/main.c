#include <stdio.h>

#include "../include/Adidas.h"
#include "../include/FileManager.h"

static const char startFile[] = "output/start.txt";
static const char corruptedFile[] = "output/corrupted.txt";
static const char endFile[] = "output/end.txt";

int main(int argc, char **argv)
{
    int k = 0;
    printf("Main has started... ");

    // Read data from file
    char initialData[1001];
    ReadFromFile(startFile, initialData, 1000);

    // Encode it and write to second file
    char encoded[2002];
    for (int i = 0; i < 2002; i++)
    {
        if (initialData[i] == EOF)
            break;

        char pair[2];
        Encode(initialData[i], pair);

        // Toggle random bits
        // SwapValue(&pair[0]);
        // SwapValue(&pair[1]);
        encoded[i*2] = pair[0];
        encoded[i*2+1] = pair[1];
    }

    // Write the encoded data to the second file
    WriteFromFile(corruptedFile, encoded);

    // Read data from second file
    char encodedFromFile[2002];
    char decodedString[1000];
    ReadFromFile(corruptedFile, encodedFromFile, 2000);

    // Decode it and write it to the final one
    for (int i = 0; i < 1000; i++)
    {
        if (encodedFromFile[i*2] == EOF)
            break;

        char pair[2];
        pair[0] = encodedFromFile[i*2];
        pair[1] = encodedFromFile[i*2+1];
        // PairityFix(&pair[0]);
        // PairityFix(&pair[1]);
        char decodedChar = 0;
        Decode(&decodedChar, pair);
        decodedString[i] = decodedChar;
    }

    // Write the decoded info to final file
    WriteFromFile(endFile, decodedString);

    printf("done\n");
    scanf("%d", &k);
    return 0;
}