#ifndef __RM_MALLOC_H__
# define __RM_MALLOC_H__

#include <stdlib.h>

#include "rm_state.h"

#define RM_DEFAULT_HASH_SIZE 4096

void *
rm_malloc(struct rm_state * state, size_t size);

struct rm_state *
rm_create_state (size_t hash_size);

void
rm_destroy_state (struct rm_state * state);

int
rm_attach(struct rm_state * state, void * data);

void
rm_release (struct rm_state * state, void * data);

void
rm_retain (struct rm_state * state, void * data);

void *
rm_detach (struct rm_state * state, void * data);

#endif
