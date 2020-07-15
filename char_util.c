#include <stdio.h>

/* 
  copy input to output
*/
void copy_io()
{
  int c;
  while ((c = getchar()) != EOF)
    putchar(c);
}

/*
  char counting
*/
int count_char_io(char *str)
{
  double nc;
  for (nc = 0; *str++ != 0; ++nc)
  {
    ;
  }
  printf("%.0f\n", nc);
  return nc;
}

/*
  Word counting
*/
int count_words(char *line[])
{
  int i;
  for (i = 0; *line[i]; i++)
  {
    printf("line i is %s\n", line[i]);
  }
  return i;
}

int main(int argc, char *argv[])
{
  char *str = "abc";
  char *line[] = {"abc", "efghi"};
  count_char_io(str);
  count_words(line);
}