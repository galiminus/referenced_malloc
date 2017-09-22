#include <stdlib.h>

#include "rm_state.h"
#include "rm_utils.h"

/**
 * Attach previously created data to the store and set the reference to 1
 */
int
rm_attach(struct rm_state * state, void * data) {
  size_t key;
  struct rm_malloc_data_entry * data_entry;
  struct rm_malloc_data_entry * head;

  data_entry = malloc (sizeof (*data_entry));
  if (data_entry == NULL) {
    goto error;
  }

  key = rm_hash (data, state->hash_size);

  head = state->entries[key].head;
  state->entries[key].head = data_entry;
  data_entry->data = data;
  data_entry->next = head;
  data_entry->reference_count = 1;

  return (0);

  error:
    return (-1);
}
