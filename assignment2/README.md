# Assignment 2

## Problem:

Write a Bash script that uses the tar utility (read manual) to separately tar every directory (only directories are tarred) in a target directory. The name of each tarred directory should be dirNameTodayDate.tar.

Example, if a directory name is pictures and today date is October 1, 2021, the tar file should be picturesOct012021.tar.

You can use command date to help construct the name.

When all directories are tarred, they should be moved to the archive directory given as an argument.

Synopsis:
```bash
$tarDirs [-t target-directory] <-a archive-directory>
```

The directories to be tarred are located in the targetdirectory. When the latter is missing, the current working directory is the target directory. Note that the script arguments can be in any order, it can also be called as
```bash
$tarDirs <-a archive-directory> [-t target-directory]
```

Your script should print the correct syntax for the call when the user does not follow the right syntax.

Some sample runs:

#### Case 1: tar from current directory
```bash
$tarDirs -a ∼/myArchive
```
Script tars each directory in current directory then move
all of them to ∼/myArchive (∼ is home directory).

#### Case 2: tar from a target-directory.
```bash
$tarDirs -a myArchive -t /home/users/bigFoot/
```
Script tars each directory in /home/users/bigFoot/ then
move all of them to ./myArchive