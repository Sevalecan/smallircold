#ifndef CINTVECT_H
#define CINTVECT_H

#include <stdlib.h>

enum _civ_ret {
    CIV_EMPTY = 1,
    CIV_NOMEM,
    CIV_INVPTR
};

typedef struct _cintvect {
    unsigned long int count;
    unsigned int *lst;
} cintvect;

cintvect *civ_new();
void civ_delete(cintvect *);
int civ_push(cintvect *des, unsigned int pdat);
int civ_pop(cintvect *des, unsigned int *pdat);
int civ_resize(cintvect *des, unsigned int len);
int civ_size(cintvect *des);

#endif
