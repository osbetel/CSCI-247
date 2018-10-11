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
    "W 0118 3647",              /* Student ID */

    "Andrew Nguyen",     /* First member full name */
    "nguyena8@wwu.edu",  /* First member email address */

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
void naive_rotate(int dim, pixel *src, pixel *dst) {
    int i, j;

    for (i = 0; i < dim; i++)
	    for (j = 0; j < dim; j++)
	        dst[RIDX(dim-1-j, i, dim)] = src[RIDX(i, j, dim)];
}

/* 
 * rotate - Your current working version of rotate
 * IMPORTANT: This is the version you will be graded on
 */

char rotate_descr[] = "Loop unrolling by 16, 2.6";
void rotate(int dim, pixel *src, pixel *dst) {
    int i, j, k;

    for (i = 0; i < dim; i+=16) {
        for (j = 0; j < dim; j++) {
            k = (dim - 1 - j)*dim + i;

            dst[k] = src[i * dim + j];
            dst[k + 1] = src[(i+1) * dim + j];
            dst[k + 2] = src[(i+2) * dim + j];
            dst[k + 3] = src[(i+3) * dim + j];
            dst[k + 4] = src[(i+4) * dim + j];
            dst[k + 5] = src[(i+5) * dim + j];
            dst[k + 6] = src[(i+6) * dim + j];
            dst[k + 7] = src[(i+7) * dim + j];
            dst[k + 8] = src[(i+8) * dim + j];
            dst[k + 9] = src[(i+9) * dim + j];
            dst[k + 10] = src[(i+10) * dim + j];
            dst[k + 11] = src[(i+11) * dim + j];
            dst[k + 12] = src[(i+12) * dim + j];
            dst[k + 13] = src[(i+13) * dim + j];
            dst[k + 14] = src[(i+14) * dim + j];
            dst[k + 15] = src[(i+15) * dim + j];
        }
    }
}

/*********************************************************************
 * register_rotate_functions - Register all of your different versions
 *     of the rotate kernel with the driver by calling the
 *     add_rotate_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

    void register_rotate_functions() {
        add_rotate_function(&naive_rotate, naive_rotate_descr);
        add_rotate_function(&rotate, rotate_descr);

    /* ... Register additional test functions here */
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
    static inline void initialize_pixel_sum(pixel_sum *sum) {
        sum->red = sum->green = sum->blue = 0;
        sum->num = 0;
        return;
    }

/* 
 * accumulate_sum - Accumulates field values of p in corresponding 
 * fields of sum 
 */
    static inline void accumulate_sum(pixel_sum *sum, pixel p) {
        sum->red += (int) p.red;
        sum->green += (int) p.green;
        sum->blue += (int) p.blue;
        sum->num++;
        return;
    }

/* 
 * assign_sum_to_pixel - Computes averaged pixel value in current_pixel 
 */
    static inline void assign_sum_to_pixel(pixel *current_pixel, pixel_sum sum) {
        current_pixel->red = (unsigned short) (sum.red / sum.num);
        current_pixel->green = (unsigned short) (sum.green / sum.num);
        current_pixel->blue = (unsigned short) (sum.blue / sum.num);
        return;
    }

/* 
 * avg - Returns averaged pixel value at (i,j) 
 */
    static inline pixel avg(int dim, int i, int j, pixel *src) {
        int ii, jj;
        pixel_sum sum;
        pixel current_pixel;

        initialize_pixel_sum(&sum);
        for (ii = max(i - 1, 0); ii <= min(i + 1, dim - 1); ii++)
            for (jj = max(j - 1, 0); jj <= min(j + 1, dim - 1); jj++)
                accumulate_sum(&sum, src[RIDX(ii, jj, dim)]);

        assign_sum_to_pixel(&current_pixel, sum);
        return current_pixel;
    }

/*
 * ************************************ START OF MY ADDED HELPER FUNCTIONS ******************************************
 */

    /*
     * Next 4 functions average the individual corner pixels
     */
    static inline unsigned short corner1avg(pixel *src, int color, int i) {
        switch (color) {
            case 0:
                return (src[0].red + src[1].red + src[i].red + src[i + 1].red) / 4;
            case 1:
                return (src[0].green + src[1].green + src[i].green + src[i + 1].green) / 4;
            case 2:
                return (src[0].blue + src[1].blue + src[i].blue + src[i + 1].blue) / 4;
            default:
                return 0;
        }
    }

    static inline unsigned short corner2avg(pixel *src, int color, int dim, int j) {
        switch (color) {
            case 0:
                return (src[dim - 1].red + src[dim - 2].red + src[j].red + src[j - 1].red) / 4;
            case 1:
                return (src[dim - 1].green + src[dim - 2].green + src[j].green + src[j - 1].green) / 4;
            case 2:
                return (src[dim - 1].blue + src[dim - 2].blue + src[j].blue + src[j - 1].blue) / 4;
            default:
                return 0;
        }
    }

    static inline unsigned short corner3avg(pixel *src, int color, int i, int j) {
        switch (color) {
            case 0:
                return (src[i].red + src[i + 1].red + src[j].red + src[j + 1].red) / 4;
            case 1:
                return (src[i].green + src[i + 1].green + src[j].green + src[j + 1].green) / 4;
            case 2:
                return (src[i].blue + src[i + 1].blue + src[j].blue + src[j + 1].blue) / 4;
            default:
                return 0;
        }
    }

    static inline unsigned short corner4avg(pixel *src, int color, int i, int j) {
        switch (color) {
            case 0:
                return (src[i].red + src[i - 1].red + src[j].red + src[j - 1].red) / 4;
            case 1:
                return (src[i].green + src[i - 1].green + src[j].green + src[j - 1].green) / 4;
            case 2:
                return (src[i].blue + src[i - 1].blue + src[j].blue + src[j - 1].blue) / 4;
            default:
                return 0;
        }
    }

    /*
     * Function to average the corners
     */
    static inline void avgImageCorners(int dim, pixel *src, pixel *dst) {
        int i, j;
        dst[0].red = corner1avg(src, 0, dim);
        dst[0].green = corner1avg(src, 1, dim);
        dst[0].blue = corner1avg(src, 2, dim);

        dst[dim-1].red = corner2avg(src, 0, dim, (dim * 2) - 1);
        dst[dim-1].green = corner2avg(src, 1, dim, (dim * 2) - 1);
        dst[dim-1].blue = corner2avg(src, 2, dim, (dim * 2) - 1);

        i = dim * (dim - 2);
        j = dim * (dim - 1);
        dst[j].red = corner3avg(src, 0, i, j);
        dst[j].green = corner3avg(src, 1, i, j);
        dst[j].blue = corner3avg(src, 2, i, j);

        i = (dim * (dim - 1)) - 1;
        j = (dim * dim) - 1;
        dst[j].red = corner4avg(src, 0, i, j);
        dst[j].green = corner4avg(src, 1, i, j);
        dst[j].blue = corner4avg(src, 2, i, j);
    }

    /*
     * Next 4 functions handle individual side pixel averages.
     */
    static inline unsigned short side1avg(pixel *src, int color, int i, int j) {
    switch (color) {
        case 0:
            return (src[j].red + src[j - 1].red + src[j + 1].red + src[j + i].red + src[j + 1 + i].red + src[j - 1 + i].red) / 6;
        case 1:
            return (src[j].green + src[j - 1].green + src[j + 1].green + src[j + i].green + src[j + 1 + i].green + src[j - 1 + i].green) / 6;
        case 2:
            return (src[j].blue + src[j - 1].blue + src[j + 1].blue + src[j + i].blue + src[j + 1 + i].blue + src[j - 1 + i].blue) / 6;
        default:
            return 0;
    }
}

    static inline unsigned short side2avg(pixel *src, int color, int i, int j) {
        switch (color) {
            case 0:
                return (src[j].red + src[j - 1].red + src[j + 1].red + src[j - i].red + src[j + 1 - i].red + src[j - 1 - i].red) / 6;
            case 1:
                return (src[j].green + src[j - 1].green + src[j + 1].green + src[j - i].green + src[j + 1 - i].green + src[j - 1 - i].green) / 6;
            case 2:
                return (src[j].blue + src[j - 1].blue + src[j + 1].blue + src[j - i].blue + src[j + 1 - i].blue + src[j - 1 - i].blue) / 6;
            default:
                return 0;
        }
    }

    static inline unsigned short side3avg(pixel *src, int color, int i, int j) {
        switch (color) {
            case 0:
                return (src[j].red + src[j - 1].red + src[j - i].red + src[j + i].red + src[j - i - 1].red + src[j - 1 + i].red) / 6;
            case 1:
                return (src[j].green + src[j - 1].green + src[j - i].green + src[j + i].green + src[j - i - 1].green + src[j - 1 + i].green) / 6;
            case 2:
                return (src[j].blue + src[j - 1].blue + src[j - i].blue + src[j + i].blue + src[j - i - 1].blue + src[j - 1 + i].blue) / 6;
            default:
                return 0;
        }
    }

    static inline unsigned short side4avg(pixel *src, int color, int i, int j) {
        switch (color) {
            case 0:
                return (src[j].red + src[j - i].red + src[j + 1].red + src[j + i].red + src[j + 1 + i].red + src[j - i + 1].red) / 6;
            case 1:
                return (src[j].green + src[j - i].green + src[j + 1].green + src[j + i].green + src[j + 1 + i].green + src[j - i + 1].green) / 6;
            case 2:
                return (src[j].blue + src[j - i].blue + src[j + 1].blue + src[j + i].blue + src[j + 1 + i].blue + src[j - i + 1].blue) / 6;
            default:
                return 0;
        }
    }

    /*
     * Function to average the sides
     */
    static inline void avgImageSides(int dim, pixel *src, pixel *dst) {
        int i, j;

        i = dim - 1;
        for (j = 1; j < i; j++) {
            dst[j].red = side1avg(src,0 , dim, j);
            dst[j].green = side1avg(src,1 , dim, j);
            dst[j].blue = side1avg(src,2 , dim, j);
        }

        i = (dim * dim) - 1;
        for (j = i - dim + 2; j < i; j++) {
            dst[j].red = side2avg(src,0 , dim, j);
            dst[j].green = side2avg(src,1 , dim, j);
            dst[j].blue = side2avg(src,2 , dim, j);
        }

        for (j = dim+dim-1; j < dim*dim-1; j+=dim) {
            dst[j].red = side3avg(src,0 , dim, j);
            dst[j].green = side3avg(src,1 , dim, j);
            dst[j].blue = side3avg(src,2 , dim, j);
        }

        i = i - (dim - 1);
        for (j = dim; j < i; j+=dim) {
            dst[j].red = side4avg(src,0 , dim, j);
            dst[j].green = side4avg(src,1 , dim, j);
            dst[j].blue = side4avg(src,2 , dim, j);
        }
    }

    static inline unsigned short avgBody1(pixel *src, int color, int tally, int dim) {
        switch (color) {
            case 0:
                return (src[tally - 1].red + src[tally].red + src[tally + 1].red + src[tally - dim - 1].red + src[tally - dim].red +
                        src[tally - dim + 1].red + src[tally + dim - 1].red + src[tally + dim].red + src[tally + dim + 1].red) / 9;
            case 1:
                return (src[tally - 1].green + src[tally].green + src[tally + 1].green + src[tally - dim - 1].green + src[tally - dim].green +
                        src[tally - dim + 1].green + src[tally + dim - 1].green + src[tally + dim].green + src[tally + dim + 1].green)/9;
            case 2:
                return (src[tally - 1].blue + src[tally].blue + src[tally + 1].blue + src[tally - dim - 1].blue + src[tally - dim].blue +
                        src[tally - dim + 1].blue + src[tally + dim - 1].blue + src[tally + dim].blue + src[tally + dim + 1].blue)/9;
            default:
                return 0;
        }
    }

    /*
     * Averaging the body pixels
     */
    static inline void avgImageBody(int dim, pixel *src, pixel *dst) {
        int i, j, tally;
        tally = dim;

        for (i = 1; i < dim - 1; i++) {
            for (j = 1; j < dim - 1; j++) {
                tally++;
                dst[tally].red = avgBody1(src, 0, tally, dim);
                dst[tally].green = avgBody1(src, 1, tally, dim);
                dst[tally].blue = avgBody1(src, 2, tally, dim);
            }
            tally += 2;
        }
    }

/******************************************************
 * Your different versions of the smooth kernel go here
 ******************************************************/

/*
 * naive_smooth - The naive baseline version of smooth 
 */
    char naive_smooth_descr[] = "naive_smooth: Naive baseline implementation";
    void naive_smooth(int dim, pixel *src, pixel *dst) {
        int i, j;

        for (i = 0; i < dim; i++)
            for (j = 0; j < dim; j++)
                dst[RIDX(i, j, dim)] = avg(dim, i, j, src);
    }

/*
 * smooth - Your current working version of smooth. 
 * IMPORTANT: This is the version you will be graded on
 */
char smooth_descr[] = "smooth: Current working version";
void smooth(int dim, pixel *src, pixel *dst) {

    /*
     * The naive avg() funtion was the real bottleneck, as it had to find the surrounding pixels every time in order to average them
     * We can mitigate this by separating the corners, sides, and body of the image into separate cases.
     *
     * Corner pixels have 4 pixels that need to be averaged. The corner, and the three adjacent pixels
     *
     * Edge pixels have 6 total pixels, the center pixel, and the 5 adjacent ones
     *
     * Body pixels have 9 pixels that need to be averaged, 1 center, 8 body
     *
     * Body         Corner      Edge
     *  1 2 3       1 2         1 2
     *  4 5 6       3 4         3 4
     *  7 8 9                   5 6
     *
     *  So we can divide the corners into a separate function, the sides into a separate function, and the edges into a
     *  separate function, and have them all handled separately with tailor made solutions. Since the image is an
     *  m x n matrix, the rotation algorithm can be derived from a smaller sample matrix (which is what I did with a 5 x 5
     *  matrix), and then used for this assignment.
     */
    avgImageCorners(dim, src, dst);
    avgImageSides(dim, src, dst);
    avgImageBody(dim, src, dst);
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
    }

