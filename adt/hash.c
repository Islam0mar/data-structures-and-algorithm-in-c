#include <stdio.h>
#include <stdlib.h>

/* FIXME: Replace int with required type */
typedef int element_type;

typedef unsigned int position;

typedef position (*hash)(element_type e);

/* if equals, return 1, othewise, return 0 */
typedef int (*cmp_func)(element_type e, element_type b);

typedef enum kind_of_entry { legitimate, empty, deleted } kind_of_entry;

typedef struct hash_entry {
  element_type element;
  kind_of_entry info;
} cell;

typedef struct hash_table {
  hash hfunc;
  cmp_func equals;
  unsigned int table_size;
  cell* cells;
} * hash_table_ptr;

hash_table_ptr hash_init_table(unsigned int size, hash f, cmp_func c);

void hash_insert(hash_table_ptr hash_tbl, element_type e);

position hash_find(hash_table_ptr hash_tbl, element_type e);

void hash_delete(hash_table_ptr hash_tbl, element_type e);

void hash_destroy_table(hash_table_ptr* ptr);

static void fatal_error(const char* errmsg) {
  fprintf(stderr, "%s\n", errmsg);
  exit(1);
}

hash_table_ptr hash_init_table(unsigned int size, hash f, cmp_func c) {
  int i = 0;
  if (f == NULL) {
    fatal_error("hash function must be provided");
  }
  if (c == NULL) {
    fatal_error("compare function must be provided");
  }
  hash_table_ptr tbl = (hash_table_ptr)malloc(sizeof(struct hash_table));
  if (tbl == NULL) {
    fatal_error("out of space");
  }
  tbl->cells = (cell*)malloc(sizeof(cell) * size);
  if (tbl->cells == NULL) {
    free(tbl);
    fatal_error("out of space");
  }
  tbl->table_size = size;
  tbl->hfunc = f;
  tbl->equals = c;
  for (; i < size; ++i) {
    tbl->cells[i].info = empty;
  }
  return tbl;
}

void hash_insert(hash_table_ptr tbl, element_type e) {
  position pos = tbl->hfunc(e);
  while (tbl->cells[pos].info != empty) {
    pos = (pos + 1) % tbl->table_size;
  }
  tbl->cells[pos].element = e;
  tbl->cells[pos].info = legitimate;
}

position hash_find(hash_table_ptr tbl, element_type e) {
  int i = 0;
  position idx = tbl->hfunc(e);
  while (i < tbl->table_size) {
    if (tbl->cells[idx].info == legitimate &&
        tbl->equals(tbl->cells[idx].element, e))
      return idx;
    idx = (idx + 1) % tbl->table_size;
    i++;
  }
  return -1;
}

void hash_delete(hash_table_ptr ptr, element_type e) {
  position pos = hash_find(ptr, e);
  if (pos != -1) {
    ptr->cells[pos].info = deleted;
  }
}

void hash_destroy_table(hash_table_ptr* phash_ptr) {
  hash_table_ptr tbl = *phash_ptr;
  if (*phash_ptr == NULL) return;
  if (tbl->cells != NULL) {
    free(tbl->cells);
  }
  free(tbl);
  *phash_ptr = NULL;
}
