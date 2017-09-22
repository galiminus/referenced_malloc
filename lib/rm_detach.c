#include <stdlib.h>

#include "rm_state.h"
#include "rm_utils.h"

/**
 * Detach data and return the reference counter after decrease, or -1 if data is not found
 */
size_t
rm_detach (struct rm_state * state, void * data) {
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
      if (previous == NULL) {
        state->entries[key].head = head->next;
      } else {
        previous->next = head->next;
      }
      free (head);

      return (0);
    }

    previous = head;
    head = next;
  }

  return (-1);
}
