#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void bubble_sort(int32_t *array, size_t array_size);

int main(void) {
  int32_t array[] = {4, 2, 3, 6, 1};
  size_t array_size = sizeof(array) / sizeof(*array);

  bubble_sort(array, array_size);

  printf("sorted array:\n");
  for (size_t i = 0; i < array_size; i++) {
    printf("%d\n", array[i]);
  }

  return 0;
}

void bubble_sort(int32_t *array, size_t array_size) {
  for (size_t i = 0; i < array_size; ++i) {
    for (size_t j = 0; j < array_size - 1 - i; ++j) {
      if (array[j] > array[j + 1]) {
        int32_t tmp = array[j];
        array[j] = array[j + 1];
        array[j + 1] = tmp;
      }
    }
  }
}
