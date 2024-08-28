#include "shell.h"

/**
 * get_environ - returns a string array copy of my environ
 * @data: structure containing arguments for maintaining function prototype
 * Return: Always 0
 */

char **get_environ(info_t *data)
{
if (!data->environ || data->env_changed)
{
data->environ = list_to_strings(data->env);
data->env_changed = 0;
}

return (data->environ);
}

/**
 * _unsetenv - deletes an environment variable
 * @data: structure containing arguments for maintaining function prototype
 * Return: 1 on delete, 0 if not deleting
 * @var: the string env var property
 */

int _unsetenv(info_t *data, char *var)
{
list_t *node = data->env;
size_t i = 0;
char *p;

if (!node || !var)
return (0);

while (node)
{
p = starts_with(node->str, var);
if (p && *p == '=')
{
data->env_changed = delete_node_at_index(&(data->env), i);
i = 0;
node = data->env;
continue;
}
node = node->next;
i++;
}
return (data->env_changed);
}

/**
 * _setenv - create a new environment variable or modify an existing one
 * @data: structure containing arguments for maintaining function prototype
 * @var: the string env var property
 * @value: the string env var value
 * Return: Always 0
 */

int _setenv(info_t *data, char *var, char *value)
{
char *buf = NULL;
list_t *node;
char *p;

if (!var || !value)
return (0);

buf = malloc(_strlen(var) + _strlen(value) + 2);
if (!buf)
return (1);
_strcpy(buf, var);
_strcat(buf, "=");
_strcat(buf, value);
node = data->env;
while (node)
{
p = starts_with(node->str, var);
if (p && *p == '=')
{
free(node->str);
node->str = buf;
data->env_changed = 1;
return (0);
}
node = node->next;
}
add_node_end(&(data->env), buf, 0);
free(buf);
data->env_changed = 1;
return (0);
}
