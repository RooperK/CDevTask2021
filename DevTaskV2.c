//
// Created by kotof on 14.02.2021.
//
#include "DevTaskLibV2.h"
#include <stdio.h>
#include <string.h>

result matOut(matrix* src){
    result r = matHandle(src);
    if(!r.ok) {
        printf("%s", r.error);
        return r;
    }
    for (int h = 0; h < src->h; ++h) {
        printf("%2d", src->data[h*src->l]);
        for (int l = 1; l < src->l; ++l) {
            printf(" | %2d", src->data[h*src->l+l]);
        }
        printf("\n");
    }
    return r;
}

result matHandle(matrix* src){
    if(!src){
        result r = {
                .ok = false,
                .error = "No matrix"
        };
        return r;
    }
    if(!src->data){
        result r = {
                .ok = false,
                .error = "No matrix data"
        };
        return r;
    }
    if(src->l <= 0 || src->h <= 0){
        result r = {
                .ok = false,
                .error = "Dimensions must be positive"
        };
        return r;
    }
    result r = {
            .ok = true,
    };
    return r;
}

result matFlip(matrix* src){
    result r = matHandle(src);
    if(!r.ok) return r;
    int s = src->l / 2;
    for (int h = 0; h < src->h; ++h) {
        for (int l = 0, e = (src->l - 1); l < s; ++l, --e) {
            int t = src->data[h*src->l+l];
            src->data[h*src->l+l] = src->data[h*src->l+e];
            src->data[h*src->l+e] = t;
        }
    }
    return r;
}

result matCopy(matrix* dst, matrix* src){
    result r = matHandle(src);
    if(!r.ok) return r;
    r = matHandle(dst);
    if(!r.ok) return r;
    if(dst->h*dst->l != src->h*src->l) {
        r.ok = false;
        r.error = "Matrices must have same capacity";
        return r;
    }
    memcpy(dst->data, src->data, src->l*src->h);
    return r;
}

result matTranspose(matrix* dst, matrix* src){
    result r = matHandle(src);
    if(!r.ok) return r;
    r = matHandle(dst);
    if(!r.ok) return r;
    if(dst->h*dst->l != src->h*src->l) {
        r.ok = false;
        r.error = "Matrices must have same capacity";
        return r;
    }
    for (int i = 0; i < dst->h; ++i) {
        for (int j = 0; j < dst->l; ++j) {
            dst->data[i*(dst->l) + j] = src->data[j*(dst->h) + i];
        }
    }
    return r;
}

result matRotate90(matrix* dst, matrix* src, int n){
    result r = matHandle(dst);
    if(!r.ok) return r;
    r = matHandle(src);
    if(!r.ok) return r;
    if(dst->h*dst->l != src->h*src->l) {
        r.ok = false;
        r.error = "Matrices must have same capacity";
        return r;
    }
    n %= 4;
    n = n < 0 ? 4+n : n;
    if(n != 0){
        if(n == 2){
            dst->l = src->l;
            dst->h = src->h;
            for (int i = 0; i < dst->h; ++i) {
                for (int j = 0; j < dst->l; ++j) {
                    dst->data[i*(dst->l) + j] = src->data[(dst->h - i - 1)*(dst->l) + (dst->l - j - 1)];
                }
            }
        } else{
            dst->l = src->h;
            dst->h = src->l;
            if(n == 1){
                for (int i = 0; i < dst->h; ++i) {
                    for (int j = 0; j < dst->l; ++j) {
                        dst->data[i*(dst->l) + j] = src->data[(dst->l - j - 1)*(dst->h) + i];
                    }
                }
            } else{
                for (int i = 0; i < dst->h; ++i) {
                    for (int j = 0; j < dst->l; ++j) {
                        dst->data[i*(dst->l) + (j)] = src->data[j*(dst->h) + (dst->h - 1 - i)];
                    }
                }
            }
        }
    } else{
        dst->l = src->l;
        dst->h = src->h;
        memcpy(dst->data, src->data, src->l*src->h);
    }

    return r;
}
