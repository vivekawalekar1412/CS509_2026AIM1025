#ifndef GEMM_H
#define GEMM_H

void run_gemm_simple(const char *filepath);
void run_gemm_blocking(const char *filepath, int block_size);

#endif