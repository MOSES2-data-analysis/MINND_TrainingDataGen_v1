#! /bin/bash

#rm -rf /minnd/lmdb/train/input/
#rm -rf /minnd/lmdb/train/truth/
rm -rf /minnd/lmdb/test/input/
rm -rf /minnd/lmdb/test/truth/

#../MINND_TrainingDataGen_v1_cpp/caffe/build/tools/convert_imageset / /minnd/images/train/input/index.txt /minnd/lmdb/train/input/
#../MINND_TrainingDataGen_v1_cpp/caffe/build/tools/convert_imageset / /minnd/images/train/truth/index.txt /minnd/lmdb/train/truth/
../MINND_TrainingDataGen_v1_cpp/caffe/build/tools/convert_imageset / /minnd/images/test/input/index.txt /minnd/lmdb/test/input/
../MINND_TrainingDataGen_v1_cpp/caffe/build/tools/convert_imageset / /minnd/images/test/truth/index.txt /minnd/lmdb/test/truth/
