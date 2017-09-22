#include <stdlib.h>
#include <stdint.h>

uint64_t
rm_hash_64(uint64_t key)
{
  key = (~key) + (key << 21);
  key = key ^ (key >> 24);
  key = (key + (key << 3)) + (key << 8);
  key = key ^ (key >> 14);
  key = (key + (key << 2)) + (key << 4);
  key = key ^ (key >> 28);
  key = key + (key << 31);

  return (key);
}

size_t
rm_hash (void * data, size_t hash_size) {
  return ((size_t) rm_hash_64 ((uint64_t)data) % hash_size);
}
