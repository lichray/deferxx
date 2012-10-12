/* A stupid example, prints all lines in a file. */
#define _POSIX_C_SOURCE 200809
#include <stdlib.h>
#include <stdio.h>

#include "defer.h"

int main(int argc, char *argv[]) {
	if (argc < 2) {
		fprintf(stderr, "Usage: %s FILE\n", argv[0]);
		return 1;
	}

	FILE *fp = fopen(argv[1], "r");

	/* It's invalid to fclose(NULL). */
	if (fp == nullptr) {
		perror(argv[0]);
		return 1;
	}
	defer([=]{ fclose(fp); });

	char *line = nullptr;
	size_t linecap = 0;
	ssize_t linelen;

	/*
	 * It's valid to free(NULL). And, by taking a reference to the
	 * pointer, we can free it even it got realloc'ed!
	 */
	defer([&]{ free(line); });
	while ((linelen = getline(&line, &linecap, fp)) > 0)
		fwrite(line, linelen, 1, stdout);

	return 0;
}
