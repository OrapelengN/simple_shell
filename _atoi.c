#include "shell.h"

/**
 * inter_mode - when in interactive mode, shell is to return true
 * @data: address for the struct
 *
 * Return: 1 if in interactive mode, 0 if not
 */

int inter_mode(info_t *data)
{
return (isatty(STDIN_FILENO) && data->readfd <= 2);
}

/**
 * is_delim - determine if the char is part of a predefined set of delimeters
 * @sym: the character to be checked
 * @delim_s: the delimeter string
 * Return: 1 if it is true, 0 if it is false
 */

int is_delim(char sym, char *delim_s)
{
while (*delim_s)
if (*delim_s++ == sym)
{
return (1);
}
return (0);
}

/**
 * _isalpha - checks to determine if the characters are alphabetic characters
 * @sym: The character to input
 * Return: 1 if c is alphabetic, 0 if it is not
 */

int _isalpha(int sym)
{
if ((sym >= 'a' && sym <= 'z') || (sym >= 'A' && sym <= 'Z'))
return (1);
else
return (0);
}

/**
 * _atoi - converts a string to an integer
 * @str: the string to convert
 * Return: 0 if no numbers in the string, otherwise if converted number
 */

int _atoi(char *str)
{
int i, sign = 1, flag = 0, output;
unsigned int result = 0;

for (i = 0; str[i] != '\0' && flag != 2; i++)
{
if (str[i] == '-')
sign *= -1;

if (str[i] >= '0' && str[i] <= '9')
{
flag = 1;
result *= 10;
result += (str[i] - '0');
}
else if (flag == 1)
flag = 2;
}

if (sign == -1)
output = -result;
else
output = result;

return (output);
}
