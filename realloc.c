#include "shell.h"

/**
 **mmry_arn - responsible for populating the memory.
 *@r: ptr to memory.
 *@p: reponsible byte for populating the memory.
 *@m: no. bytes to be populated.
 *Return: ptr to the memory.
 */
char *mmry_arn(char *r, char p, unsigned int m)
{
	unsigned int l;

	for (l = 0; l < m; l++)
		r[l] = p;
	return (r);
}

/**
 * dmfree - responsible for freeing a string of strings.
 * @ss: the string of stringsin subject.
 */
void dmfree(char **ss)
{
	char **g = ss;

	if (!ss)
		return;
	while (*ss)
		free(*ss++);
	free(g);
}

/**
 * mem_ralloc - responsible for allocating a block of memory.
 * @pptr: ptr to memory allocated block.
 * @init_size: initial size of a block of memory.
 * @curr_size: size of the new mem allocated block.
 *
 * Return: a ptr to the memory block.
 */
void *mem_ralloc(void *pptr, unsigned int init_size, unsigned int curr_size)
{
	char *t;

	if (!pptr)
		return (malloc(curr_size));
	if (!curr_size)
		return (free(pptr), NULL);
	if (curr_size == init_size)
		return (pptr);

	t = malloc(curr_size);
	if (!t)
		return (NULL);

	init_size = init_size < curr_size ? init_size : curr_size;
	while (init_size--)
		t[init_size] = ((char *)pptr)[init_size];
	free(pptr);
	return (t);
}
