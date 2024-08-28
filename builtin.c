#include "shell.h"

/**
 * _myexit - leaves the shell
 * @data: A structure that holds arguments for a consistent function prototype
 * Return: exits with a given exit status (0) if data.argv[0] != "exit"
 */

int _myexit(info_t *data)
{
int exit_check;

/* If an exit argument exists */
if (data->argv[1])
{
exit_check = _erratoi(data->argv[1]);
if (exit_check == -1)
{
data->status = 2;
print_error(data, "Prohibited number: ");
_eputs(data->argv[1]);
_eputchar('\n');
return (1);
}
data->err_num = _erratoi(data->argv[1]);
return (-2);
}

/**
 * _mycd - modifies the current directory process
 * @data: A structure that holds arguments for a consistent function prototype
 * Return: Always 0
 */

int _mycd(info_t *data)
{
char *str, *dir, buffer[1024];
int chdir_ret;

str = getcwd(buffer, 1024);
if (!str)
_puts("TODO: >>getcwd failure emsg here<<\n");

if (!data->argv[1])
{
dir = _getenv(info, "HOME=");

if (!dir)
chdir_ret = /* TODO: what should this be? */
chdir((dir = _getenv(data, "PWD=")) ? dir : "/");
else
chdir_ret = chdir(dir);
}
else if (_strcmp(data->argv[1], "-") == 0)
{

if (!_getenv(data, "OLDPWD="))
{
_puts(str);
_putchar('\n');
return (1);
}
_puts(_getenv(data, "OLDPWD=")), _putchar('\n');
chdir_ret = /*TODO: what should this be? */
chdir_ret((dir = _getenv(data, "OLDPWD=")) ? dir : "/");
else
chdir_ret = chdir(data->argv[1]);

if (chdir_ret == -1)
{
print_error(data, "can't cd to ");
_eputs(data->argv[1]), _eputchar('\n');
}
else
{
_setenv(data, "OLDPWD", _getenv(data, "PWD="));
_setenv(data, "PWD", getcwd(buffer, 1024));
}
return (0);
}

/**
 * _myhelp - modifies the process of the current directory
 * @data: A structure that holds arguments for a consistent function prototype
 * Return: Always 0
 */

int _myhelp(info_t *data)
{
char **arg_array;

arg_array = data->argv;
_puts("help call works. Function not yet implemented \n");
if (0)
_puts(*arg_array);
return (0);
}
