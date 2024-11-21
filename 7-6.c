/* Write a program to compare two files, printing the first line where they differ. */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	FILE *fp1, *fp2;
	void filecmp(FILE *, FILE *, FILE *);
	char *prog = argv[0];

	if (argc < 3) {
		fprintf(stderr, "this program needs at least to files\n");
		exit(1);
	} else {
		if ((fp1 = fopen(*++argv, "r")) == NULL) {
			fprintf(stderr, "%s: can't open %s\n", prog, *argv);
			exit(2);
		}
		if ((fp2 = fopen(*++argv, "r")) == NULL) {
			fprintf(stderr, "%s: can't open %s\n", prog, *argv);
			exit(2);
		}
		filecmp(fp1, fp2, stdout);
		if (ferror(stdout)) {
			fprintf(stderr, "%s: error writing stdout\n", prog);
			exit(3);
		}
	}
	exit(0);
}

void filecmp(FILE *fp1, FILE *fp2, FILE *fo)
{
	FILE *faux1, *faux2;
	int c1, c2;

	faux1 = fp1;
	faux2 = fp2;
	c1 = fgetc(fp1);
	c2 = fgetc(fp2);
	while (c1 == c2) {
		if (c1 == EOF && c2 == EOF)
			break;
		if (c1 == '\n' && c2 == '\n') {
			faux1 = fp1;
			faux2 = fp2;
		}
		c1 = fgetc(fp1);
		c2 = fgetc(fp2);
	}
	if (c1 != c2){
		for (c1 = fgetc(faux1); c1 != '\n' && c1 != EOF; c1 = fgetc(faux1))
			putc(c1, fo);
		printf("\n");
		for (c2 = fgetc(faux2); c2 != '\n' && c2 != EOF; c2 = fgetc(faux2))
			putc(c2, fo);
		printf("\n");
	}
}
