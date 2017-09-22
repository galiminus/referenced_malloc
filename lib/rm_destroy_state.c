#include <stdlib.h>

#include "rm_state.h"

/**
 * Destroy a previously created reference store
 */
void
rm_destroy_state (struct rm_state * state) {
  size_t key;
  struct rm_malloc_data_entry * next;
  struct rm_malloc_data_entry * head;

  for (key = 0; key < state->hash_size; key++) {
    head = state->entries[key].head;

    while (head) {
      next = head->next;
      free (head);
      head = next;
    }
  }

  free (state->entries);
  free (state);

  return ;
}
