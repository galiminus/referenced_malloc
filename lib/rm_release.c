#include <stdlib.h>

#include "rm_state.h"
#include "rm_utils.h"

/**
 * Decrease reference count and free data if no more references are hold
 */
void
rm_release (struct rm_state * state, void * data) {
  size_t key;

  struct rm_malloc_data_entry * previous;
  struct rm_malloc_data_entry * next;
  struct rm_malloc_data_entry * head;

  key = rm_hash (data, state->hash_size);

  previous = NULL;
  head = state->entries[key].head;

  while (head) {
    next = head->next;

    if (head->data == data) {
      head->reference_count -= 1;
      if (head->reference_count == 0) {
        if (previous == NULL) {
          state->entries[key].head = head->next;
        } else {
          previous->next = head->next;
        }
        free (head->data);
        free (head);
      }
      break ;
    }

    previous = head;
    head = next;
  }

  return ;
}
