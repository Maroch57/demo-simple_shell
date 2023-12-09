#include "shell.h"

/**
 * strngcop - fn used to copy a string.
 * @destn: destination in subject.
 * @srce: the source in subject.
 *
 * Return: a ptr to destination.
 */
char *strngcop(char *destn, char *srce)
{
	int h = 0;

	if (destn == srce || srce == 0)
		return (destn);
	while (srce[h])
	{
		destn[h] = srce[h];
		h++;
	}
	destn[h] = 0;
	return (destn);
}

/**
 * strngclone - fn duplicates a strng.
 * @strr: strng under duplication.
 *
 * Return: a ptr to the duplicated strng.
 */
char *strngclone(const char *strr)
{
	int lngth = 0;
	char *retn;

	if (strr == NULL)
		return (NULL);
	while (*strr++)
		length++;
	retn = malloc(sizeof(char) * (lngth + 1));
	if (!retn)
		return (NULL);
	for (lngth++; lngth--;)
		retn[lngth] = *--strr;
	return (retn);
}

/**
 *strngin - ensures an input string is printed.
 *@sstr: printed strng.
 *
 * Return: void.
 */
void strngin(char *sstr)
{
	int n = 0;

	if (!sstr)
		return;
	while (sstr[n] != '\0')
	{
		_putchar(sstr[n]);
		n++;
	}
}

/**
 * _putchar - fn writes a char c to standard output console.
 * @c: char to be printed.
 *
 * Return: if successful 1 else, 0.
 */
int _putchar(char c)
{
	static int k;
	static char buf[WRITE_BUFFER_SIZE];

	if (k == BUFFER_FLUSH || k >= WRITE_BUFFER_SIZE)
	{
		write(1, buf, k);
		i = 0;
	}
	if (c != BUFFER_FLUSH)
		buf[k++] = c;
	return (1);
}
