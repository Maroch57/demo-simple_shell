#include "shell.h"

/**
 * infclr - it initializes pseuarg_ch struct.
 * @info: it is the address of struct.
 */
void infclr(pseuarg_ch *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->way = NULL;
	info->argc = 0;
}

/**
 * infprs - it initializes pseuarg_ch struct.
 * @info: it is the address of struct.
 * @arv: the arg vector.
 */
void infprs(pseuarg_ch *info, char **arv)
{
	int z = 0;

	info->progname = arv[0];
	if (info->arg)
	{
		info->argv = mod_strng(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = strngclone(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (z = 0; info->argv && info->argv[z]; z++)
			;
		info->argc = z;

		rp_alias(info);
		rp_vstr(info);
	}
}

/**
 * infree - fn handles freeing of pseuarg_ch struct fields.
 * @info: it is the address of struct.
 * @fldall: becomes true if all fields are freed.
 */
void infree(pseuarg_ch *info, int fldall)
{
	dmfree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (fdall)
	{
		if (!info->cdbuffer)
			free(info->arg);
		if (info->exvar)
			freelst(&(info->exvar));
		if (info->hst)
			freelst(&(info->hst));
		if (info->fake)
			freelst(&(info->fake));
		dmfree(info->environ);
			info->environ = NULL;
		mem_free((void **)info->cdbuffer);
		if (info->READ_BUFFER_SIZE > 2)
			close(info->READ_BUFFER_SIZE);
		_putchar(BUFFER_FLUSH);
	}
}
