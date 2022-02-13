#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BLOCK_SIZE 512
typedef uint8_t BYTE;
int main(int argc, char *argv[])
{
    // Check for invalid usage
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

// Open memory card
    char *input_filename = argv[1];
    FILE *inptr = fopen(input_filename, "r");
    FILE *outptr = NULL;
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s. \n", input_filename);
        return 2;
    }

// Look for beginning of JPEG file - 0xff 0xd8 0xff 0xe#
    BYTE buffer_ptr[BLOCK_SIZE];
int counter = 0;
    int currently_writing = 0;

// Read 512 byte blocks into buffer
    while (fread(&buffer_ptr, BLOCK_SIZE, 1, inptr) == 1)
    {
        // If JPEG is found ...
        if (buffer_ptr[0] == 0xff && buffer_ptr[1] == 0xd8 && buffer_ptr[2] == 0xff && (buffer_ptr[3] & 0xf0) == 0xe0)
        {
            // If currently writing an image, close pointer
            if (currently_writing == 1)
            {
                fclose(outptr);
            }
            // Else set currently writing to 1 to indicate new file found
            else
            {
                currently_writing = 1;
            }

// Open a new JPEG file and output pointer to write
            char fileName[8];
            sprintf(fileName, "%03i.jpg", counter);
            outptr = fopen(fileName, "w");
            counter++;
        }

// If new JPEG is found, write buffer to file
        if (currently_writing == 1)
        {
            fwrite(&buffer_ptr, BLOCK_SIZE, 1, outptr);
        }
    };
    
// Close files
    if (outptr == NULL)
    {
        fclose(outptr);
    }
    if (inptr == NULL)
    {
        fclose(inptr);
    }
return 0;
}