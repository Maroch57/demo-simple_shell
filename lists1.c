#include "shell.h"

/**
 * lngth_lst - responsible for the length of a linked list.
 * @pr: ptr to first node in a list
 *
 * Return: total size of the list.
 */
size_t lngth_lst(const lst_m *pr)
{
	size_t y = 0;

	while (pr)
	{
		pr = pr->next;
		y++;
	}
	return (y);
}

/**
 * strng_lst - fn returns an array of strings.
 * @phead: ptr to first node in the linked list.
 *
 * Return: an array of strngs.
 */
char **strng_lst(lst_m *phead)
{
	lst_m *node = phead;
	size_t y = lngth_lst(phead), z;
	char **sstrs;
	char *strr;

	if (!phead || !y)
		return (NULL);
	sstrs = malloc(sizeof(char *) * (y + 1));
	if (!sstrs)
		return (NULL);
	for (i = 0; node; node = node->next, y++)
	{
		strr = malloc(lngth_str(node->strr) + 1);
		if (!strr)
		{
			for (z = 0; z < y; z++)
				free(sstrs[z]);
			free(sstrs);
			return (NULL);
		}

		strr = strngcop(strr, node->strr);
		sstrs[y] = strr;
	}
	sstrs[y] = NULL;
	return (sstrs);
}


/**
 * prnt_lst - fn prints all elements of a linked list.
 * @pr: ptr to first element/node in the list.
 *
 * Return: total size of the list in subject.
 */
size_t prnt_lst(const lst_m *pr)
{
	size_t d = 0;

	while (pr)
	{
		strngin(conv_nmber(pr->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		strngin(pr->strng ? pr->strng : "(nil)");
		strngin("\n");
		pr = pr->next;
		d++;
	}
	return (d);
}

/**
 * strt_stng - returns node starting a string.
 * @nod: ptr to head of list.
 * @prefix: string in subject under match.
 * @c: next char after prefix under match.
 *
 * Return: void
 */
lst_m *strng_lst(lst_m *nod, char *prefix, char c)
{
	char *m = NULL;

	while (nod)
	{
		m = at_strt(nod->strng, prefix);
		if (m && ((c == -1) || (*m == c)))
			return (nod);
		nod = nod->next;
	}
	return (NULL);
}

/**
 * indx_gt - responsible for getting the node index.
 * @head: ptr to head of list.
 * @node: the ptr to the node in subject.
 *
 * Return: node index else, -1
 */
ssize_t indx_gt(lst_m *head, lst_m *node)
{
	size_t b = 0;

	while (head)
	{
		if (head == node)
			return (b);
		head = head->next;
		b++;
	}
	return (-1);
}
