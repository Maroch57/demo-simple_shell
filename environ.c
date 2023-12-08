#include "shell.h"

/**
 * myown_env - ensures current environment is printed.
 * @info: struct contains potential constant fn prototype.
 * Return: 0
 */
int myown_env(pseuarg_ch *info)
{
	lststr_prnt(info->exvar);
	return (0);
}

/**
 * pop_env - fn gets environment variable values.
 * @info: struct of arguments in use.
 * @vname: variable name on env in subject.
 *
 * Return: value.
 */
char *pop_env(pseuarg_ch *info, const char *vname)
{
	lst_m *node = info->exvar;
	char *k;

	while (node)
	{
		k = at_strt(node->strng, vname);
		if (k && *k)
			return (k);
		node = node->next;
	}
	return (NULL);
}

/**
 * good_env - configs/modif new environment variables.
 * @info: struct containing potential arg prototypes.
 *  Return: 0
 */
int good_env(pseuarg_ch *info)
{
	if (info->argc != 3)
	{
		putide("Incorrect number of arguements\n");
		return (1);
	}
	if (ptenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * bad_env - eliminates/removes an env var.
 * @info: struct containing potential arg prototype.
 *  Return: 0
 */
int bad_env(pseuarg_ch *info)
{
	int d;

	if (info->argc == 1)
	{
		putide("Too few arguements.\n");
		return (1);
	}
	for (d = 1; d <= info->argc; d++)
		bad_env(info, info->argv[d]);

	return (0);
}

/**
 * fill_env - adds to an environmnt lst.
 * @info: struct contains potential arg prototypes.
 * Return: 0
 */
int fill_env(pseuarg_ch *info)
{
	lst_m *node = NULL;
	size_t d;

	for (d = 0; envirn[d]; i++)
		endnode_add(&node, envirn[d], 0);
	info->exvar = node;
	return (0);
}
