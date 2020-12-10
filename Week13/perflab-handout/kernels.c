/********************************************************
 * Kernels to be optimized for the CS:APP Performance Lab
 ********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

/* 
 * Please fill in the following team struct 
 */
team_t team = {
    "Username",              /* name */

    "User ID",     /* student ID */
    "User email",  /* student email */

    "",                   /* Second member full name (leave blank if none) */
    ""                    /* Second member email addr (leave blank if none) */
};

/***************
 * ROTATE KERNEL
 ***************/

/******************************************************
 * Your different versions of the rotate kernel go here
 ******************************************************/

/* 
 * naive_rotate - The naive baseline version of rotate 
 */
char naive_rotate_descr[] = "naive_rotate: Naive baseline implementation";
void naive_rotate(int dim, pixel *src, pixel *dst) 
{
    int i, j;

    for (i = 0; i < dim; i++)
	for (j = 0; j < dim; j++)
	    dst[RIDX(dim-1-j, i, dim)] = src[RIDX(i, j, dim)];
}

char my_rotate_descr2[] = "my rotate 2";
void my_rotate2(int dim, pixel* src, pixel* dst) {
    int i, j, i1, j1;

    for (i = 0; i < dim; i += 32) {
        for (j = 0; j < dim; j += 32) {
            for (j1 = j; (j1 < j + 32) && (j1 < dim); j1++) {
                for (i1 = i; (i1 < i + 32) && (i1 < dim); i1++) {
                    dst[RIDX(dim-1-j1, i1, dim)] = src[RIDX(i1, j1, dim)];
                }
            }
        }
    }
}

char my_rotate_descr3[] = "my rotate 3";
void my_rotate3(int dim, pixel* src, pixel* dst) {
    int i, j, i1, j1, i1max, j1max;

    for (i = 0; i < dim; i += 32) {
        for (j = 0; j < dim; j += 32) {
            j1max = j + 32;
            for (j1 = j; j1 < j1max; j1++) {
                i1max = i + 32;
                for (i1 = i; i1 < i1max; i1++) {
                    dst[RIDX(dim-1-j1, i1, dim)] = src[RIDX(i1, j1, dim)];
                }
            }
        }
    }
}

char my_rotate_descr4[] = "my rotate 4";
void my_rotate4(int dim, pixel* src, pixel* dst) {
    int i, j, i1, j1, i1max, j1max, dim_power, dst_pos, dst_pos_init, src_pos;
    dim_power = dim * dim;

    for (i = 0; i < dim; i += 32) {
        for (j = 0; j < dim; j += 32) {
            j1max = j + 32;
            dst_pos_init = dim_power - (j + 1) * dim + i;
            for (j1 = j; j1 < j1max; j1++) {
                i1max = i + 32;
                dst_pos = dst_pos_init;
                dst_pos_init -= dim;
                src_pos = i * dim + j1;
                for (i1 = i; i1 < i1max; i1++) {
                    dst[dst_pos++] = src[src_pos];
                    src_pos += dim;
                }
            }
        }
    }
}

#define ROTATE_ASSIGN(dst, idx) { \
    dst[dim_power - (j1 + 1) * dim + idx + i] = src[(idx + i) * dim + j1]; \
}

#define ROTATE_ASSIGN_32 { \
    ROTATE_ASSIGN(dst, 0); \
    ROTATE_ASSIGN(dst, 1); \
    ROTATE_ASSIGN(dst, 2); \
    ROTATE_ASSIGN(dst, 3); \
    ROTATE_ASSIGN(dst, 4); \
    ROTATE_ASSIGN(dst, 5); \
    ROTATE_ASSIGN(dst, 6); \
    ROTATE_ASSIGN(dst, 7); \
    ROTATE_ASSIGN(dst, 8); \
    ROTATE_ASSIGN(dst, 9); \
    ROTATE_ASSIGN(dst, 10); \
    ROTATE_ASSIGN(dst, 11); \
    ROTATE_ASSIGN(dst, 12); \
    ROTATE_ASSIGN(dst, 13); \
    ROTATE_ASSIGN(dst, 14); \
    ROTATE_ASSIGN(dst, 15); \
    ROTATE_ASSIGN(dst, 16); \
    ROTATE_ASSIGN(dst, 17); \
    ROTATE_ASSIGN(dst, 18); \
    ROTATE_ASSIGN(dst, 19); \
    ROTATE_ASSIGN(dst, 20); \
    ROTATE_ASSIGN(dst, 21); \
    ROTATE_ASSIGN(dst, 22); \
    ROTATE_ASSIGN(dst, 23); \
    ROTATE_ASSIGN(dst, 24); \
    ROTATE_ASSIGN(dst, 25); \
    ROTATE_ASSIGN(dst, 26); \
    ROTATE_ASSIGN(dst, 27); \
    ROTATE_ASSIGN(dst, 28); \
    ROTATE_ASSIGN(dst, 29); \
    ROTATE_ASSIGN(dst, 30); \
    ROTATE_ASSIGN(dst, 31); \
}

/*char my_rotate_descr7[] = "my rotate 7";
void my_rotate7(int dim, pixel *src, pixel *dst) {
    int i, j, j1, dim_power, dst_pos, src_pos;

    dim_power = dim * dim;

    for (i = 0; i < dim; i += 32) {
        for (j = 0; j < dim; j += 32) {
            dst_pos = dim_power - (j + 1) * dim + i;
            ROTATE_ASSIGN_32
            j1++;
            ROTATE_ASSIGN_32
            j1++;
            ROTATE_ASSIGN_32
            j1++;
            ROTATE_ASSIGN_32
            j1++;
            ROTATE_ASSIGN_32
            j1++;
            ROTATE_ASSIGN_32
            j1++;
            ROTATE_ASSIGN_32
            j1++;
            ROTATE_ASSIGN_32
            j1++;
            ROTATE_ASSIGN_32
            j1++;
            ROTATE_ASSIGN_32
            j1++;
            ROTATE_ASSIGN_32
            j1++;
            ROTATE_ASSIGN_32
            j1++;
            ROTATE_ASSIGN_32
            j1++;
            ROTATE_ASSIGN_32
            j1++;
            ROTATE_ASSIGN_32
            j1++;
            ROTATE_ASSIGN_32
            j1++;
            ROTATE_ASSIGN_32
            j1++;
            ROTATE_ASSIGN_32
            j1++;
            ROTATE_ASSIGN_32
            j1++;
            ROTATE_ASSIGN_32
            j1++;
            ROTATE_ASSIGN_32
            j1++;
            ROTATE_ASSIGN_32
            j1++;
            ROTATE_ASSIGN_32
            j1++;
            ROTATE_ASSIGN_32
            j1++;
            ROTATE_ASSIGN_32
            j1++;
            ROTATE_ASSIGN_32
            j1++;
            ROTATE_ASSIGN_32
            j1++;
            ROTATE_ASSIGN_32
            j1++;
            ROTATE_ASSIGN_32
            j1++;
            ROTATE_ASSIGN_32
            j1++;
            ROTATE_ASSIGN_32
            j1++;
            ROTATE_ASSIGN_32
        }
    }
}*/

char my_rotate_descr5[] = "my rotate 5";
void my_rotate5(int dim, pixel* src, pixel* dst) {
    int i, j, i1, j1;

    for (i = 0; i < dim; i += 32) {
        for (j = 0; j < dim; j += 32) {
            for (j1 = j; (j1 < j + 32) && (j1 < dim); j1++) {
                for (i1 = i; (i1 < i + 32) && (i1 < dim); i1++) {
                    dst[dim * dim - (j1 + 1) * dim + i1] = src[i1 * dim + j1];
                }
            }
        }
    }
}

char my_rotate_descr[] = "my rotate";
void my_rotate(int dim, pixel* src, pixel* dst) {
    int i, j, i1, j1, it1;

    for (i = 0; i < dim; i += 16) {
        for (j = 0; j < dim; j += 16) {
            for (j1 = j; (j1 < j + 16) && (j1 < dim); j1++) {
                for (i1 = i; (i1 < i + 8) && (i1 < dim); i1 += 2) {
                    dst[RIDX(dim-1-j1, i1, dim)] = src[RIDX(i1, j1, dim)];
                    dst[RIDX(dim-1-j1, i1 + 1, dim)] = src[RIDX(i1 + 1, j1, dim)];
                }
                if (i1 == i + 8) {
                    it1 = i1 - 1;
                    dst[RIDX(dim-1-j1, it1, dim)] = src[RIDX(it1, j1, dim)];
                } else if (i1 == dim) {
                    it1 = dim - 1;
                    dst[RIDX(it1-j1, it1, dim)] = src[RIDX(it1, j1, dim)];
                }
            }
        }
    }
}

/* 
 * rotate - Your current working version of rotate
 * IMPORTANT: This is the version you will be graded on
 */
char rotate_descr[] = "rotate: Current working version";
void rotate(int dim, pixel *src, pixel *dst) 
{
    my_rotate4(dim, src, dst);
}

/*********************************************************************
 * register_rotate_functions - Register all of your different versions
 *     of the rotate kernel with the driver by calling the
 *     add_rotate_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_rotate_functions() 
{
    add_rotate_function(&naive_rotate, naive_rotate_descr);   
    add_rotate_function(&rotate, rotate_descr);   
    /* ... Register additional test functions here */
    //add_rotate_function(&my_rotate, my_rotate_descr);
    //add_rotate_function(&my_rotate2, my_rotate_descr2);  
    //add_rotate_function(&my_rotate3, my_rotate_descr3);
    //add_rotate_function(&my_rotate4, my_rotate_descr4);
    //add_rotate_function(&my_rotate6, my_rotate_descr6); 
    //add_rotate_function(&my_rotate7, my_rotate_descr7);
}


/***************
 * SMOOTH KERNEL
 **************/

/***************************************************************
 * Various typedefs and helper functions for the smooth function
 * You may modify these any way you like.
 **************************************************************/

/* A struct used to compute averaged pixel value */
typedef struct {
    int red;
    int green;
    int blue;
    int num;
} pixel_sum;

/* Compute min and max of two integers, respectively */
static int min(int a, int b) { return (a < b ? a : b); }
static int max(int a, int b) { return (a > b ? a : b); }

/* 
 * initialize_pixel_sum - Initializes all fields of sum to 0 
 */
static void initialize_pixel_sum(pixel_sum *sum) 
{
    sum->red = sum->green = sum->blue = 0;
    sum->num = 0;
    return;
}

/* 
 * accumulate_sum - Accumulates field values of p in corresponding 
 * fields of sum 
 */
static void accumulate_sum(pixel_sum *sum, pixel p) 
{
    sum->red += (int) p.red;
    sum->green += (int) p.green;
    sum->blue += (int) p.blue;
    sum->num++;
    return;
}

/* 
 * assign_sum_to_pixel - Computes averaged pixel value in current_pixel 
 */
static void assign_sum_to_pixel(pixel *current_pixel, pixel_sum sum) 
{
    current_pixel->red = (unsigned short) (sum.red/sum.num);
    current_pixel->green = (unsigned short) (sum.green/sum.num);
    current_pixel->blue = (unsigned short) (sum.blue/sum.num);
    return;
}

/* 
 * avg - Returns averaged pixel value at (i,j) 
 */
static pixel avg(int dim, int i, int j, pixel *src) 
{
    int ii, jj;
    pixel_sum sum;
    pixel current_pixel;

    initialize_pixel_sum(&sum);
    for(ii = max(i-1, 0); ii <= min(i+1, dim-1); ii++) 
	for(jj = max(j-1, 0); jj <= min(j+1, dim-1); jj++) 
	    accumulate_sum(&sum, src[RIDX(ii, jj, dim)]);

    assign_sum_to_pixel(&current_pixel, sum);
    return current_pixel;
}

/******************************************************
 * Your different versions of the smooth kernel go here
 ******************************************************/

/*
 * naive_smooth - The naive baseline version of smooth 
 */
char naive_smooth_descr[] = "naive_smooth: Naive baseline implementation";
void naive_smooth(int dim, pixel *src, pixel *dst) 
{
    int i, j;

    for (i = 0; i < dim; i++)
	for (j = 0; j < dim; j++)
	    dst[RIDX(i, j, dim)] = avg(dim, i, j, src);
}


#define ACCUMULATE_SUM(r, g, b, from, idx) { \
    int _t_idx = (idx); \
    r += from[_t_idx].red; \
    g += from[_t_idx].green; \
    b += from[_t_idx].blue; \
}

#define INITIALZE_PIXEL_SUM(r, g, b) { \
    r = 0; g = 0; b = 0; \
}

#define ASSIGN_TO_DST(dst, r, g, b, div_n) { \
    dst.red = (unsigned short) (r / div_n); \
    dst.green = (unsigned short) (g / div_n); \
    dst.blue = (unsigned short) (b / div_n); \
}

char my_smooth_descr2[] = "smooth2";
void my_smooth2(int dim, pixel *src, pixel *dst) {
    int target_row, target_idx, target_idx_init, i, j, dim_power, dim_x2;

    int rt;
    int gt;
    int bt;

    dim_power = dim * dim;
    dim_x2 = dim * 2;

    // corner smooth
    // 0, 0
    INITIALZE_PIXEL_SUM(rt, gt, bt);
    ACCUMULATE_SUM(rt, gt, bt, src, 0);
    ACCUMULATE_SUM(rt, gt, bt, src, 1);
    ACCUMULATE_SUM(rt, gt, bt, src, dim);
    ACCUMULATE_SUM(rt, gt, bt, src, dim + 1);

    ASSIGN_TO_DST(dst[0], rt, gt, bt, 4);

    // dim - 1, 0
    INITIALZE_PIXEL_SUM(rt, gt, bt);
    ACCUMULATE_SUM(rt, gt, bt, src, dim - 1);
    ACCUMULATE_SUM(rt, gt, bt, src, dim - 2);
    ACCUMULATE_SUM(rt, gt, bt, src, dim_x2 - 1);
    ACCUMULATE_SUM(rt, gt, bt, src, dim_x2 - 2);

    ASSIGN_TO_DST(dst[dim - 1], rt, gt, bt, 4);

    // 0, dim - 1
    INITIALZE_PIXEL_SUM(rt, gt, bt);
    ACCUMULATE_SUM(rt, gt, bt, src, dim_power - dim_x2);
    ACCUMULATE_SUM(rt, gt, bt, src, dim_power - dim_x2 + 1);
    ACCUMULATE_SUM(rt, gt, bt, src, dim_power - dim);
    ACCUMULATE_SUM(rt, gt, bt, src, dim_power - dim + 1);

    ASSIGN_TO_DST(dst[dim_power - dim], rt, gt, bt, 4);

    // dim - 1, dim - 1
    INITIALZE_PIXEL_SUM(rt, gt, bt);
    ACCUMULATE_SUM(rt, gt, bt, src, dim_power - 1);
    ACCUMULATE_SUM(rt, gt, bt, src, dim_power - 2);
    ACCUMULATE_SUM(rt, gt, bt, src, dim_power - dim - 1);
    ACCUMULATE_SUM(rt, gt, bt, src, dim_power - dim - 2);

    ASSIGN_TO_DST(dst[dim_power - 1], rt, gt, bt, 4);

    // edge smooth
    // 1 ~ dim-1, 0
    for (i = 1; i < dim - 1; i++) {
        INITIALZE_PIXEL_SUM(rt, gt, bt);

        ACCUMULATE_SUM(rt, gt, bt, src, i - 1);
        ACCUMULATE_SUM(rt, gt, bt, src, i);
        ACCUMULATE_SUM(rt, gt, bt, src, i + 1);
        ACCUMULATE_SUM(rt, gt, bt, src, i + dim - 1);
        ACCUMULATE_SUM(rt, gt, bt, src, i + dim);
        ACCUMULATE_SUM(rt, gt, bt, src, i + dim + 1);

        ASSIGN_TO_DST(dst[i], rt, gt, bt, 6);
    }

    // 0, 1 ~ dim-1
    target_row = dim_power - dim_x2;
    for (i = dim; i <= target_row; i += dim) {
        INITIALZE_PIXEL_SUM(rt, gt, bt);

        ACCUMULATE_SUM(rt, gt, bt, src, i - dim);
        ACCUMULATE_SUM(rt, gt, bt, src, i - dim + 1);
        ACCUMULATE_SUM(rt, gt, bt, src, i);
        ACCUMULATE_SUM(rt, gt, bt, src, i + 1);
        ACCUMULATE_SUM(rt, gt, bt, src, i + dim);
        ACCUMULATE_SUM(rt, gt, bt, src, i + dim + 1);

        ASSIGN_TO_DST(dst[i], rt, gt, bt, 6);
    }

    // dim-1, 1 ~ dim-1
    target_row = dim_power - dim;
    for (i = dim_x2-1; i < target_row; i += dim) {
        INITIALZE_PIXEL_SUM(rt, gt, bt);

        ACCUMULATE_SUM(rt, gt, bt, src, i - dim - 1);
        ACCUMULATE_SUM(rt, gt, bt, src, i - dim);
        ACCUMULATE_SUM(rt, gt, bt, src, i - 1);
        ACCUMULATE_SUM(rt, gt, bt, src, i);
        ACCUMULATE_SUM(rt, gt, bt, src, i + dim - 1);
        ACCUMULATE_SUM(rt, gt, bt, src, i + dim);

        ASSIGN_TO_DST(dst[i], rt, gt, bt, 6);
    }

    // 1 ~ dim-1, dim-1
    for (i = dim_power - dim + 1; i < dim_power - 1; i++) {
        INITIALZE_PIXEL_SUM(rt, gt, bt);

        ACCUMULATE_SUM(rt, gt, bt, src, i - dim - 1);
        ACCUMULATE_SUM(rt, gt, bt, src, i - dim);
        ACCUMULATE_SUM(rt, gt, bt, src, i - dim + 1);
        ACCUMULATE_SUM(rt, gt, bt, src, i - 1);
        ACCUMULATE_SUM(rt, gt, bt, src, i);
        ACCUMULATE_SUM(rt, gt, bt, src, i + 1);

        ASSIGN_TO_DST(dst[i], rt, gt, bt, 6);
    }
    
    target_idx_init = dim + 1;
    for (i = 1; i < dim - 1; i++) {
        target_idx = target_idx_init;
        for (j = 1; j < dim - 1; j++) {
            INITIALZE_PIXEL_SUM(rt, gt, bt);

            ACCUMULATE_SUM(rt, gt, bt, src, target_idx - dim - 1);
            ACCUMULATE_SUM(rt, gt, bt, src, target_idx - dim);
            ACCUMULATE_SUM(rt, gt, bt, src, target_idx - dim + 1);
            ACCUMULATE_SUM(rt, gt, bt, src, target_idx - 1);
            ACCUMULATE_SUM(rt, gt, bt, src, target_idx);
            ACCUMULATE_SUM(rt, gt, bt, src, target_idx + 1);
            ACCUMULATE_SUM(rt, gt, bt, src, target_idx + dim - 1);
            ACCUMULATE_SUM(rt, gt, bt, src, target_idx + dim);
            ACCUMULATE_SUM(rt, gt, bt, src, target_idx + dim + 1);

            ASSIGN_TO_DST(dst[target_idx], rt, gt, bt, 9);
            target_idx++;
        }
        target_idx_init += dim;
    }
}

#define ADD_TWO_PIXEL(t_rt, t_gt, t_bt, s_rt, s_gt, s_bt) {\
    t_rt += s_rt; \
    t_gt += s_gt; \
    t_bt += s_bt; \
}

#define MOVE_PIXEL(t_rt, t_gt, t_bt, s_rt, s_gt, s_bt) {\
    t_rt = s_rt; \
    t_gt = s_gt; \
    t_bt = s_bt; \
}

char my_smooth_descr4[] = "smooth4";
void my_smooth4(int dim, pixel *src, pixel *dst) {
    int target_row, target_idx, target_idx_init, i, j, dim_power, dim_x2;

    int rt;
    int gt;
    int bt;

    int prev_rt, prev_gt, prev_bt;
    int cur_rt, cur_gt, cur_bt;
    int next_rt, next_gt, next_bt;

    dim_power = dim * dim;
    dim_x2 = dim * 2;

    // corner smooth
    // 0, 0
    INITIALZE_PIXEL_SUM(rt, gt, bt);
    ACCUMULATE_SUM(rt, gt, bt, src, 0);
    ACCUMULATE_SUM(rt, gt, bt, src, 1);
    ACCUMULATE_SUM(rt, gt, bt, src, dim);
    ACCUMULATE_SUM(rt, gt, bt, src, dim + 1);

    ASSIGN_TO_DST(dst[0], rt, gt, bt, 4);

    // dim - 1, 0
    INITIALZE_PIXEL_SUM(rt, gt, bt);
    ACCUMULATE_SUM(rt, gt, bt, src, dim - 1);
    ACCUMULATE_SUM(rt, gt, bt, src, dim - 2);
    ACCUMULATE_SUM(rt, gt, bt, src, dim_x2 - 1);
    ACCUMULATE_SUM(rt, gt, bt, src, dim_x2 - 2);

    ASSIGN_TO_DST(dst[dim - 1], rt, gt, bt, 4);

    // 0, dim - 1
    INITIALZE_PIXEL_SUM(rt, gt, bt);
    ACCUMULATE_SUM(rt, gt, bt, src, dim_power - dim_x2);
    ACCUMULATE_SUM(rt, gt, bt, src, dim_power - dim_x2 + 1);
    ACCUMULATE_SUM(rt, gt, bt, src, dim_power - dim);
    ACCUMULATE_SUM(rt, gt, bt, src, dim_power - dim + 1);

    ASSIGN_TO_DST(dst[dim_power - dim], rt, gt, bt, 4);

    // dim - 1, dim - 1
    INITIALZE_PIXEL_SUM(rt, gt, bt);
    ACCUMULATE_SUM(rt, gt, bt, src, dim_power - 1);
    ACCUMULATE_SUM(rt, gt, bt, src, dim_power - 2);
    ACCUMULATE_SUM(rt, gt, bt, src, dim_power - dim - 1);
    ACCUMULATE_SUM(rt, gt, bt, src, dim_power - dim - 2);

    ASSIGN_TO_DST(dst[dim_power - 1], rt, gt, bt, 4);

    // edge smooth
    // 1 ~ dim-1, 0
    for (i = 1; i < dim - 1; i++) {
        INITIALZE_PIXEL_SUM(rt, gt, bt);

        ACCUMULATE_SUM(rt, gt, bt, src, i - 1);
        ACCUMULATE_SUM(rt, gt, bt, src, i);
        ACCUMULATE_SUM(rt, gt, bt, src, i + 1);
        ACCUMULATE_SUM(rt, gt, bt, src, i + dim - 1);
        ACCUMULATE_SUM(rt, gt, bt, src, i + dim);
        ACCUMULATE_SUM(rt, gt, bt, src, i + dim + 1);

        ASSIGN_TO_DST(dst[i], rt, gt, bt, 6);
    }

    // 0, 1 ~ dim-1
    target_row = dim_power - dim_x2;
    for (i = dim; i <= target_row; i += dim) {
        INITIALZE_PIXEL_SUM(rt, gt, bt);

        ACCUMULATE_SUM(rt, gt, bt, src, i - dim);
        ACCUMULATE_SUM(rt, gt, bt, src, i - dim + 1);
        ACCUMULATE_SUM(rt, gt, bt, src, i);
        ACCUMULATE_SUM(rt, gt, bt, src, i + 1);
        ACCUMULATE_SUM(rt, gt, bt, src, i + dim);
        ACCUMULATE_SUM(rt, gt, bt, src, i + dim + 1);

        ASSIGN_TO_DST(dst[i], rt, gt, bt, 6);
    }

    // dim-1, 1 ~ dim-1
    target_row = dim_power - dim;
    for (i = dim_x2-1; i < target_row; i += dim) {
        INITIALZE_PIXEL_SUM(rt, gt, bt);

        ACCUMULATE_SUM(rt, gt, bt, src, i - dim - 1);
        ACCUMULATE_SUM(rt, gt, bt, src, i - dim);
        ACCUMULATE_SUM(rt, gt, bt, src, i - 1);
        ACCUMULATE_SUM(rt, gt, bt, src, i);
        ACCUMULATE_SUM(rt, gt, bt, src, i + dim - 1);
        ACCUMULATE_SUM(rt, gt, bt, src, i + dim);

        ASSIGN_TO_DST(dst[i], rt, gt, bt, 6);
    }

    // 1 ~ dim-1, dim-1
    for (i = dim_power - dim + 1; i < dim_power - 1; i++) {
        INITIALZE_PIXEL_SUM(rt, gt, bt);

        ACCUMULATE_SUM(rt, gt, bt, src, i - dim - 1);
        ACCUMULATE_SUM(rt, gt, bt, src, i - dim);
        ACCUMULATE_SUM(rt, gt, bt, src, i - dim + 1);
        ACCUMULATE_SUM(rt, gt, bt, src, i - 1);
        ACCUMULATE_SUM(rt, gt, bt, src, i);
        ACCUMULATE_SUM(rt, gt, bt, src, i + 1);

        ASSIGN_TO_DST(dst[i], rt, gt, bt, 6);
    }
    
    target_idx_init = dim + 1;
    for (i = 1; i < dim - 1; i++) {
        target_idx = target_idx_init;
        INITIALZE_PIXEL_SUM(prev_rt, prev_gt, prev_bt);
        ACCUMULATE_SUM(prev_rt, prev_gt, prev_bt, src, target_idx - dim - 1);
        ACCUMULATE_SUM(prev_rt, prev_gt, prev_bt, src, target_idx - 1);
        ACCUMULATE_SUM(prev_rt, prev_gt, prev_bt, src, target_idx + dim - 1);

        INITIALZE_PIXEL_SUM(cur_rt, cur_gt, cur_bt);
        ACCUMULATE_SUM(cur_rt, cur_gt, cur_bt, src, target_idx - dim);
        ACCUMULATE_SUM(cur_rt, cur_gt, cur_bt, src, target_idx);
        ACCUMULATE_SUM(cur_rt, cur_gt, cur_bt, src, target_idx + dim);

        for (j = 1; j < dim - 1; j++) {
            INITIALZE_PIXEL_SUM(rt, gt, bt);
            INITIALZE_PIXEL_SUM(next_rt, next_gt, next_bt);

            ACCUMULATE_SUM(next_rt, next_gt, next_bt, src, target_idx - dim + 1);
            ACCUMULATE_SUM(next_rt, next_gt, next_bt, src, target_idx + 1);
            ACCUMULATE_SUM(next_rt, next_gt, next_bt, src, target_idx + dim + 1);

            ADD_TWO_PIXEL(rt, gt, bt, prev_rt, prev_gt, prev_bt);
            ADD_TWO_PIXEL(rt, gt, bt, cur_rt, cur_gt, cur_bt);
            ADD_TWO_PIXEL(rt, gt, bt, next_rt, next_gt, next_bt);

            MOVE_PIXEL(prev_rt, prev_gt, prev_bt, cur_rt, cur_gt, cur_bt);
            MOVE_PIXEL(cur_rt, cur_gt, cur_bt, next_rt, next_gt, next_bt);

            ASSIGN_TO_DST(dst[target_idx], rt, gt, bt, 9);
            target_idx++;
        }
        target_idx_init += dim;
    }
}

char my_smooth_descr3[] = "smooth3";
void my_smooth3(int dim, pixel *src, pixel *dst) {
    int target_row, target_idx, target_idx_init, i, j, dim_power, dim_x2;

    int rt;
    int gt;
    int bt;

    int t_idx;

    dim_power = dim * dim;
    dim_x2 = dim * 2;

    // corner smooth
    // 0, 0
    INITIALZE_PIXEL_SUM(rt, gt, bt);
    ACCUMULATE_SUM(rt, gt, bt, src, 0);
    ACCUMULATE_SUM(rt, gt, bt, src, 1);
    ACCUMULATE_SUM(rt, gt, bt, src, dim);
    ACCUMULATE_SUM(rt, gt, bt, src, dim + 1);

    ASSIGN_TO_DST(dst[0], rt, gt, bt, 4);

    // dim - 1, 0
    INITIALZE_PIXEL_SUM(rt, gt, bt);
    ACCUMULATE_SUM(rt, gt, bt, src, dim - 1);
    ACCUMULATE_SUM(rt, gt, bt, src, dim - 2);
    ACCUMULATE_SUM(rt, gt, bt, src, dim_x2 - 1);
    ACCUMULATE_SUM(rt, gt, bt, src, dim_x2 - 2);

    ASSIGN_TO_DST(dst[dim - 1], rt, gt, bt, 4);

    // 0, dim - 1
    INITIALZE_PIXEL_SUM(rt, gt, bt);
    ACCUMULATE_SUM(rt, gt, bt, src, dim_power - dim_x2);
    ACCUMULATE_SUM(rt, gt, bt, src, dim_power - dim_x2 + 1);
    ACCUMULATE_SUM(rt, gt, bt, src, dim_power - dim);
    ACCUMULATE_SUM(rt, gt, bt, src, dim_power - dim + 1);

    ASSIGN_TO_DST(dst[dim_power - dim], rt, gt, bt, 4);

    // dim - 1, dim - 1
    INITIALZE_PIXEL_SUM(rt, gt, bt);
    ACCUMULATE_SUM(rt, gt, bt, src, dim_power - 1);
    ACCUMULATE_SUM(rt, gt, bt, src, dim_power - 2);
    ACCUMULATE_SUM(rt, gt, bt, src, dim_power - dim - 1);
    ACCUMULATE_SUM(rt, gt, bt, src, dim_power - dim - 2);

    ASSIGN_TO_DST(dst[dim_power - 1], rt, gt, bt, 4);

    // edge smooth
    // 1 ~ dim-1, 0
    for (i = 1; i < dim - 1; i++) {
        INITIALZE_PIXEL_SUM(rt, gt, bt);

        t_idx = i - 1;
        ACCUMULATE_SUM(rt, gt, bt, src, t_idx);
        t_idx++;
        ACCUMULATE_SUM(rt, gt, bt, src, t_idx);
        t_idx++;
        ACCUMULATE_SUM(rt, gt, bt, src, t_idx);
        t_idx = i + dim - 1;
        ACCUMULATE_SUM(rt, gt, bt, src, t_idx);
        t_idx++;
        ACCUMULATE_SUM(rt, gt, bt, src, t_idx);
        t_idx++;
        ACCUMULATE_SUM(rt, gt, bt, src, t_idx);

        ASSIGN_TO_DST(dst[i], rt, gt, bt, 6);
    }

    // 0, 1 ~ dim-1
    target_row = dim_power - dim_x2;
    for (i = dim; i <= target_row; i += dim) {
        INITIALZE_PIXEL_SUM(rt, gt, bt);

        t_idx = i - dim;
        ACCUMULATE_SUM(rt, gt, bt, src, t_idx);
        t_idx++;
        ACCUMULATE_SUM(rt, gt, bt, src, t_idx);
        t_idx = i;
        ACCUMULATE_SUM(rt, gt, bt, src, t_idx);
        t_idx++;
        ACCUMULATE_SUM(rt, gt, bt, src, t_idx);
        t_idx = i + dim;
        ACCUMULATE_SUM(rt, gt, bt, src, t_idx);
        t_idx++;
        ACCUMULATE_SUM(rt, gt, bt, src, t_idx);

        ASSIGN_TO_DST(dst[i], rt, gt, bt, 6);
    }

    // dim-1, 1 ~ dim-1
    target_row = dim_power - dim;
    for (i = dim_x2-1; i < target_row; i += dim) {
        INITIALZE_PIXEL_SUM(rt, gt, bt);

        t_idx = i - dim - 1;
        ACCUMULATE_SUM(rt, gt, bt, src, t_idx);
        t_idx++;
        ACCUMULATE_SUM(rt, gt, bt, src, t_idx);
        t_idx = i - 1;
        ACCUMULATE_SUM(rt, gt, bt, src, t_idx);
        t_idx++;
        ACCUMULATE_SUM(rt, gt, bt, src, t_idx);
        t_idx = i + dim - 1;
        ACCUMULATE_SUM(rt, gt, bt, src, t_idx);
        t_idx++;
        ACCUMULATE_SUM(rt, gt, bt, src, t_idx);

        ASSIGN_TO_DST(dst[i], rt, gt, bt, 6);
    }

    // 1 ~ dim-1, dim-1
    for (i = dim_power - dim + 1; i < dim_power - 1; i++) {
        INITIALZE_PIXEL_SUM(rt, gt, bt);

        t_idx = i - dim - 1;
        ACCUMULATE_SUM(rt, gt, bt, src, t_idx);
        t_idx++;
        ACCUMULATE_SUM(rt, gt, bt, src, t_idx);
        t_idx++;
        ACCUMULATE_SUM(rt, gt, bt, src, t_idx);
        t_idx = i - 1;
        ACCUMULATE_SUM(rt, gt, bt, src, t_idx);
        t_idx++;
        ACCUMULATE_SUM(rt, gt, bt, src, t_idx);
        t_idx++;
        ACCUMULATE_SUM(rt, gt, bt, src, t_idx);

        ASSIGN_TO_DST(dst[i], rt, gt, bt, 6);
    }
    
    target_idx_init = dim + 1;
    for (i = 1; i < dim - 1; i++) {
        target_idx = target_idx_init;
        for (j = 1; j < dim - 1; j++) {
            INITIALZE_PIXEL_SUM(rt, gt, bt);
            
            t_idx = target_idx - dim - 1;
            ACCUMULATE_SUM(rt, gt, bt, src, t_idx);
            t_idx++;
            ACCUMULATE_SUM(rt, gt, bt, src, t_idx);
            t_idx++;
            ACCUMULATE_SUM(rt, gt, bt, src, t_idx);
            t_idx = target_idx - 1;
            ACCUMULATE_SUM(rt, gt, bt, src, t_idx);
            t_idx++;
            ACCUMULATE_SUM(rt, gt, bt, src, t_idx);
            t_idx++;
            ACCUMULATE_SUM(rt, gt, bt, src, t_idx);
            t_idx = target_idx + dim - 1;
            ACCUMULATE_SUM(rt, gt, bt, src, t_idx);
            t_idx++;
            ACCUMULATE_SUM(rt, gt, bt, src, t_idx);
            t_idx++;
            ACCUMULATE_SUM(rt, gt, bt, src, t_idx);

            ASSIGN_TO_DST(dst[target_idx], rt, gt, bt, 9);
            target_idx++;
        }
        target_idx_init += dim;
    }
}

/*
 * smooth - Your current working version of smooth. 
 * IMPORTANT: This is the version you will be graded on
 */
char smooth_descr[] = "smooth: Current working version";
void smooth(int dim, pixel *src, pixel *dst) 
{
    my_smooth4(dim, src, dst);
}


/********************************************************************* 
 * register_smooth_functions - Register all of your different versions
 *     of the smooth kernel with the driver by calling the
 *     add_smooth_function() for each test function.  When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_smooth_functions() {
    add_smooth_function(&smooth, smooth_descr);
    add_smooth_function(&naive_smooth, naive_smooth_descr);
    /* ... Register additional test functions here */
    //add_smooth_function(&my_smooth2, my_smooth_descr2);
    add_smooth_function(&my_smooth4, my_smooth_descr4);
}

