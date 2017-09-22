#include <stdlib.h>

#include "rm_malloc.h"
#include "rm_state.h"

/**
 * Allocate data and set the reference counter to 1
 */
void *
rm_malloc(struct rm_state * state, size_t size) {
  void * data;

  data = malloc (size);
  if (data == NULL) {
    goto error;
  }

  if (rm_attach (state, data) == -1) {
    goto free_data;
  }

  return (data);

  free_data:
    free (data);
  error:
    return (NULL);
}
