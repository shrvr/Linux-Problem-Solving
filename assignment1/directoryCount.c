#define _XOPEN_SOURCE 500
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>

int count = -1; // to avoid count of . and argument passed directory

static int directory_count(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf)
{
	if (typeflag == FTW_D || typeflag == FTW_DNR)
		count++; // increase the count if the visited node is directory
	return 0;
}

int main(int argc, char *argv[])
{
	int flags = FTW_CHDIR;

	if (nftw((argc < 2) ? "." : argv[1], directory_count, 10, flags) == -1)
	{
		perror("nftw");
		exit(EXIT_FAILURE);
	}
	printf("Directory count: %d\n", count);
	exit(EXIT_SUCCESS);
}
