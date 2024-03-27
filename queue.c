#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int32_t value;
  struct Node *next;
} Node;

typedef struct Queue {
  size_t size;
  Node *front;
  Node *back;
} Queue;

typedef enum QueueError {
  OK,
  NULL_POINTER,
  ALLOCATION_FAILED,
  EMPTY_QUEUE
} QueueError;

QueueError new_queue(Queue **out);
QueueError enqueue(Queue *queue, int32_t value);
QueueError dequeue(Queue *queue, int32_t *out);
QueueError peek(Queue *queue, int32_t *out);
QueueError free_queue(Queue *queue);
char *error_message_queue(QueueError error);

int main(void) {
  Queue *queue;
  QueueError queue_error;

  if ((queue_error = new_queue(&queue)) != OK) {
    fprintf(stderr, "could not create queue, error: %s\n",
            error_message_queue(queue_error));
    exit(EXIT_FAILURE);
  }

  for (int32_t i = 0; i < 3; ++i) {
    if ((queue_error = enqueue(queue, i)) != OK) {
      fprintf(stderr, "could not enqueue, error: %s\n",
              error_message_queue(queue_error));
    }
  }

  if (queue->size > 0) {
    printf("size: %lu, front: %d, back: %d\n", queue->size, queue->front->value,
           queue->back->value);
  }

  for (size_t i = 0; i < 3; ++i) {
    int32_t value;

    if ((queue_error = peek(queue, &value)) != OK) {
      fprintf(stderr, "could not peek queue, error: %s\n",
              error_message_queue(queue_error));
    } else {
      printf("peek: %d\n", value);
    }

    if ((queue_error = dequeue(queue, &value)) != OK) {
      fprintf(stderr, "could not dequeue, error: %s\n",
              error_message_queue(queue_error));
    } else {
      printf("dequeue: %d\n", value);
    }
  }

  free_queue(queue);

  return 0;
}

QueueError new_queue(Queue **out) {
  if (out == NULL) {
    return NULL_POINTER;
  }

  Queue *queue = (Queue *)malloc(sizeof(Queue));

  if (queue == NULL) {
    return ALLOCATION_FAILED;
  }

  queue->size = 0;
  queue->front = NULL;
  queue->back = NULL;

  *out = queue;

  return OK;
}

QueueError enqueue(Queue *queue, int32_t value) {
  if (queue == NULL) {
    return NULL_POINTER;
  }

  Node *node = (Node *)malloc(sizeof(Node));

  if (node == NULL) {
    return ALLOCATION_FAILED;
  }

  node->value = value;
  node->next = NULL;

  if (queue->size == 0) {
    queue->front = node;
    queue->back = node;
  } else {
    queue->back->next = node;
    queue->back = node;
  }

  ++queue->size;

  return OK;
}

QueueError dequeue(Queue *queue, int32_t *out) {
  if (queue == NULL || out == NULL) {
    return NULL_POINTER;
  }

  if (queue->size == 0) {
    return EMPTY_QUEUE;
  }

  Node *popped_front = queue->front;
  if (queue->size > 1) {
    queue->front = popped_front->next;
  } else {
    queue->front = NULL;
    queue->back = NULL;
  }
  --queue->size;

  *out = popped_front->value;
  free(popped_front);

  return OK;
}

QueueError peek(Queue *queue, int32_t *out) {
  if (queue == NULL || out == NULL) {
    return NULL_POINTER;
  }

  if (queue->size == 0) {
    return EMPTY_QUEUE;
  }

  *out = queue->front->value;

  return OK;
}

QueueError free_queue(Queue *queue) {
  if (queue == NULL) {
    return NULL_POINTER;
  }

  Node *current = queue->front;

  while (current != NULL) {
    Node *delete = current;
    current = current->next;
    free(delete);
  }

  free(queue);

  return OK;
}

char *error_message_queue(QueueError error) {
  switch (error) {
  case OK:
    return "no error";
  case NULL_POINTER:
    return "operation cannot be performed on a null pointer";
  case ALLOCATION_FAILED:
    return "could not allocate memory for operation";
  case EMPTY_QUEUE:
    return "operation could not be performed because queue is empty";
  default:
    return "unknown error";
  }
}
