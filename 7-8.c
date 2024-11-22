/* Write a program to print a set of files, starting each new one on a new page, with a title and a running page count for each file. */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	FILE *fp;
	void filecopy(FILE *, FILE *);
	char *prog = *argv;
	int page = 1;


	if (argc < 2) {
		fprintf(stderr, "%s: need at least one file\n", prog);
		exit(0);
	} else
		while (--argc > 0)
			if ((fp = fopen(*++argv, "r")) == NULL) {
				fprintf(stderr, "%s: can't open %s\n", prog, *argv);
				exit(2);
			} else {
				fprintf(stdout, "\n\n%50s\n%50d\n\n", *argv, page++);
				filecopy(fp, stdout);
			}
			if (ferror(stdout)) {
				fprintf(stderr, "%s: error writing stdout\n", prog);
				exit(3);
			}
		exit(0);
}

void filecopy(FILE *fp, FILE *of)
{
	int c;

	while ((c = getc(fp)) != EOF)
		putc(c, of);
}
