#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "uthash.h"

/* hash of hashes */
typedef struct item {
  char name[10];
  struct item *sub;
  int val;
  UT_hash_handle hh;
} item_t;

item_t *items=NULL;

int main(int argc, char *argvp[]) {
  item_t *item1, *item2, *tmp1, *tmp2;

  /* make initial element */
  item_t *i = malloc(sizeof(*i));
  strcpy(i->name, "bob");
  i->sub = NULL;
  i->val = 0;
  HASH_ADD_STR(items, name, i);

  /* add a sub hash table off this element */
  item_t *s = malloc(sizeof(*s));
  strcpy(s->name, "age");
  s->sub = NULL;
  s->val = 37;
  HASH_ADD_STR(i->sub, name, s);

  /* iterate over hash elements  */
  HASH_ITER(hh, items, item1, tmp1) {
    HASH_ITER(hh, item1->sub, item2, tmp2) {
      printf("$items{%s}{%s} = %d\n", item1->name, item2->name, item2->val);
    }
  }

  return 0;
}
