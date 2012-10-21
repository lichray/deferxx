/* A stupid example, copies all lines from one file to another. */
#include <err.h>
#define _POSIX_C_SOURCE 200809
#include <stdlib.h>
#include <stdio.h>

#include "defer.h"

static int	 copyfile(FILE *from, FILE *to);

int
main(int argc, char *argv[])
{
	if (argc < 3) {
		fprintf(stderr, "usage: %s FILE1 FILE2\n", argv[0]);
		return 2;
	}

	FILE *fp = fopen(argv[1], "r");
	if (fp == nullptr)
		err(1, "%s", argv[1]);
	defer(fclose(fp));

	FILE *tfp = fopen(argv[2], "wx");
	if (tfp == nullptr)
		err(1, "%s", argv[2]);
	defer(fclose(tfp));

	return copyfile(fp, tfp);
}

static int
copyfile(FILE *from, FILE *to)
{
	char *line = nullptr;
	size_t linecap = 0;
	ssize_t linelen;

	/*
	 * defer() uses a lambda expression to take a reference to the
	 * pointer, so it is safe to free it even it get realloc'ed.
	 */
	defer(free(line));
	while ((linelen = getline(&line, &linecap, from)) > 0)
		if (fwrite(line, linelen, 1, to) < 1)
			return 1;

	return 0;
}
