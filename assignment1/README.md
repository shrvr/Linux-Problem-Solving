# Assignment 1

## Problem:

Write a C program, call it directoryCount, to count the number of sub-directories (excluding . and ..) in a given directory then, prints that number on the screen.

In particular, you should read the manual entry of system call nftw() then, use it to walk across a directory tree. This system call will do all the recursive walk for you and, each time it visits a file or a directory, it will call your own function (a function that you pass as a parameter to nftw()).

Synopsis: directoryCount < targetDirectory >

Call examples:
```bash
$directoryCount
```
counts number of sub-directories in current directory.

```bash
$directoryCount /bin
```
counts number of sub-directories in /bin.

Important: your program must use system call nftw()
and avoid explicit recursive calls.