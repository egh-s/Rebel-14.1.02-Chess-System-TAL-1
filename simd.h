
#ifndef SIMD_H
#define SIMD_H

#include <stdint.h>


void simd_linear_forward(uint8_t *input, int32_t *output, int ninputs,
                         int noutputs, int32_t *biases, int8_t *weights);


void simd_scale_and_clamp(int32_t *input, uint8_t *output, int shift,
                          int nvalues);

void simd_clamp(int16_t *input, uint8_t *output, int nvalues);

void simd_copy(int16_t *from, int16_t *to, int nvalues);
void simd_add(int16_t *from, int16_t *to, int nvalues);
void simd_sub(int16_t *from, int16_t *to, int nvalues);

#endif
