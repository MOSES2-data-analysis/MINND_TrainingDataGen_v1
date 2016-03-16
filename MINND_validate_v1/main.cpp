
/* 
 * File:   main.cpp
 * Author: byrdie
 *
 * Created on March 15, 2016, 6:41 PM
 */

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <iosfwd>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "caffe/caffe.hpp"

using std::string;
using namespace caffe;

/*
 * 
 */
int main(int argc, char** argv) {

    /* Set up directories */
    string model_file = "/home/byrdie/NetBeansProjects/MINND_TrainingDataGen_v1/MINND_v1/minnd_train_test.prototxt";
    string trained_file = "/home/byrdie/NetBeansProjects/MINND_TrainingDataGen_v1/MINND_v1/MINND_v1_iter_10000.solverstate";

    shared_ptr<Net<float> > net_;
    
    /* Enable GPU mode */
    Caffe::set_mode(Caffe::GPU);

    /* Load the network. */
    net_.reset(new Net<float>(model_file, TEST));
    net_->CopyTrainedLayersFrom(trained_file);

    return 0;
}

