#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{

    if (argc != 2)
    {

        printf("1 parameter only\n");
        return 1;

    }

    if (argv[1] == NULL)
    {

        printf("Missing file parameter\n");
        return 1;

    }

    FILE *inputfile = fopen(argv[1], "r");
    if (inputfile == NULL)
    {

        printf("Cannot open file\n");
        return 2;

    }

    //point output file to nothing
    FILE *outputfile = NULL;

    //declare counter for file name
    int counter = 0;

    //declare type BYTE as unsigned 8 bit int. This is 1 BYTE of data
    typedef uint8_t BYTE;

    //declare space for 512 byte long buffer. This is 1 BLOCK of data
    BYTE buffer[512];
    char *filename = (char *)malloc(sizeof(char) * 8);

    //read from file and write to buffer a 512 block of code
    while (fread(&buffer, 512, 1, inputfile))
    {

        //if header found
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ((buffer[3] & 0xf0) == 0xe0))
        {

            //if there is a previous image, close file
            if (counter != 0)
            {

                fclose(outputfile);

            }

            //start new file
            sprintf(filename, "%03i.jpg", counter);
            outputfile = fopen(filename, "w");
            counter ++;
        }

        //only writes if at least 1 file is found
        if (counter != 0)
        {

            //continue writing to existing file
            fwrite(&buffer, 512, 1, outputfile);

        }

    }

    //clean it up janny
    free(filename);
    fclose(inputfile);
    fclose(outputfile);

    return 0;

}