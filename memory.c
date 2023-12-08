#include "shell.h"

/**
 * mem_free - fn frees a pointer and makes it addrss NULL.
 * @pttr: addrss of ptr to be freed.
 *
 * Return: 1 if successful, else 0.
 */
int mem_free(void **pttr)
{
	if (pttr && *pttr)
	{
		free(*pttr);
		*pttr = NULL;
		return (1);
	}
	return (0);
}
