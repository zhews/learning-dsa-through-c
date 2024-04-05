#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct ArrayList {
  size_t length;
  size_t capacity;
  int32_t *array;
} ArrayList;

typedef enum ArrayListError {
  OK,
  NULL_POINTER,
  ALLOCATION_FAILED,
  INDEX_OUT_OF_BOUNDS,
  EMPTY_ARRAY_LIST
} ArrayListError;

ArrayListError new_array_list(size_t capacity, ArrayList **out);
ArrayListError get_array_list(ArrayList *array_list, size_t index,
                              int32_t *out);
ArrayListError push_array_list(ArrayList *array_list, int32_t value);
ArrayListError pop_array_list(ArrayList *array_list, int32_t *out);
ArrayListError free_array_list(ArrayList *array_list);
char *error_message_array_list(ArrayListError error);

int main(void) {
  ArrayList *array_list;
  ArrayListError array_list_error;

  if ((array_list_error = new_array_list(2, &array_list)) != OK) {
    fprintf(stderr, "could not create array list, error: %s\n",
            error_message_array_list(array_list_error));
    exit(EXIT_FAILURE);
  }

  for (size_t i = 0; i < 3; i++) {
    if ((array_list_error = push_array_list(array_list, i)) != OK) {
      fprintf(stderr, "could not push array list, error: %s\n",
              error_message_array_list(array_list_error));
    }

    int32_t value;
    if ((array_list_error = get_array_list(array_list, i, &value)) != OK) {
      fprintf(stderr, "could not get array list, error: %s\n",
              error_message_array_list(array_list_error));
    }

    printf("pushed value: %d\n", value);
  }

  for (size_t i = 0; i < 3; i++) {
    int32_t value;
    if ((array_list_error = pop_array_list(array_list, &value)) != OK) {
      fprintf(stderr, "could not pop array list, error: %s\n",
              error_message_array_list(array_list_error));
    }

    printf("popped value: %d\n", value);
  }

  free_array_list(array_list);

  return 0;
}

ArrayListError new_array_list(size_t capacity, ArrayList **out) {
  if (out == NULL) {
    return NULL_POINTER;
  }

  ArrayList *array_list = (ArrayList *)malloc(sizeof(ArrayList));

  if (array_list == NULL) {
    return ALLOCATION_FAILED;
  }

  const size_t default_capacity = 1;
  if (capacity == 0) {
    capacity = default_capacity;
  }

  int32_t *array = (int32_t *)malloc(capacity * sizeof(int32_t));

  if (array == NULL) {
    return ALLOCATION_FAILED;
  }

  array_list->length = 0;
  array_list->capacity = capacity;
  array_list->array = array;

  *out = array_list;

  return OK;
}

ArrayListError get_array_list(ArrayList *array_list, size_t index,
                              int32_t *out) {
  if (array_list == NULL || out == NULL) {
    return NULL_POINTER;
  }

  if (index >= array_list->length) {
    return INDEX_OUT_OF_BOUNDS;
  }

  *out = array_list->array[index];

  return OK;
}

ArrayListError push_array_list(ArrayList *array_list, int32_t value) {
  if (array_list == NULL) {
    return NULL_POINTER;
  }

  if (array_list->length == array_list->capacity) {
    const float capacity_growth_rate = 1.5;
    size_t new_capacity =
        (size_t)ceil(array_list->capacity * capacity_growth_rate);

    int32_t *new_array =
        realloc(array_list->array, new_capacity * sizeof(int32_t));

    if (new_array == NULL) {
      return ALLOCATION_FAILED;
    }

    array_list->capacity = new_capacity;
    array_list->array = new_array;
  }

  array_list->array[array_list->length] = value;
  ++array_list->length;

  return OK;
}

ArrayListError pop_array_list(ArrayList *array_list, int32_t *out) {
  if (array_list == NULL || out == NULL) {
    return NULL_POINTER;
  }

  if (array_list->length == 0) {
    return EMPTY_ARRAY_LIST;
  }

  *out = array_list->array[array_list->length - 1];
  --array_list->length;

  return OK;
}

ArrayListError free_array_list(ArrayList *array_list) {
  if (array_list == NULL) {
    return NULL_POINTER;
  }

  free(array_list->array);
  free(array_list);

  return OK;
}

char *error_message_array_list(ArrayListError error) {
  switch (error) {
  case OK:
    return "no error";
  case NULL_POINTER:
    return "operation cannot be performed on a null pointer";
  case ALLOCATION_FAILED:
    return "could not allocate memory for operation";
  case INDEX_OUT_OF_BOUNDS:
    return "provided index is out of bounds";
  case EMPTY_ARRAY_LIST:
    return "operation could not be performed because array list is empty";
  default:
    return "unknown error";
  }
}
