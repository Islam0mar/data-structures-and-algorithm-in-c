/*
 *author: booirror@163.com
 *date: 2015/4/28
 */
#include <stdio.h>
void swap(int a[], int n, int m) {
  if (n == m) return;
  int tmp = a[n];
  a[n] = a[m];
  a[m] = tmp;
}

void qsort(int a[], int n) {
  int i, j;
  int last = 0;
  if (n < 2) return;
  swap(a, 0, n / 2);
  for (i = 1; i < n; i++) {
    if (a[i] < a[0]) {
      swap(a, ++last, i);
    }
  }
  swap(a, 0, last);
  qsort(a, last);
  qsort(a + last + 1, n - last - 1);
}
