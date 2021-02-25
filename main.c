#include <stdio.h>
#include "DevTaskLibV2.h"

/// @brief Test function
/// @details Function where all functions are tested
/// @param l - Matrix length
/// @param h - Matrix height
void matTest(int l, int h){

    // Initial matrix
    uint8_t matData[h * l];
    srand(42);
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < l; ++j) {
            matData[i*l + j] = rand() % 100;
        }
    }

    /*uint8_t matData[] = {
            1, 2, 3, 4, 5, 6,
            7, 8, 9, 10, 11, 12,
            13, 14, 15, 16, 17, 18,
            19, 20, 21, 22, 23, 24,
            25, 26, 27, 28, 29, 30
    };*/

    matrix mat = {
            .l = l,
            .h = h,
            .data = matData
    };

    matOut(&mat);

    // Matrix copy
    printf("\nMat copy:\n");
    uint8_t matDataMirror[h * l];
    matrix matMirror = {
            .l = l,
            .h = h,
            .data = matDataMirror
    };
    result r = matCopy(&matMirror, &mat);
    if(r.ok) {
        matOut(&matMirror);
    }else{
        printf("%s", r.error);
    }

    // Matrix flipping
    printf("\nMat flip:\n");
    r = matFlip(&matMirror);
    if(r.ok) {
        matOut(&matMirror);
    } else{
        printf("%s", r.error);
    }

    // Matrix transposing
    printf("\nMat transpose:\n");
    uint8_t matDataTranspose[l * h];
    struct Matrix mat_Transpose = {
            .l = h,
            .h = l,
            .data = matDataTranspose
    };
    r = matTranspose(&mat_Transpose, &mat);
    if(r.ok){
        matOut(&mat_Transpose);
    } else{
        printf("%s", r.error);
    }

    // Matrix rotating
    printf("\nMat rotate:\n");
    uint8_t matDataRotate[l * h];
    struct Matrix mat_Rotate = {
            .l = l,
            .h = h,
            .data = matDataTranspose
    };
    r = matRotate90(&mat_Rotate, &mat, 5);
    if(r.ok){
        matOut(&mat_Rotate);
    } else{
        printf("%s", r.error);
    }

    // Matrix copy fault test
    printf("\nMat copy fault:\n");
    uint8_t matDataSquare[3*3];
    matrix matrixFaulty ={
            .l = 3,
            .h = 3,
            .data = matDataSquare
    };
    r = matCopy(&matrixFaulty, &mat);
    if(r.ok){
        matOut(&matrixFaulty);
    } else{
        printf("%s", r.error);
    }
    printf("\n");

    // Matrix flip fault test
    printf("\nMat flip fault:\n");
    matrix matrixFlipFaulty ={
            .data = matDataSquare
    };
    r = matFlip(&matrixFlipFaulty);
    if(r.ok){
        matOut(&matrixFlipFaulty);
    } else{
        printf("%s", r.error);
    }
    printf("\n");

    // Matrix null pointer test
    printf("\nMat null pointer:\n");
    r = matOut(0);
    printf("\n");

    printf("\nMat flip with null data:\n");
    matrix blank = {
            .h = 3,
            .l = 42,
            .data = 0
    };
    r = matFlip(&blank);
    if(r.ok){
        matOut(&blank);
    } else{
        printf("%s", r.error);
    }

    printf("\nMat transpose with null data:\n");
    r = matTranspose(&blank, &mat);
    if(r.ok){
        matOut(&blank);
    } else{
        printf("%s", r.error);
    }

    printf("\nMat rotate with null data:\n");
    r = matRotate90(&blank, &mat, -6);
    if(r.ok){
        matOut(&blank);
    } else{
        printf("%s", r.error);
    }
}

int main() {
    matTest(4,3);
    return 0;
}
