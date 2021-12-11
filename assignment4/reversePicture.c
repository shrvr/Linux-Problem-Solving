#include <stdio.h>
#include <stdlib.h>

unsigned char **image;
char magicNumber[3]; // file type: P5 for binary and P2 for ASCII
int nbLines, nbCols, maxGrayValue;

//rotates the image through data in char pointer image
void rotateImage(FILE *opImage)
{
    fprintf(opImage, "%s\n", magicNumber);
    fprintf(opImage, "%d %d\n", nbLines, nbCols);
    fprintf(opImage, "%d\n", maxGrayValue);
    for (int i = nbLines - 1; i >= 0; i--)
        fwrite(image[i], sizeof(unsigned char), nbCols, opImage);
}

// reads the input file
void readImage(FILE *ipImage)
{
    fscanf(ipImage, "%s", magicNumber);
    fscanf(ipImage, "%d %d", &nbLines, &nbCols);
    fscanf(ipImage, "%d", &maxGrayValue);

    image = malloc(nbLines * sizeof(unsigned char *));
    fgetc(ipImage);

    for (int i = 0; i < nbLines; i++)
    {
        image[i] = malloc(nbCols * sizeof(unsigned char));
        fread(image[i], sizeof(unsigned char), nbCols, ipImage);
    }
}

int main()
{
    FILE *ipImage = fopen("m1.pgm", "rb"); //input file

    // exits if the file does not exist
    if (ipImage == NULL)
    {
        printf("File does not exist\n");
        return 1;
    }

    FILE *opImage = fopen("m1_rotated.pgm", "w+"); //output file

    readImage(ipImage);   // reads the file and set the global variables
    rotateImage(opImage); //rotates the image data stored in **image pointer

    //file closing
    fclose(ipImage);
    fclose(opImage);
    return 0;
}