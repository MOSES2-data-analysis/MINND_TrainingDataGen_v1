/*
 * File: Phomod.c
 * Author: Roy Smart
 * 
 * This is a port of the program phomod.pro originally written in IDL by Charles
 * Kankelborg and Hans Courrier.
 * 
 * This program models how photons are distributed in each of the three spectral
 * orders in the MOSES instrument.
 * 
 * NOTE: As of this writing it is only implemented for two dimensions
 * 
 */

#include "fomod.h"

void fomod(int plus[], int zero[], int minus[], int cube[][SPECTRAL_DIM][CHANNELS]) {

    printf("\n");

    /* Construct zero order image */
    /* Loop through spatial coordinate */
    for (int i = 0; i < SPATIAL_DIM; i++) {

        int sum = 0; // Intermediate variable to store the sum of each column

        /* Sum across each spectral component */
        for (int j = 0; j < SPECTRAL_DIM; j++) {
            sum += cube[i][j][ZERO];
        }

        printf("%d \n", sum);
        zero[i] = sum; // Put the results of the sum into the output array
    }

    printf("\n");

    /* Construct positive order image */
    for (int m = 0; m < (SPATIAL_DIM + SPECTRAL_DIM - 1); m++) {

        int sum = 0; // Store the sum of each spectral direction

        /* Sum across spectral dimension */
        for (int n = 0; n < SPECTRAL_DIM; n++) {

            int i = n + (m - (SPECTRAL_DIM - 1));
            int j = n;


            if (i >= 0 && i < SPATIAL_DIM) {
                sum += cube[i][j][ZERO];
            }

        }

        plus[m] = sum;
        printf("%d \n", sum);
    }

    printf("\n");

    /* Construct negative order image */
    for (int m = 0; m < (SPATIAL_DIM + SPECTRAL_DIM - 1); m++) {

        int sum = 0; // Store the sum of each spectral direction

        /* Sum across spectral dimension */
        for (int n = 0; n < SPECTRAL_DIM; n++) {

            int i = m - n;
            int j = n;


            if (i >= 0 && i < SPATIAL_DIM) {
                sum += cube[i][j][ZERO];
            }

        }

        minus[m] = sum;
        printf("%d \n", sum);
    }
}

/**
 * This program attempts to run the forward model in reverse. Since the forward 
 * model loses information, this function can only describe the maximum possible
 * value of the pixel at every location. Information from each of the 3 orders
 * is encoded into the RGB channels.
 * 
 * @param spatial_dim: Size of spatial dimension in pixels
 * @param spectral_dim: Size of spectral dimension in pixels
 * @param plus: 1D input array containing the positive order results of fomod
 * @param zero
 * @param minus
 * @param cube : 2D Output array
 */
void reverse_fomod(int plus[], int zero[], int minus[], int max_cube[][SPECTRAL_DIM][CHANNELS]) {


    /* Loop across cube */
    for (int i = 0; i < SPATIAL_DIM; i++) {
        for (int j = 0; j < SPECTRAL_DIM; j++) {

            /* postive order: least significant */
            /* negative order: most significant bits */
            max_cube[i][j][PLUS] = plus[(SPATIAL_DIM - 1 - j) + i];
            max_cube[i][j][ZERO] = zero[i];
            max_cube[i][j][MINUS] = minus[i + j];

        }
    }

}