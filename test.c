#include <string.h>
#include <stdio.h>

#include "rm_malloc.h"

int
main() {
  struct rm_state * state;
  char * buffer;

  state = rm_create_state(RM_DEFAULT_HASH_SIZE);

  buffer = rm_malloc (state, 2048);
  rm_release (state, buffer);

  rm_destroy_state (state);
}
