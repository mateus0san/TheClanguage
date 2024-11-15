/* Exercise 6-3. Write a cross-referencer that prints a list of all words in a document, and, for each word, a list of the line numbers on which it occurs. Remove noise words like "the," "and," and so on. */
/* I didn't remove noise words... */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXWORD 100

struct lines {
	int line;
	struct lines *next;
};

struct tnode {
	char *word;
	struct lines *listlines;
	struct tnode *left;
	struct tnode *right;
};

int getword(char *, int);
struct tnode *addtree(struct tnode *, char *, int);
void treeprint(struct tnode *);
int main(void)
{
	struct tnode *root;
	char word[MAXWORD];
	int line;
	
	line = 1;
	root = NULL;
	while (getword(word, MAXWORD) != EOF) {
		if (isalpha(word[0]))
			root = addtree(root, word, line);
		else if (strcmp(word, "\n") == 0)
			line++;
	}
	treeprint(root);
	return 0;
}

int getword(char *word, int lim)
{
	int c, getch(void);
	void ungetch(int);
	char *w = word;

	while ((c = getch()) == ' ' || c == '\t')
		;
	if (c != EOF)
		*w++ = c;
	if (!isalpha(c)) {
		*w = '\0';
		return c;
	}
	for ( ; --lim > 0; w++)
		if (!isalnum(*w = getch()))  {
			ungetch(*w);
			break;
		}
	*w = '\0';
	return word[0];
}

#define BUFSIZE 100
int buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if (bufp < BUFSIZE)
		buf[bufp++] = c;
	else
		printf("ungetch: too many characters\n");
}

#include <stdlib.h>

struct lines *addnumber(struct lines *, int actualline);
char *strdupm(char *s);

struct tnode *addtree(struct tnode *p, char *w, int actualline)
{
	int cond;

	if (p == NULL) {
		p = (struct tnode *) malloc(sizeof(struct tnode));
		p->listlines = (struct lines *) malloc(sizeof(struct lines));
		p->left = p->right = NULL;
		p->listlines->next = NULL;
		p->listlines->line = actualline;
		p->word = strdupm(w);
	} else if ((cond = strcmp(w, p->word)) == 0)
		p->listlines = addnumber(p->listlines, actualline);
	else if (cond < 0)
		p->left = addtree(p->left, w, actualline);
	else
		p->right = addtree(p->right, w, actualline);
	return p;
}

char *strdupm(char *s)
{
	char *p;
	
	p = (char *) malloc(strlen(s)+1);
	if (p != NULL)
		strcpy(p, s);
	return p;
}

struct lines *addnumber(struct lines *p, int actualline)
{
	if (p->line < actualline && p->next == NULL) {
		p->next = (struct lines *) malloc(sizeof(struct lines));
		p->next->line = actualline;
		p->next->next = NULL;
	} else if (p->next != NULL)
		p->next = addnumber(p->next, actualline);
	return p;
}

void listprint(struct lines *);

void treeprint(struct tnode *p)
{
	if (p != NULL) {
		treeprint(p->left);
		listprint(p->listlines);
		printf(" %s\n", p->word);
		treeprint(p->right);
	}
}

void listprint(struct lines *p)
{
	if (p != NULL) {
		printf(" %d", p->line);
		listprint(p->next);
	}
}
