# Assignment 3

## Problem:

Read the manual of command find then write a Bash script, call it myArchive, to move all files, in a directory hierarchy, with specific extensions to a target directory.

Synopsis:
```bash
$myArchive [-t targetDir] [-a arcDir] <extension-list>.
```

myArchive should use command find to visit each file in the hierarchy, given by root directory targetDir, and if their extensions are in extension-list, the files are moved to arcDir.

In particular :
* When arcDir is missing, then directory archiveDirectory should be created in current directory.
* When target-directory is missing, then current directory should be used as target directory.
* You script should check if target-directory exists and if it has write permission. Otherwise, your script should exit with an error message.
* The option arguments of the script can be in any order. For example,
```bash
$myArchive [-a arcDir] [-t targetDir] <extension-list>.
```
or
```bash
$myArchive [-t targetDir] [-a arcDir] <extension-list>
```

Some sample runs:

#### Case 1:
```bash
$myArchive -a ∼/safe pdf doc
```
Script searches all files whose extensions are either pdf or doc in the whole directory hierarchy (whose root is ./), create ∼/safe if it does not exist already, then moves all these files to ∼/safe.

#### Case 2:
```bash
$myArchive pdf doc txt
```
Script searches all files whose extensions are either pdf, doc or txt in the whole directory hierarchy (whose root is ./ , creates archiveDirectory then moves all these files to it.

#### Case 3:
```bash
$myArchive -a ∼/safe -t oldFiles pdf
```
Script searches all files whose extension is pdf in the whole directory hierarchy (whose root is ./oldFiles), create ∼ safe if it does not exist already, then moves all these files to ∼/safe.

**Hint:** you can use getopts Linux built-in function to parse command line arguments of your script.