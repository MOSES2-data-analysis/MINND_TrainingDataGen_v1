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

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>

    void fomod(int channels, int spatial_dim, int spectral_dim, int plus[], int zero[], int minus[], int cube[][spectral_dim][channels]);
    
    void reverse_fomod(int channels, int spatial_dim, int spectral_dim, int plus[], int zero[], int minus[], int cube[][spectral_dim][channels]);
    

    enum orders {
        PLUS,
        ZERO,
        MINUS
    };

#ifdef __cplusplus
}
#endif

#endif /* PHOMOD_H */

