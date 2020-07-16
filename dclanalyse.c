/*
  analyse the declaration int *i => i: point to i
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXTOKEN 100
#define BUFSIZE 100

enum
{
  NAME,
  PARENS,
  BRACKETS
};

void dcl(void);
void dirdcl(void);

int gettoken(void);
int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];

int main()
{
  while (gettoken() != EOF)
  {
    strcpy(datatype, token);
    out[0] = '\0';
    dcl();
    // printf("tokentype in the while is %d\n", tokentype);
    if (tokentype != '\n')
      printf("syntax error\n");
    printf("analyse: \n");
    printf("%s: %s %s \n", name, out, datatype);
  }
  return 0;
}

void dcl(void)
{
  int ns;
  for (ns = 0; gettoken() == '*';)
  {
    ns++;
    // printf("ns is %d\n", ns);
  }

  dirdcl();
  while (ns-- > 0)
  {
    strcat(out, " point to");
  }
  // printf("one dcl is done and out is %s\n", out);
}

void dirdcl(void)
{
  // printf("dirdcl is called\n");
  int type;

  if (tokentype == '(')
  {
    dcl();
    if (tokentype != ')')
      printf("error: missing )\n");
  }
  else if (tokentype == NAME)
    strcpy(name, token);
  else
    printf("error: expected name or (dcl)\n");
  while ((type = gettoken()) == PARENS || type == BRACKETS)
    if (type == PARENS)
    {
      strcat(out, " function returning");
    }
    else
    {
      strcat(out, " array");
      strcat(out, token);
      strcat(out, " of");
    }
}

/*
  return next token
*/
int gettoken(void)
{
  int c, getch(void);
  void ungetch(int);
  char *p = token;

  while ((c = getch()) == ' ' || c == '\t')
    ;
  if (c == '(')
  {
    if ((c = getch()) == ')')
    {
      strcpy(token, "()");
      return tokentype = PARENS;
    }
    else
    {
      ungetch(c);
      return tokentype = '(';
    }
  }
  else if (c == '[')
  {
    for (*p++ = c; (*p++ = getch()) != ']';)
      ;
    *p = '\0';
    return tokentype = BRACKETS;
  }
  else if (isalpha(c))
  {
    for (*p++ = c; isalnum(c = getch());)
      *p++ = c;
    *p = '\0';
    ungetch(c);
    return tokentype = NAME;
  }
  else
  {
    return tokentype = c;
  }
}

/*
  use for getch and ungetch
*/
char buf[BUFSIZE];
int bufp = 0;

/*
  get a char from buf or from user input 
*/
int getch(void)
{
  return (bufp > 0) ? buf[--bufp] : getchar();
}

/*
  put back a char to the buf
*/
void ungetch(int c)
{
  if (bufp > BUFSIZE)
    printf("error: buf is full\n");
  else
    buf[bufp++] = c;
}