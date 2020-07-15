#include <stdio.h>

void qsort(int v[], int i, int j);
void swap(int v[], int i, int j);

void qsort(int v[], int left, int right)
{
  int i, last;
  if (left >= right)
    return;
  swap(v, left, (left + right) / 2);
  last = left;
  for (i = left + 1; i <= right; i++)
    if (v[i] < v[left])
      swap(v, ++last, i);
  swap(v, left, last);
  qsort(v, left, last - 1);
  qsort(v, last + 1, right);
}

void swap(int v[], int i, int j)
{
  int temp;

  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}

int main(int argc, char *argv[])
{
  /*test*/
  // int last = 0;
  // int v[] = {2, 1, 5, 8, 7};
  // swap(v, ++last, 2);
  // for (int i = 0; i < 5; i++)
  //   printf("swap done %d\n", v[i]);

  int arr[] = {2, 1, 5, 8, 7};
  qsort(arr, 0, 4);
  for (int i = 0; i < 5; i++)
    printf("quick sort done %d\n", arr[i]);
}