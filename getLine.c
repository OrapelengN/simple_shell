#include "shell.h"

/**
 * input_buf - buffers sequential commands
 * @data: parameter struct
 * @buf: buffers location
 * @len: len var location
 *
 * Return: the bytes that have been read
 */

ssize_t input_buf(info_t *data, char **buf, size_t *len)
{
ssize_t r = 0;
size_t len_p = 0;

if (!*len) /* Fill buffer if nothing is left in it */
{
free(*buf);
*buf = NULL;
signal(SIGINT, sigintHandler);
#if USE_GETLINE
r = getline(buf, &len_p, stdin);
#else
r = _getline(data, buf, &len_p);
#endif
if (r > 0)
{
if ((*buf)[r - 1] == '\n')
{
(*buf)[r - 1] = '\0'; /*remove trailing newline */
r--;
}
data->linecount_flag = 1;
remove_comments(*buf);
build_history_list(data, *buf, data->histcount++);
/*if (_strchr(*buf, ';')) is this a command chain? */
{
*len = r;
data->cmd_buf = buf;
}
}
}
return (r);
}

/**
 * get_input - gets a line minus the newline
 * @data: parameter struct
 *
 * Return: the bytes that are read
 */

ssize_t get_input(info_t *data)
{
static char *buf; /* the ';' command chain buffer */
static size_t i, j, len;
ssize_t r = 0;
char **buf_p = &(data->arg), *p;

_putchar(BUF_FLUSH);
r = input_buf(data, &buf, &len);
if (r == -1) /* EOF */
return (-1);
if (len) /* we have commands left in the chain buffer */
{
j = i; /* init new iterator to current buf position */
p = buf + i; /* get pointer for return */

check_chain(data, buf, &j, i, len);
while (j < len) /* iterate to semicolon or end */
{
if (is_chain(data, buf, &j))
break;
j++;
}

i = j + i; /* increment past nulled ';'' */
if (i >= len) /* reached end of buffer? */
{
i = len = 0; /* reset position and length */
data->cmd_buf_type = CMD_NORM;
}

*buf_p = p; /* pass back pointer to current command position */
return (_strlen(p)); /* return length of current command */
}

*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
return (r); /* return length of buffer from _getline() */
}

/**
 * read_buf - reads a buffer
 * @data: parameter struct
 * @buf: the buffer
 * @i: the size
 *
 * Return: r
 */

ssize_t read_buf(info_t *data, char *buf, size_t *i)
{
ssize_t r = 0;

if (*i)
return (0);
r = read(data->readfd, buf, READ_BUF_SIZE);
if (r >= 0)
*i = r;
return (r);
}

/**
 * _getline - gets the next line of input from STDIN
 * @data: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */

int _getline(info_t *data, char **ptr, size_t *length)
{
static char buf[READ_BUF_SIZE];
static size_t i, len;
size_t k;
ssize_t r = 0, s = 0;
char *p = NULL, *new_p = NULL, *c;

p = *ptr;
if (p && length)
s = *length;
if (i == len)
i = len = 0;

r = read_buf(data, buf, &len);
if (r == -1 || (r == 0 && len == 0))
return (-1);

c = _strchr(buf + i, '\n');
k = c ? 1 + (insigned int)(c - buf) : len;
new_p = _realloc(p, s, s ? s + k : k + 1);
if (!new_p) /* MALLOC FAILURE! */
return (p ? free(p), -1 : -1);

if (s)
_strncat(new_p, buf + i, k - i);
else
_strncat(new_p, buf + i, k - i + 1);

s += k - i;
i = k;
p = new_p;

if (length)
*length = s;
*ptr = p;
return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */

void sigintHandler(__attrubute__((unused))int sig_num)
{
_puts("\n");
_puts("$ ");
_putchar(BUF_FLUSH);
}
