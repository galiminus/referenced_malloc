#include <stdlib.h>
#include <string.h>

#include "rm_state.h"

/**
 * Create a new reference store
 */
struct rm_state *
rm_create_state (size_t hash_size) {
  struct rm_state * rm_state;

  rm_state = malloc(sizeof(*rm_state));
  if (rm_state == NULL) {
    goto error;
  }

  rm_state->entries = malloc(sizeof(*rm_state->entries) * hash_size);
  if (rm_state->entries == NULL) {
    goto free_rm_state;
  }
  rm_state->hash_size = hash_size;
  memset (rm_state->entries, 0, sizeof(*rm_state->entries) * hash_size);

  return (rm_state);

  free_rm_state:
    free (rm_state->entries);

  error:
    return (NULL);
}
