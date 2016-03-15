/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   phomod.h
 * Author: byrdie
 *
 * Created on March 12, 2016, 2:50 PM
 */

#ifndef PHOMOD_H
#define PHOMOD_H

#define CHANNELS 3
#define SPATIAL_DIM 4
#define SPECTRAL_DIM 4

#include <stdlib.h>
#include <iostream>

    void fomod(int plus[], int zero[], int minus[], int cube[][SPECTRAL_DIM][CHANNELS]);
    
    void reverse_fomod(int plus[], int zero[], int minus[], int max_cube[][SPECTRAL_DIM][CHANNELS]);
    

    enum orders {
        PLUS,
        ZERO,
        MINUS
    };



#endif /* PHOMOD_H */
