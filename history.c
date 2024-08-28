#include "shell.h"

/**
 * get_history_file - gets the file of the history
 * @data: parameter struct
 *
 * Return: the string containing history file
 */

char *get_history_file(info_t *data)
{
char *buf, *dir;

dir = _getenv(data, "HOME=");
if (!dir)
return (NULL);
buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
if (!buf)
return (NULL);
buf[0] = 0;
_strcpy(buf, dir);
_strcat(buf, "/");
_strcat(buf, HIST_FILE);
return (buf);
}

/**
 * write_history - creates a file, or modifies an existing file
 * @data: the parameter struct
 *
 * Return: 1 on success, else -1
 */

int write_history(info_t *data)
{
ssize_t fd;
char *filename = get_history_file(data);
list_t *node = NULL;

if (!filename)
return (-1);

fd = open(filename, o_CREAT | O_TRUNC | O_RDWR, 0644);
free(filename);
if (fd == -1)
return (-1);
for (node = data->history; node; node = node->next)
{
_putsfd(node->str, fd);
_putfd('\n', fd);
}
_putfd(BUF_FLUSH, fd);
close(fd);
return (1);
}

/**
 * read_history - reads the file to get the history
 * @data: the parameter struct
 *
 * Return: history count on success, else 0
 */

int read_history(info_t *data)
{
int i, last = 0, lcount = 0;
ssize_t fd, rdlen, fsize = 0;
struct stat st;
char *buf = NULL, *filename = get_history_file(data);

if (!filename)
return (0);

fd = open(filename, O_RDONLY);
free(filename);
if (fd == -1)
return (0);
if (!fstat(fd, &st))
fsize = st.st_size;
if (fsize < 2)
return (0);
buf = malloc(sizeof(char) * (fsize + 1));
if (!buf)
return (0);
rdlen = read(fd, buf, fsize);
buf[fsize] = 0;
if rdlen <= 0)
return (free(buf), 0);
close(fd);
for (i = 0; i < fsize; i++)
if (buf[i] == '\n')
{
buf[i] = 0;
build_history_list(data, buf + last, lcount++);
last = i + 1;
}
if (last != i)
build_history_list(data, buf + last, lcount++);
free(buf);
data->histcount = lcount;
while (data->histcount-- >= HIST_MAX)
delete_node_at_index(&(data->history), 0);
renumber_history(data);
return (data->histcount);
}

/**
 * build_history_list - adds entry to a history linked list
 * @data: structure containing arguments for maintaining function prototype
 * @buf: the buffer
 * @lcount: histcount, the linecount of the history
 *
 * Return: Always 0
 */

int build_history_list(info_t *data, char *buf, int lcount)
{
list_t *node = NULL;

if (data->history)
node = data->history;
add_node_end(&node, buf, lcount);

if (!data->history)
data->history = node;
return (0);
}

/**
 * renumber_history - after changes, it renumbers the history linked list
 * @data: structure containing arguments for maintaining function prototype
 *
 * Return: the new history count
 */

int renumber_history(info_t *data)
{
list_t *node = data->history;
int i = 0;

while (node)
{
node->num = i++;
node = node->next;
}
return (data->histcount = i);
}
