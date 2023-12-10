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
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((actv_int(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
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
				print_error(info, "Permission denied\n");
		}
	}
}
