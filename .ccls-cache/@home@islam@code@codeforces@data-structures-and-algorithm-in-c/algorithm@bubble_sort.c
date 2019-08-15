#include <stdio.h>

void bubble_sort(int array[], int n) {
  int i, j, tmp;
  for (i = 0; i < n - 1; i++) {
    for (j = 0; j < n - 1 - i; j++) {
      if (array[j] > array[j + 1]) {
        tmp = array[j + 1];
        array[j + 1] = array[j];
        array[j] = tmp;
      }
    }
  }
}
