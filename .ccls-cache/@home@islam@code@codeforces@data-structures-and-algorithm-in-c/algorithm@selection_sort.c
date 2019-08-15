#include <stdio.h>

void selection_sort(int a[], int n) {
  int i, j, k;
  for (i = 0; i < n - 1; i++) {
    k = i;
    for (j = i + 1; j < n; j++) {
      if (a[k] > a[j]) k = j;
    }
    if (k != i) {
      int tmp = a[i];
      a[i] = a[k];
      a[k] = tmp;
    }
  }
}
