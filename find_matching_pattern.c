#include <stdio.h>
#define MAXLINE 1000

int getline2(char line[], int max);
int strindex(char source[], char searchfor[]);

char pattern[] = "here";

int main()
{
  char line[MAXLINE];
  int found = 0;

  while (getline2(line, MAXLINE) > 0)
  {
    if (strindex(line, pattern) >= 0)
      printf("%s", line);
    found++;
  }
  return found;
}

/* 
  get line into s, return the length
*/
int getline2(char s[], int lim)
{
  int c, i;
  i = 0;

  while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
    s[i++] = c;
  if (c == '\n')
    s[i++] = c;
  s[i] = '\0';
  return i;
}

/* 
  return index of t in s, -1 if none
*/
int strindex(char s[], char t[])
{
  int i, j, k;
  for (i = 0; s[i] != EOF; i++)
  {
    for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
      ;
    if (k > 0 && t[k] == '\0')
      return i;
  }
  return -1;
}