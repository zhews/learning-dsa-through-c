#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum TwoCrystalBallsError { OK, DID_NOT_BREAK } TwoCrystalBallsError;

TwoCrystalBallsError two_crystal_balls(bool *break_points,
                                       size_t break_points_size, size_t *out);
char *error_message_two_crystal_balls(TwoCrystalBallsError error);

int main(void) {
  bool break_points[] = {
      false, false, false, false, false, false, false, false,
      false, true,  true,  true,  true,  true,  true,  true,
  };
  size_t break_points_size = sizeof(break_points) / sizeof(*break_points);

  size_t floor;
  TwoCrystalBallsError two_crystal_balls_error;
  if ((two_crystal_balls_error =
           two_crystal_balls(break_points, break_points_size, &floor)) != OK) {
    fprintf(stderr, "invalid break points, error: %s\n",
            error_message_two_crystal_balls(two_crystal_balls_error));
    exit(EXIT_FAILURE);
  }

  printf("the crystal balls break on floor: %lu\n", floor);

  return 0;
}

TwoCrystalBallsError two_crystal_balls(bool *break_points,
                                       size_t break_points_size, size_t *out) {
  size_t jump_size = (size_t)floor(sqrt(break_points_size));

  size_t i = jump_size;
  while (i < break_points_size) {
    if (break_points[i]) {
      break;
    }
    i += jump_size;
  }

  size_t j = i - jump_size;
  while (j <= i && i < break_points_size) {
    if (break_points[j]) {
      *out = j;
      return OK;
    }
    ++j;
    ++i;
  }

  return DID_NOT_BREAK;
}

char *error_message_two_crystal_balls(TwoCrystalBallsError error) {
  switch (error) {
  case OK:
    return "no error";
  case DID_NOT_BREAK:
    return "crystal balls do not break with these break points";
  default:
    return "unknown error";
  }
}
