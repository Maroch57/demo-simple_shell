#include "shell.h"

/**
 * exst_err - transforms strng to int.
 * @s: strng under transformation.
 * Return: 0 if successful, else -1
 */
int exst_err(char *s)
{
	int u = 0;
	unsigned long int rslt = 0;

	if (*u == '+')
		u++;  /* TODO: why does this make main return 255? */
	for (u = 0;  s[u] != '\0'; u++)
	{
		if (s[u] >= '0' && s[u] <= '9')
		{
			rslt *= 10;
			rslt += (s[u] - '0');
			if (rslt > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (rslt);
}

/**
 * errorprnt - prnts error mssage as output.
 * @info: struct return information.
 * @errstrng: string with a certain error.
 * Return: 0 if successful, else -1
 */
void errorprnt(pseuarg_ch *info, char *errstrng)
{
	putide(info->progname);
	putide(": ");
	disprnt(info->cnterr, STDERR_FILENO);
	putide(": ");
	putide(info->argv[0]);
	putide(": ");
	putide(errstrng);
}

/**
 * disprnt - fn prnts an int no. to base 10.
 * @inpt: input in subject.
 * @fd: file descriptor to be written to.
 *
 * Return: total no. of chars prnted.
 */
int disprnt(int inpt, int fd)
{
	int (*__putchar)(char) = _putchar;
	int u, ccount = 0;
	unsigned int bs_arr, currnt;

	if (fd == STDERR_FILENO)
		__putchar = charins;
	if (inpt < 0)
	{
		bs_arr = -inpt;
		__putchar('-');
		ccount++;
	}
	else
		bs_arr = inpt;
	currnt = bs_arr;
	for (u = 1000000000; u > 1; u /= 10)
	{
		if (bs_arr / u)
		{
			__putchar('0' + currnt / u);
			ccount++;
		}
		currnt %= u;
	}
	__putchar('0' + currnt);
	ccount++;

	return (ccount);
}

/**
 * conv_nmber - fn that converts.
 * @numb: the number in subject.
 * @base_s: the base in subject.
 * @flags: arg flags in subject.
 *
 * Return: a string of chars.
 */
char *conv_nmber(long int numb, int base_s, int flags)
{
	static char *arr;
	static char bffer[50];
	char indic = 0;
	char *pter;
	unsigned long m = numb;

	if (!(flags & CONVERT_UNSIGNED) && numb < 0)
	{
		m = -numb;
		indic = '-';

	}
	arr = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	pter = &bffer[49];
	*pter = '\0';

	do	{
		*--pter = arr[m % base_s];
		m /= base_s;
	} while (m != 0);

	if (indic)
		*--pter = indic;
	return (pter);
}

/**
 * rm_comm - fn replaces first instance of '#' with null terminator..
 * @bufff: the address of string under modification.
 *
 * Return: 0
 */
void rm_comm(char *bufff)
{
	int r;

	for (r = 0; bufff[r] != '\0'; r++)
		if (bufff[r] == '#' && (!r || bufff[r - 1] == ' '))
		{
			bufff[r] = '\0';
			break;
		}
}
