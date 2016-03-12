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
#include "pcg_basic.h"
#include "gnuplot_i.h"

/*
 * 
 */
int main(int argc, char** argv) {

    /* Create new gnuplot session */
    gnuplot_ctrl * h;
    h = gnuplot_init();

    /* Seed for PRNG */
    pcg32_random_t rng;
    pcg32_srandom_r(&rng, 42u, 25u);

    /* Max value of each pixel */
    int max_dn = 0xFF;
    
    //struct pixel

    /* Store the dimensions of the input data cube */
    int x_dim = 4;
    int lambda_dim = 4;
    int total_pix = x_dim * lambda_dim;

    /* Allocate memory for the input cube */
    int cube[x_dim][lambda_dim];
    memset(cube, 0, x_dim * lambda_dim * sizeof (int));

    /* Find random coordinates for next point */
    int x = (int) pcg32_boundedrand_r(&rng, x_dim);
    int y = (int) pcg32_boundedrand_r(&rng, lambda_dim);

    /* Find intensity of the activated pixel */
    int I = (int) pcg32_boundedrand_r(&rng, max_dn);

    /* Activate pixel */
    cube[x][y] = I;

    /* Save image to disk */
    char * image_path = "/home/byrdie/NetBeansProjects/MINND_TrainingDataGen_v1/MINND_TrainingDataGen_v1/test.bin";
    FILE * fp = fopen(image_path, "wb");
    fwrite(cube, sizeof (int), total_pix, fp);
    fclose(fp);

    /* Plot image for testing */
    char cmd_str[200];
    sprintf(cmd_str, "plot '%s' binary array=(%d,%d) ", image_path, x_dim, lambda_dim);
    strcat(cmd_str, "flipy format='%%uchar%%uchar%%uchar%%uchar' with image");
    printf(cmd_str);
    gnuplot_cmd(h, cmd_str);

    sleep(1000);
    
    return (EXIT_SUCCESS);
}

