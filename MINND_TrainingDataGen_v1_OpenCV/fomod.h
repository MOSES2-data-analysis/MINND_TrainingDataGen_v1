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
#define SPATIAL_DIM 8
#define SPECTRAL_DIM 8

#include <stdlib.h>
#include <iostream>

    void fomod(float plus[], float zero[], float minus[], float cube[][SPECTRAL_DIM][SPATIAL_DIM]);
    
    void reverse_fomod(float plus[], float zero[], float minus[], float max_cube[][SPECTRAL_DIM][SPATIAL_DIM]);
    

    enum orders {
        PLUS,
        ZERO,
        MINUS
    };



#endif /* PHOMOD_H */

