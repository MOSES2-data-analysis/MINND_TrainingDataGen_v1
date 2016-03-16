
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
    string model_file = "/home/byrdie/NetBeansProjects/MINND_TrainingDataGen_v1/MINND_v1/minnd_deploy.prototxt";
    string trained_file = "/home/byrdie/NetBeansProjects/MINND_TrainingDataGen_v1/MINND_v1/MINND_v1_iter_10000.solverstate";

    /* Variable declaration */
    shared_ptr<Net<float> > net_; // Neural Network model
    int num_channels_;

    /* Enable GPU mode */
    Caffe::set_mode(Caffe::GPU);

    /* Load the network. */
    net_.reset(new Net<float>(model_file, TEST));
    net_->CopyTrainedLayersFrom(trained_file);

//    CHECK_EQ(net_->num_inputs(), 1) << "Network should have exactly one input.";
//    CHECK_EQ(net_->num_outputs(), 1) << "Network should have exactly one output.";

    return 0;
}

