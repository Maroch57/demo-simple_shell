#include "shell.h"

/**
 * shellmain - the main loop fn in shell.
 * @info: struct param in subject.
 * @arv: argument vector in subject.
 *
 * Return: 0 if successful, else 1.
 */
int shellmain(pseuarg_ch *info, char **arv)
{
	ssize_t g = 0;
	int builtin_ret = 0;

	while (g != -1 && builtin_ret != -2)
	{
		infclr(info);
		if (actv_int(info))
			strngin("$ ");
		charins(BUFFER_FLUSH);
		g = inpt_gt(info);
		if (g != -1)
		{
			infprs(info, arv);
			builtin_ret = go_emb(info);
			if (builtin_ret == -1)
				loc_comm(info);
		}
		else if (actv_int(info))
			_putchar('\n');
		infree(info, 0);
	}
	write_history(info);
	infree(info, 1);
	if (!actv_int(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->errn == -1)
			exit(info->status);
		exit(info->errn);
	}
	return (builtin_ret);
}

/**
 * go_emb - fn searches for a builtin command.
 * @info: struct param in subject.
 *
 * Return: -1 if builtin command is not found,
 *		0 if successful,
 *		1 if not successful,
 *		-2 if the fn is supposed to exit.
 */
int go_emb(info_t *info)
{
	int g, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", exist_sts},
		{"env", exvar},
		{"help", help_inf},
		{"history", hist_rep},
		{"setenv", good_env},
		{"unsetenv", bad_env},
		{"cd", cd_mine},
		{"alias", alum_hist},
		{NULL, NULL}
	};

	for (g = 0; builtintbl[g].type; g++)
		if (strn_cmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->cnterr++;
			built_in_ret = builtintbl[g].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * loc_comm - responsible for finding a command in a certain path.
 * @info: struct param in subject.
 *
 * Return: NULL.
 */
void loc_comm(pseuarg_ch *info)
{
	char *pth = NULL;
	int l, m;

	info->pth = info->argv[0];
	if (info->cntline_flg == 1)
	{
		info->cnterr++;
		info->cntline_flg = 0;
	}
	for (l = 0, m = 0; info->arg[l]; l++)
		if (!prser(info->arg[l], " \t\n"))
			m++;
	if (!m)
		return;

	pth = locpath(info, pop_env(info, "PATH="), info->argv[0]);
	if (pth)
	{
		info->pth = pth;
		loc_fork(info);
	}
	else
	{
		if ((actv_int(info) || pop_env(info, "PATH=")
			|| info->argv[0][0] == '/') && cmd_prt(info, info->argv[0]))
			loc_fork(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			errorprnt(info, "not found\n");
		}
	}
}

/**
 * loc_fork - enables forking of an executable thread.
 * @info: struct param in subject.
 *
 * Return: void.
 */
void loc_fork(pseuarg_ch *info)
{
	pid_t chld_pid;

	chld_pid = fork();
	if (chld_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (chld_pid == 0)
	{
		if (execve(info->path, info->argv, aqrenv(info)) == -1)
		{
			infree(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				errorprnt(info, "Permission denied\n");
		}
	}
}
