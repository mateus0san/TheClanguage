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
#define MAXLINE 10000
void filecmp(FILE *fp1, FILE *fp2, FILE *fo)
{
	int c1, c2, i;
	char line1[MAXLINE];
	char line2[MAXLINE];

	for (i = 0; i < MAXLINE; i++) {
		if ((line1[i] = c1 = getc(fp1)) != (line2[i] = c2 = getc(fp2)))
			break;
		if (c1 == '\n' && c2 == '\n'){
			i = -1;
			line1[0] = '\0';
			line2[0] = '\0';
			continue;
		}
	}
	if (i >= MAXLINE) {
		printf("line too big\n");
		exit(4);
	}
	line1[i+1] = '\0';
	line2[i+1] = '\0';
	if (c1 != c2) {
		fprintf(fo, "%s", line1);
		while ((c1 = getc(fp1)) != EOF && c1 != '\n')
			putc(c1, fo);
		fprintf(fo, "\n%s", line2);
		while ((c2 = getc(fp2)) != EOF && c2 != '\n')
			putc(c2, fo);
		putc('\n', fo);
	}
}
