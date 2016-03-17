/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   lmbd_convert.h
 * Author: byrdie
 *
 * Created on March 14, 2016, 8:06 PM
 */

#ifndef LMBD_CONVERT_H
#define LMBD_CONVERT_H

#include <stdint.h>
#include <sys/stat.h>
#include <fstream>  // NOLINT(readability/streams)
#include <string>

#include <gflags/gflags.h>
#include <glog/logging.h>
#include <google/protobuf/text_format.h>
#include <lmdb.h>

#include "caffe/include/caffe/util/format.hpp"
#include "caffe/build/src/caffe/proto/caffe.pb.h"
#include "fomod.h"

void open_input_db(char db_path[]);
void open_truth_db(char db_path[]);
void add_to_input_db(int item_id, float image[][SPECTRAL_DIM][SPATIAL_DIM]);
void add_to_truth_db(int item_id, float image[][SPECTRAL_DIM][SPATIAL_DIM]);
void close_input_db();
void close_truth_db();

void convert_dataset(char db_path[], int image[][SPECTRAL_DIM][CHANNELS]);



#endif /* LMBD_CONVERT_H */

