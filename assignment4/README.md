# Assignment 4

## Problem:

Using Unix I/O system calls(read(), write(), lseek(),...), write a C program, called reversePicture, to transform a given picture into an up-side-down picture. In particular, your program should reverse the image by directly reading from one file and writing to another file, without the need of a two-dimensional array.

The input image is a gray-scale picture, where each pixel has a value between 0(black) and 255(white). The image is simply an nbLines × nbCols matrix of bytes, where each byte store the gray-level of the corresponding pixel.

nbLines is the number of lines and nbCols is the number of columns.

To help you understand the structure of the binary file containing the image, here is the function that was used to store the image in a file.

```c
void saveImage(char **image, int nbLines, int nbCols, FILE *fd){
    int i;
    fputs("P5\n", fd); // just a code
    fprintf(fd, "%d %d\n", nbLines, nbCols);
    fputs("255\n", fd); // another code
    for(i=0; i<nbLines; i++)
        fwrite(image[i], nbCols, fd);
}
```

**Notes :**
The image(the input file to your program) is in the same folder.
Many image reader can be used to view your images (input and output). You can, for example, use the UltraFileOpener that can be downloaded from http://www.ultrafileopener.com.