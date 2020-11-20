//2019039843

/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

void transpos_6167(int M, int N, int A[N][M], int B[M][N]) {
    for (int i = 0; i < N; i += 8) {
        for (int j = 0; j < M; j += 8) {
            for (int j1 = j; (j1 < j + 8) && (j1 < M); j1++) {
                for (int i1 = i; (i1 < i + 8) && (i1 < N); i1++) {
                    B[j1][i1] = A[i1][j1];
                }
            }
        }
    }
}

void transpos_3232(int M, int N, int A[N][M], int B[M][N]) {
    for (int i = 0; i < N; i += 8) {
        for (int j = 0; j < M; j += 8) {
            if (i == j) {
                for (int i1 = i; (i1 < i + 8) && (i1 < N); i1++) {
                    int t;
                    for (int j1 = j; (j1 < j + 8) && (j1 < M); j1++) {
                        if (j1 == i1) {
                            t = A[i1][i1];
                        }
                        else {
                            B[j1][i1] = A[i1][j1];
                        }
                    }
                    B[i1][i1] = t;
                }
            }	
            else {
                for (int i1 = i; (i1 < i + 8) && (i1 < N); i1++) {
                    for (int j1 = j; (j1 < j + 8) && (j1 < M); j1++) {
                        B[i1][j1] = A[j1][i1];
                    }
                }	
            }
        }
    }
}

void transpos_6464(int M, int N, int A[N][M], int B[M][N]) {
    for (int i = 0; i < N; i += 8) {
        for (int j = 0; j < M; j += 8) {
            int i1, t1, t2, t3, t4, t5, t6, t7, t8;
            for (i1 = i; i1 < i + 4; i1++) {
                B[j][i1] = A[i1][j];
                B[j + 1][i1] = A[i1][j + 1];
                B[j + 2][i1] = A[i1][j + 2];
                B[j + 3][i1] = A[i1][j + 3];
                
                B[j][i1 + 4] = A[i1][j + 4];
                B[j + 1][i1 + 4] = A[i1][j + 5];
                B[j + 2][i1 + 4] = A[i1][j + 6];
                B[j + 3][i1 + 4] = A[i1][j + 7];
            }
            for (i1 = 0; i1 < 4; i1++) {
                t1 = A[i + 4][j + i1];
                t2 = A[i + 5][j + i1];
                t3 = A[i + 6][j + i1];
                t4 = A[i + 7][j + i1];
                t5 = B[j + i1][i + 4];
                t6 = B[j + i1][i + 5];
                t7 = B[j + i1][i + 6];
                t8 = B[j + i1][i + 7];
            
                B[j + i1][i + 4] = t1;
                B[j + i1][i + 5] = t2;
                B[j + i1][i + 6] = t3;
                B[j + i1][i + 7] = t4;
                B[j + i1 + 4][i] = t5;
                B[j + i1 + 4][i + 1] = t6;
                B[j + i1 + 4][i + 2] = t7;
                B[j + i1 + 4][i + 3] = t8;
            }
            for (i1 = i + 4; i1 < i + 8; i1++) {
                t1 = A[i1][j + 4];
                t2 = A[i1][j + 5];
                t3 = A[i1][j + 6];
                t4 = A[i1][j + 7];
            
                B[j + 4][i1] = t1;
                B[j + 5][i1] = t2;
                B[j + 6][i1] = t3;
                B[j + 7][i1] = t4;
            }
        }
    }
}

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    if (M == 61 && N == 67) {
        transpos_6167(M, N, A, B);
    }

    if (M == 32 && N == 32) {
        transpos_3232(M, N, A, B);
    }

    if (M == 64 && N == 64) {
        transpos_6464(M, N, A, B);
    }
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

