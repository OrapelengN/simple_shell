exits.c

#include "shell.h"

/**
 * *_strncpy - duplicates a string
 * @dest: the destination string for copying
 * @src: the source string
 * @num: the number of characters to copy
 * Return: the string that is concatenated
 */

char *_strncpy(char *dest, char *src, int num)
{
int i, j;
char *s = dest;

i = 0;
while (src[i] != '\0' && i < num - 1)
{
dest[i] = src[i];
i++;
}
if (i < num)
{
j = i;
while (j < num)
{
dest[j] = '\0';
j++;
}
return (s);
}

/**
 * *_strncat - combines two strings
 * @dest: the first string
 * @src: the second string
 * @num: The maximum number of bytes to use
 * Return: the string that is concatenated
 */

char *_strncat(char *dest, char *src, int num)
{
int i, j;
char *s = dest;

i = 0;
j = 0;
while (dest[i] != '\0')
i++;
while (src[j] != '\0' && j < num)
{
dest[i] = src[j];
i++;
j++;
}
if (j < num)
dest[i] = '\0';
return (s);
}

/**
 * *_strchr - finds a character in a string
 * @str: the string to parse
 * @ch: the character to find
 * Return: (str) a pointer to the memory area str
 */

char *_strchr(char *str, char ch)
{
do {
if (*str == ch)
return (str);
} while (*str++ != '\0');

return (NULL);
}
