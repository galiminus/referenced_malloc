## rm_malloc

This library wrap calls to malloc to include reference counting, it can also use any
preallocated memory pointer.

Internally it use a simple hash table which hold all the reference counters, it hurts
performance by a factor of 5 to 10.

### API

#### Initialization

Counters are stored in a `struct rm_state`, you are responsible for giving this state
to all other `rm_*` functions. The library doesn't have any internal state so you are
free to create multiple states (ex.: one state by thread).

```
#include "rm_malloc.h"

int main() {
  struct rm_state * state;

  state = rm_create_state(RM_DEFAULT_HASH_SIZE);
  rm_destroy_state(state);

  return ;
}
```

`RM_DEFAULT_HASH_SIZE` is the default size of the hash table, you can try to tweak it
to see if you get better perfomance.

Note that the `struct rm_state` is opaque, the underlying structure can change without
constituting an API break. However you can include `rm_state.h` to access its definition.

#### Allocation and deallocation

```
#include "rm_malloc.h"

int main() {
  struct rm_state * state;
  char * buffer;

  state = rm_create_state(RM_DEFAULT_HASH_SIZE);

  buffer = rm_malloc(state, 2048);
  rm_release(state, buffer);

  rm_destroy_state(state);

  return ;
}
```

In this case `rm_malloc` and `rm_release` works pretty much like `malloc` and `free`.
`rm_malloc` allocates a new chunk of memory a set its reference counter to 1, `rm_release`
decrease the reference counter a `free()` the given data if the reference counter reaches 0.

`rm_retain` can be used to increment the reference counter:

```
#include "rm_malloc.h"

int main() {
  struct rm_state * state;
  char * buffer;

  state = rm_create_state(RM_DEFAULT_HASH_SIZE);

  buffer = rm_malloc(state, 2048); // refcount == 1
  rm_retain(state, buffer);        // refcount == 2
  rm_retain(state, buffer);        // refcount == 3

  rm_release(state, buffer);       // refcount == 2
  rm_release(state, buffer);       // refcount == 1
  rm_release(state, buffer);       // refcount == 0, data is freed

  rm_destroy_state(state);

  return ;
}
```

You can also attach any arbytrary chunk of memory with `rm_attach`:

```
#include "rm_malloc.h"

int main() {
  struct rm_state * state;
  char * buffer;

  state = rm_create_state(RM_DEFAULT_HASH_SIZE);

  buffer = malloc(2048);
  rm_attach(state, buffer);
  rm_release(state, buffer);

  rm_destroy_state(state);

  return ;
}
```

And you detach a pointer from the entire state by calling `rm_detach`, this function
will not free the attached data, but it will decrease its reference counter before
returning it, so you can check if any other references are still holding.

```
#include "rm_malloc.h"

int main() {
  struct rm_state * state;
  char * buffer;
  size_t refcount;

  state = rm_create_state(RM_DEFAULT_HASH_SIZE);

  buffer = rm_malloc(state, 2048);
  rm_retain(state, buffer);

  rm_detach(state, buffer); // will return 1

  rm_destroy_state(state);

  return ;
}
```

## LICENCING

DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
        Version 2, December 2004

Copyright (C) 2017 Victor Goya <phorque@phorque.it>

Everyone is permitted to copy and distribute verbatim or modified
copies of this license document, and changing it is allowed as long
as the name is changed.

DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION

0. You just DO WHAT THE FUCK YOU WANT TO.
