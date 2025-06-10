#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const uint8_t signature[4] = {0xFF, 0xD8, 0xFF, 0xE0};

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open input file
    FILE *input = fopen(argv[1], "r");
    if (!input)
    {
        printf("Could not open %s\n", argv[1]);
        return 1;
    }

    uint8_t buffer[512];
    uint8_t firstBytes[4];
    FILE *output = NULL;
    int fileCount = 0;
    char *fileName = malloc(8);
    if (fileName == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // While there's still data left to read from the memory card
    while (fread(buffer, 1, 512, input) == 512)
    {
        // Store first four bytes
        int length = sizeof(firstBytes);
        for (int i = 0; i < length; i++)
        {
            firstBytes[i] = buffer[i];
        }

        // Check JPEG signature
        if (firstBytes[0] == signature[0] && firstBytes[1] == signature[1] &&
            firstBytes[2] == signature[2] && (firstBytes[3] & 0xF0) == signature[3])
        {
            // End old file
            if (output)
            {
                fclose(output);
                fileCount++;
            }

            // Update fileName
            sprintf(fileName, "%03d.jpg", fileCount);

            // Start a new file
            output = fopen(fileName, "w");
            if (!output)
            {
                printf("Could not create %s.\n", fileName);
                return 1;
            }

            // Print buffer
            fwrite(buffer, 1, 512, output);
        }
        else if (output)
        {
            // Print buffer
            fwrite(buffer, 1, 512, output);
        }
    }

    fclose(input);
    fclose(output);
    free(fileName);

    return 0;
}
