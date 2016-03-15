/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Roy Smart
 *
 * Created on March 12, 2016, 11:22 AM
 */

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "pcg_basic.h"
#include "gnuplot_i.h"
#include "fomod.h"

/*
 * 
 */
int main(int argc, char** argv) {

    /* Create new gnuplot session */
    gnuplot_ctrl * h;
    h = gnuplot_init();

    /* Seed for PRNG */
    pcg32_random_t rng;
    //    pcg32_srandom_r(&rng, 37u, 25u);
    pcg32_srandom_r(&rng, time(NULL) ^ (intptr_t) & printf, 127u);

    /* Max value of each pixel */
    int max_dn = 0xFF;

    //struct pixel

    /* Store the dimensions of the input data cube */
    int channels = 3;
    int x_dim = 4;
    int lambda_dim = 4;
    int total_pix = x_dim * lambda_dim;

    /* Allocate memory for the input cube */
    int cube[x_dim][lambda_dim][channels];
    memset(cube, 0, channels * x_dim * lambda_dim * sizeof (int));

    /* Find random coordinates for next point */
    int x = (int) pcg32_boundedrand_r(&rng, x_dim);
    int y = (int) pcg32_boundedrand_r(&rng, lambda_dim);

    //    int x = 0;
    //    int y = 3;

    /* Find intensity of the activated pixel */
    int I = (int) pcg32_boundedrand_r(&rng, max_dn);

    /* Activate randomized pixel */
    cube[x][y][PLUS] = I;
    cube[x][y][ZERO] = I;
    cube[x][y][MINUS] = I;

    /* Save cube to disk */
    char * cube_path = "/home/byrdie/NetBeansProjects/MINND_TrainingDataGen_v1/MINND_TrainingDataGen_v1/training_data/cube.bin";
    FILE * fp = fopen(cube_path, "wb");
    fwrite(cube, sizeof (int), total_pix*channels, fp);
    fclose(fp);

    /* Plot input cube for testing */
    char cmd_str[200];
    sprintf(cmd_str, "plot '%s' binary array=(%d,%d) ", cube_path, x_dim, lambda_dim);
    strcat(cmd_str, " rotation=-90d format='%%int%%int%%int' with rgbimage");
    //    printf(cmd_str);
    gnuplot_cmd(h, cmd_str);

    /* Allocate space for results of MOSES forward model */
    int outboard_sz = x_dim + lambda_dim - 1;
    int plus[outboard_sz];
    int zero[x_dim];
    int minus[outboard_sz];

    /* Execute MOSES forward model */
    fomod(channels, x_dim, lambda_dim, plus, zero, minus, cube);

    /* Save results of forward model to disk */
    /* Zero order */
    char * zero_path = "/home/byrdie/NetBeansProjects/MINND_TrainingDataGen_v1/MINND_TrainingDataGen_v1/training_data/zero.bin";
    fp = fopen(zero_path, "wb");
    fwrite(zero, sizeof (int), x_dim, fp);
    fclose(fp);
    /* Positive Order*/
    char * plus_path = "/home/byrdie/NetBeansProjects/MINND_TrainingDataGen_v1/MINND_TrainingDataGen_v1/training_data/plus.bin";
    fp = fopen(plus_path, "wb");
    fwrite(plus, sizeof (int), outboard_sz, fp);
    fclose(fp);
    /* Positive Order*/
    char * minus_path = "/home/byrdie/NetBeansProjects/MINND_TrainingDataGen_v1/MINND_TrainingDataGen_v1/training_data/minus.bin";
    fp = fopen(minus_path, "wb");
    fwrite(minus, sizeof (int), outboard_sz, fp);
    fclose(fp);

    /* Plot the result */
    gnuplot_cmd(h, "set term wxt 1"); // Set to figure 1
    //    gnuplot_cmd(h, "set xrange [0:4]");
    gnuplot_cmd(h, "plot '%s' binary array=(%d) format='%%int' with lines", zero_path, x_dim);
    gnuplot_cmd(h, "set term wxt 2"); // Set to figure 2
    //    gnuplot_cmd(h, "set xrange [0:4]");
    gnuplot_cmd(h, "plot '%s' binary array=(%d) format='%%int' with lines", minus_path, outboard_sz);


    /* Execute reverse forward model to put in format for Neural Network */
    int cnn_cube[x_dim][lambda_dim][channels];
    memset(cnn_cube, 0, channels * x_dim * lambda_dim * sizeof (int));
    reverse_fomod(channels, x_dim, lambda_dim, plus, zero, minus, cnn_cube);

    /* Save CNN input cube to disk */
    char * cnn_cube_path = "/home/byrdie/NetBeansProjects/MINND_TrainingDataGen_v1/MINND_TrainingDataGen_v1/training_data/cnn_cube.bin";
    fp = fopen(cnn_cube_path, "wb");
    fwrite(cnn_cube, sizeof (int), total_pix*channels, fp);
    fclose(fp);

    /* Plot input cube for testing */
    cmd_str[200];
    sprintf(cmd_str, "plot '%s' binary array=(%d,%d) ", cnn_cube_path, x_dim, lambda_dim);
    strcat(cmd_str, " rotation=-90d format='%%int%%int%%int' with rgbimage");
    //    printf(cmd_str);
    gnuplot_cmd(h, cmd_str);

    /* Stop program until we're finished looking at the results */
    pause();

    return (EXIT_SUCCESS);
}

