#ifndef CINTVECT_C
#define CINTVECT_C

#include <cintvect.h>

cintvect *civ_new() {
    cintvect *mf;
    mf = (cintvect *)malloc(sizeof(cintvect));
    if (mf == NULL) return 0;
    memset(mf, 0, sizeof(cintvect));
    return mf;
}    

void civ_delete(cintvect *civ) {
    int x;
    if (civ->count > 0) {
        free(civ->lst);
    }    
    free(civ);
    return;
}    

int civ_push(cintvect *des, unsigned int pdat) {
    int ret;
    ret = civ_resize(des, des->count+1);
    if (ret != 0) return ret;
    des->lst[des->count-1] = pdat;
    return 0;
}

int civ_pop(cintvect *des, unsigned int *pdat) {
    if (des->count == 0) return CIV_EMPTY;
    int ret;
    *pdat = des->lst[des->count-1];
    ret = civ_resize(des, des->count-1);
    return 0;
}

int civ_resize(cintvect *des, unsigned int len) {
    if ((des->count == 0 || des->lst == NULL) && len != 0) {
        des->count = 0;
        des->lst = malloc(sizeof(unsigned long int)*len);
        if (des->lst == NULL) return CIV_NOMEM;
        des->count = len;
    }
    else if (des->count > 0 && des->lst != NULL && len > 0) {
        int *ra;
        ra = realloc(des->lst, sizeof(unsigned long int)*len);
        if (ra == NULL) return CIV_NOMEM;
        des->lst = ra;
        des->count = len;
    }
    else if (des->count > 0 && des->lst != NULL && len == 0) {
        free(des->lst);
        des->count = len;
        des->lst = NULL;
    }
    return 0;
}

int civ_size(cintvect *des) {
    return des->count;
}

#endif
