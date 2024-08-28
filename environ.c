#include "shell.h"

/**
 * _myenv - displays the current environment
 * @data: A structure that stores arguments for a consistent function prototype
 * Return: Always 0
 */

int _myenv(info_t *data)
{
print_list_str(data->env);
return (0);
}

/**
 * _getenv - collects the value of an environ variable
 * @data: A structure that stores arguments for a consistent function prototype
 * @name: environ variable name
 *
 * Return: the value
 */

char *_getenv(info_t *data, const char *name)
{
list_t *node = info->env;
char *p;

while (node)
{
p = starts_with(node->str, name);
if (p && *p)
return (p);
node = node->next;
}
return (NULL);
}

/**
 * _mysetenv - variable initialization or modification of an existing variable
 * @data: A structure that stores arguments for a consistent function prototype
 * Return: Always 0
 */

int _mysetenv(info_t *data)
{
if (data->argc != 3)
{
_eputs("Wrong number of arguments\n");
return (1);
}
if (_setenv(data, data->argv[1], data->argv[2]))
return (0);
return (1);
}

/**
 * _myunsetenv - Remove an environment variable
 * @data: A structure that stores arguments for a consistent function prototype
 * Return: Always 0
 */

int _myunsetenv(info_t *data)
{
int i;

if (data->argc == 1)
{
_eputs("Too few arguments.\n");
return (1);
}
for (i = 1; i <= data->argc; i++)
_unsetenv(data, data->argv[i]);

return (0);
}

/**
 * populate_env_list - fills the linked list of environ
 * @data: A structure that stores arguments for a consistent function prototype
 * Return: Always 0
 */

int populate_env_list(info_t *data)
{
list_t *node = NULL;
size_t i;

for (i = 0; environ[i]; i++)
add_node_end(&node, environ[i], 0);
data->env = node;
return (0);
}
