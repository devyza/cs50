#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef uint8_t BYTE;

bool isJPEG(BYTE *bf);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    if (file == NULL)
    {
        printf("File cannot be read\n");
        return 2;
    }

    // Buffer Data from Card Memory (FAT System)
    BYTE *bf = malloc(512);

    // Allocate 8 Memory Spaces for ###.jpg (including NULL byte)
    char *filename = malloc(8);

    // File Pointer for Current Image
    FILE *image;

    // To Count Total Images
    int count = 0;

    // If the buffer is not Null, check JPEG
    while (fread(bf, 512, 1, file))
    {

        if (isJPEG(bf))
        {
            // The previous image fill need to be closed if new image is found
            if (count > 0)
            {
                fclose(image);
            }

            // Define file name with ###.jpg format and write a new image.
            sprintf(filename, "%03i.jpg", count++);
            image = fopen(filename, "w");

            // If the pointer for new image is NULL, deallocate memory and exit
            if (image == NULL)
            {
                free(filename);
                free(bf);
                printf("Can't create JPEG");
                return 3;
            }

        }

        // Write buffer into the new image
        if (count > 0)
        {
            fwrite(bf, 512, 1, image);
        }


    }

    free(filename);
    free(bf);
    return 0;
}

// To check whether JPEG or not
bool isJPEG(BYTE *bf)
{
    return bf[0] == 0xFF && bf[1] == 0xD8 && bf[2] == 0xFF && (bf[3] & 0xFF) == 0xE0;
}

