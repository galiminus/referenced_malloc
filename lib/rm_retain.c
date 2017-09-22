#include <stdlib.h>

#include "rm_state.h"
#include "rm_utils.h"

/**
 * Increase reference count by one
 */
void
rm_retain (struct rm_state * state, void * data) {
  size_t key;

  struct rm_malloc_data_entry * next;
  struct rm_malloc_data_entry * head;

  key = rm_hash (data, state->hash_size);

  head = state->entries[key].head;

  while (head) {
    next = head->next;

    if (head->data == data) {
      head->reference_count += 1;
      break ;
    }

    head = next;
  }

  return ;
}
