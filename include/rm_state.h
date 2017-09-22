#ifndef __RM_MALLOC_STATE_H__
# define __RM_MALLOC_STATE_H__

struct rm_malloc_data_entry {
  void * data;
  size_t reference_count;

  struct rm_malloc_data_entry * next;
};

struct rm_malloc_hash_entry {
  struct rm_malloc_data_entry * head;
};

struct rm_state {
  struct rm_malloc_hash_entry * entries;
  size_t hash_size;
};

#endif
