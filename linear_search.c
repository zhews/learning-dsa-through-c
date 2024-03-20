#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

bool linear_search(int32_t *haystack, size_t haystack_length, int32_t needle);

int main(void) {
  int32_t haystack[] = {
      0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
  };
  size_t haystack_length = sizeof(haystack) / sizeof(*haystack);

  int32_t needle = 5;

  bool found = linear_search(haystack, haystack_length, needle);
  printf("found needle in haystack: %d\n", found);

  return 0;
}

bool linear_search(int32_t *haystack, size_t haystack_length, int32_t needle) {
  for (size_t i = 0; i < haystack_length; ++i) {
    if (haystack[i] == needle)
      return true;
  }
  return false;
}
