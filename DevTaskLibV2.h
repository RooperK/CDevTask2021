//
// Created by kotof on 14.02.2021.
//

#ifndef TASK_DEVTASKLIB_H
#define TASK_DEVTASKLIB_H
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

/// @brief Matrix structure
/// @details Stores size and pointer to matrix data
/// @param l - length
/// @param h - height
typedef struct Matrix{
    int l, h;
    uint8_t *data;
} matrix;

/// @brief Result structure
/// @details Stores operation result status
/// @param ok - result flag
/// @param error - error description
typedef struct Result{
    bool ok;
    const char* error;
} result;

/// @brief Matrix validation
/// @details Checks Matrix validity
/// @param src - Matrix
/// @returns result
extern result matHandle(matrix* src);

/// @brief Matrix print out
/// @details Prints out Matrix in console
/// @param src - Matrix
extern result matOut(matrix* src);

/// @brief Matrix mirroring
/// @details Flips Matrix along vertical axis
/// @param dst - destination Matrix
extern result matFlip(matrix* src);

/// @brief Matrix coping
/// @details Copies src to dst
/// @param src - source Matrix
extern result matCopy(matrix* dst, matrix* src);

/// @brief Matrix transposition
/// @details Transposes Matrix along diagonal line
/// @param dst - destination Matrix
/// @param src - source Matrix
extern result matTranspose(matrix* dst, matrix* src);

/// @brief Matrix rotation
/// @details Rotates Matrix clockwise n times
/// @param dst - destination Matrix
/// @param src - source Matrix
/// @param n - rotation times
extern result matRotate90(matrix* dst, matrix* src, int n);

#endif //TASK_DEVTASKLIB_H
