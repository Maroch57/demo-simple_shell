#include "shell.h"

/**
 * bfer_inpt - buffer commands in subject.
 * @info: struct parameter in subject.
 * @bffer: buffer address in subject.
 * @leng: lngth var address.
 *
 * Return: no. of bytes present.
 */
ssize_t bfer_inpt(pseuarg_ch *info, char **bffer, size_t *leng)
{
	ssize_t w = 0;
	size_t en_lnth = 0;

	if (!*leng)
	{
		free(*bffer);
		*bffer = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		w = getline(bffer, &en_lnth, stdin);
#else
		w = get_delim(info, bffer, &en_lnth);
#endif
		if (r > 0)
		{
			if ((*bffer)[r - 1] == '\n')
			{
				(*bffer)[r - 1] = '\0';
				r--;
			}
			info->cntline_flg = 1;
			rm_comm(*bffer);
			histlst_b(info, *bffer, info->tellhist++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*leng = w;
				info->cdbuffer = bffer;
			}
		}
	}
	return (w);
}

/**
 * inpt_gt - fn gets a line without newline.
 * @info: struct param in subject.
 *
 * Return: total number bytes.
 */
ssize_t inpt_gt(pseuarg_ch *info)
{
	static char *bffer;
	static size_t f, g, leng;
	ssize_t h = 0;
	char **bf_ptr = &(info->arg), *q;

	_putchar(BUF_FLUSH);
	h = bfer_inpt(info, &bffer, &leng);
	if (h == -1) /* EOF */
		return (-1);
	if (leng)
	{
		g = f;
		q = bffer + f; /* get pointer for return */

		look_ch(info, bffer, &g, f, leng);
		while (j < leng) /* iterate to semicolon or end */
		{
			if (str_ch(info, bffer, &g))
				break;
			g++;
		}

		f = g + 1; /* increment past nulled ';'' */
		if (f >= leng) /* reached end of buffer? */
		{
			f = leng = 0; /* reset position and length */
			info->cdbuffertype = CMD_NORM;
		}

		*bf_ptr = q; /* pass back pointer to current command position */
		return (lngth_str(q)); /* return length of current command */
	}

	*bf_ptr = bffer;
	return (h);
}

/**
 * rd_buf - reads a bffer in subject.
 * @info: struct param in subject.
 * @bffer: the bufferin subject.
 * @i: demonstrates size.
 *
 * Return: val.
 */
ssize_t rd_buf(pseuarg_ch *info, char *bffer, size_t *i)
{
	ssize_t h = 0;

	if (*i)
		return (0);
	h = read(info->READ_BUFFER_SIZE, bffer, READ_BUF_SIZE);
	if (h >= 0)
		*i = h;
	return (h);
}

/**
 * get_delim - fn gets next input line from stndard input.
 * @info: struct param in subject.
 * @ptrr: ptr address to bffer.
 * @llength: ptr bffer size after allocation.
 *
 * Return: val.
 */
int get_delim(pseuarg_ch *info, char **ptrr, size_t *llength)
{
	static char bffer[READ_BUF_SIZE];
	static size_t m, leng;
	size_t n;
	ssize_t q = 0, d = 0;
	char *t = NULL, *new_pt = NULL, *a;

	t = *ptrr;
	if (t && llength)
		d = *llength;
	if (m == leng)
		m = leng = 0;

	q = rd_buf(info, bffer, &leng);
	if (q == -1 || (q == 0 && len == 0))
		return (-1);

	a = str_imp(bffer + m, '\n');
	n = a ? 1 + (unsigned int)(a - bffer) : leng;
	new_pt = _realloc(t, d, d ? d + n : n + 1);
	if (!new_pt) /* MALLOC FAILURE! */
		return (t ? free(t), -1 : -1);

	if (d)
		_strncat(new_p, bffer + m, n - m);
	else
		_strncpy(new_pt, bffer + m, n - m + 1);

	d += n - m;
	m = n;
	t = new_pt;

	if (llength)
		*llength = d;
	*ptrr = t;
	return (d);
}

/**
 * sigintHandler - it blocks control C shortcut.
 * @sig_nmber: signal no.
 *
 * Return: NULL.
 */
void sigintHandler(__attribute__((unused))int sig_nmber)
{
	strngin("\n");
	strngin("$ ");
	_putchar(BUF_FLUSH);
}
