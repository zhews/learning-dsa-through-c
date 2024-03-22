#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

bool binary_search(int32_t *haystack, size_t haystack_length, int32_t needle);

int main(void) {
  int32_t haystack[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  size_t haystack_length = sizeof(haystack) / sizeof(*haystack);

  int32_t needle = 5;

  bool found = binary_search(haystack, haystack_length, needle);
  printf("found needle in haystack: %d\n", found);

  return 0;
}

bool binary_search(int32_t *haystack, size_t haystack_length, int32_t needle) {
  size_t range_start = 0;
  size_t range_end = haystack_length;

  while (range_start < range_end) {
    size_t midpoint_index =
        (size_t)floor(range_start + (range_end - range_start) / 2);
    int32_t midpoint = haystack[midpoint_index];

    if (midpoint == needle) {
      return true;
    } else if (needle > midpoint) {
      range_start = midpoint_index + 1;
    } else {
      range_end = midpoint_index;
    }
  }

  return false;
}
