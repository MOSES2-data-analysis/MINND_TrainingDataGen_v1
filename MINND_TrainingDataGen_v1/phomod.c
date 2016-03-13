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

#include "phomod.h"

void phomod(int spatial_dim, int spectral_dim, int plus[], int zero[], int minus[], int cube[][spectral_dim]) {

    printf("\n");

    /* Construct zero order image */
    /* Loop through spatial coordinate */
    for (int i = 0; i < spatial_dim; i++) {

        int sum = 0; // Intermediate variable to store the sum of each column

        /* Sum across each spectral component */
        for (int j = 0; j < spectral_dim; j++) {
            sum += cube[i][j];
        }

        printf("%d \n", sum);
        zero[i] = sum; // Put the results of the sum into the output array
    }

    printf("\n");

    /* Construct positive order image */
    for (int m = 0; m < (spatial_dim + spectral_dim - 1); m++) {

        int sum = 0; // Store the sum of each spectral direction

        /* Sum across spectral dimension */
        for (int n = 0; n < spectral_dim; n++) {

            int i = n + (m - (spectral_dim - 1));
            int j = n;


            if (i >= 0 && i < spatial_dim) {
                sum += cube[i][j];
            }

        }

        plus[m] = sum;
        printf("%d \n", sum);
    }
    
    printf("\n");

    /* Construct negative order image */
    for (int m = 0; m < (spatial_dim + spectral_dim - 1); m++) {

        int sum = 0; // Store the sum of each spectral direction

        /* Sum across spectral dimension */
        for (int n = 0; n < spectral_dim; n++) {

            int i = m - n;
            int j = n;


            if (i >= 0 && i < spatial_dim) {
                sum += cube[i][j];
            }

        }

        minus[m] = sum;
        printf("%d \n", sum);
    }
}
