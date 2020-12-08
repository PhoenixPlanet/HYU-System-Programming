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
    add_rotate_function(&my_rotate3, my_rotate_descr3);
    add_rotate_function(&my_rotate4, my_rotate_descr4);
    //add_rotate_function(&my_rotate5, my_rotate_descr5); 
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

char my_smooth_descr2[] = "smooth2";
void my_smooth2(int dim, pixel *src, pixel *dst) 
{
    int target_row, target_idx, target_idx_init, i, j, dim_power, dim_x2, n, i1, j1;

    pixel_sum t_pixel_sum;
    pixel t_pixel;

    dim_power = dim * dim;
    dim_x2 = dim * 2;

    // corner smooth
    // 0, 0
    initialize_pixel_sum(&t_pixel_sum);
    accumulate_sum(&t_pixel_sum, src[0]);
    accumulate_sum(&t_pixel_sum, src[1]);
    accumulate_sum(&t_pixel_sum, src[dim]);
    accumulate_sum(&t_pixel_sum, src[dim + 1]);

    assign_sum_to_pixel(&t_pixel, t_pixel_sum);
    dst[0] = t_pixel;

    // dim - 1, 0
    initialize_pixel_sum(&t_pixel_sum);
    accumulate_sum(&t_pixel_sum, src[dim - 1]);
    accumulate_sum(&t_pixel_sum, src[dim - 2]);
    accumulate_sum(&t_pixel_sum, src[dim_x2 - 1]);
    accumulate_sum(&t_pixel_sum, src[dim_x2 - 2]);

    assign_sum_to_pixel(&t_pixel, t_pixel_sum);
    dst[dim - 1] = t_pixel;

    // 0, dim - 1
    initialize_pixel_sum(&t_pixel_sum);
    accumulate_sum(&t_pixel_sum, src[dim_power - dim_x2]);
    accumulate_sum(&t_pixel_sum, src[dim_power - dim_x2 + 1]);
    accumulate_sum(&t_pixel_sum, src[dim_power - dim]);
    accumulate_sum(&t_pixel_sum, src[dim_power - dim + 1]);

    assign_sum_to_pixel(&t_pixel, t_pixel_sum);
    dst[dim_power - dim] = t_pixel;

    // dim - 1, dim - 1
    initialize_pixel_sum(&t_pixel_sum);
    accumulate_sum(&t_pixel_sum, src[dim_power - 1]);
    accumulate_sum(&t_pixel_sum, src[dim_power - 2]);
    accumulate_sum(&t_pixel_sum, src[dim_power - dim - 1]);
    accumulate_sum(&t_pixel_sum, src[dim_power - dim - 2]);

    assign_sum_to_pixel(&t_pixel, t_pixel_sum);
    dst[dim_power - 1] = t_pixel;

    // edge smooth
    // 1 ~ dim-1, 0
    for (i = 1; i < dim - 1; i++) {
        initialize_pixel_sum(&t_pixel_sum);
        for (n = i - 1; n <= i + 1; n++) {
            accumulate_sum(&t_pixel_sum, src[n]);
        }
        for (n = i - 1; n <= i + 1; n++) {
            accumulate_sum(&t_pixel_sum, src[dim + n]);
        }
        assign_sum_to_pixel(dst + i, t_pixel_sum);
    }

    // 0, 1 ~ dim-1
    target_row = dim_power - dim_x2;
    for (i = dim; i <= target_row; i += dim) {
        initialize_pixel_sum(&t_pixel_sum);

        accumulate_sum(&t_pixel_sum, src[i - dim]);
        accumulate_sum(&t_pixel_sum, src[i - dim + 1]);
        accumulate_sum(&t_pixel_sum, src[i]);
        accumulate_sum(&t_pixel_sum, src[i + 1]);
        accumulate_sum(&t_pixel_sum, src[i + dim]);
        accumulate_sum(&t_pixel_sum, src[i + dim + 1]);

        assign_sum_to_pixel(dst + i, t_pixel_sum);
    }

    // dim-1, 1 ~ dim-1
    for (i = dim-1; i < target_row; i += dim) {
        initialize_pixel_sum(&t_pixel_sum);

        accumulate_sum(&t_pixel_sum, src[i - dim - 1]);
        accumulate_sum(&t_pixel_sum, src[i - dim]);
        accumulate_sum(&t_pixel_sum, src[i - 1]);
        accumulate_sum(&t_pixel_sum, src[i]);
        accumulate_sum(&t_pixel_sum, src[i + dim - 1]);
        accumulate_sum(&t_pixel_sum, src[i + dim]);

        assign_sum_to_pixel(dst + i, t_pixel_sum);
    }

    // 1 ~ dim-1, dim-1
    for (i = dim_power - dim + 1; i < dim_power - 1; i++) {
        initialize_pixel_sum(&t_pixel_sum);
        for (n = i - 1; n <= i + 1; n++) {
            accumulate_sum(&t_pixel_sum, src[n]);
        }
        for (n = i - 1; n <= i + 1; n++) {
            accumulate_sum(&t_pixel_sum, src[dim + n]);
        }
        assign_sum_to_pixel(dst + i, t_pixel_sum);
    }
    
    target_idx_init = dim + 1;
    for (i = 1; i < dim - 1; i++) {
        target_idx = target_idx_init;
        for (j = 1; j < dim - 1; j++) {
            initialize_pixel_sum(&t_pixel_sum);
            for(i1 = i - 1; i1 <= i + 1; i1++) {
                for(j1 = j - 1; j1 <= j + 1; j1++) {
                    accumulate_sum(&t_pixel_sum, src[RIDX(i1, j1, dim)]);
                }
            }
            assign_sum_to_pixel(dst + target_idx, t_pixel_sum);
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
    naive_smooth(dim, src, dst);
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
    add_smooth_function(&my_smooth2, my_smooth_descr2);
}

