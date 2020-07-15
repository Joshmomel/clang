/*
  calculate: get the result for such like 1 2 - 4 5 + *
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXOP 100
#define NUMBER '0'
#define MAXVAL 100
#define BUFSIZE 100

int getop(char[]);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);

int main()
{
  int type;
  double op2;
  char s[MAXOP];

  while ((type = getop(s)) != EOF)
  {
    switch (type)
    {
    case NUMBER:
      push(atof(s));
      break;
    case '+':
      push(pop() + pop());
      break;
    case '*':
      push(pop() * pop());
      break;
    case '-':
      op2 = pop();
      push(pop() - op2);
      break;
    case '/':
      op2 = pop();
      push(pop() / op2);
      break;
    case '\n':
      printf("return: %g\n", pop());
      break;
    default:
      printf("error command %s\n", s);
      break;
    }
  }
  return 0;
}

/*
  push f onto value stack
*/
int sp = 0;
double val[MAXVAL];

void push(double f)
{
  if (sp < MAXVAL)
  {
    val[sp] = f;
    sp++;
  }
  else
    printf("error: stack is full");
}

/*
  pop the first element in the stack 
*/
double pop()
{
  if (sp > 0)
  {
    double v = val[--sp];
    return v;
  }
  else
    printf("error: the stack is empty");
  return 0.0;
}

/*
  get next character or numberic operand
*/
int getop(char s[])
{
  int i, c;
  // skip space
  while ((s[0] = c = getch()) == ' ' || c == '\t')
    ;
  s[1] = '\0';
  // Non digit
  if (!isdigit(c) && c != '.')
  {
    return c;
  }

  i = 0;
  if (isdigit(c))
    while (isdigit(s[++i] = c = getch()))
      ;
  if (c == '.')
    while (isdigit(s[++i] = c = getch()))
      ;
  s[i] = '\0';
  // Non EOF, should put the char back for next getop
  if (c != EOF)
    ungetch(c);
  return NUMBER;
}

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
    printf("error: buf is full");
  else
    buf[bufp++] = c;
}