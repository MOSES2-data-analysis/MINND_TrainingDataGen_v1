#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-Wl,-rpath,/usr/local/cuda/lib64 -Wl,-rpath,/home/byrdie/NetBeansProjects/MINND_TrainingDataGen_v1/MINND_TrainingDataGen_v1_cpp/caffe/build/lib /usr/lib/x86_64-linux-gnu/libhdf5_hl_cpp.so /usr/lib/x86_64-linux-gnu/libhdf5_cpp.so /home/byrdie/NetBeansProjects/MINND_TrainingDataGen_v1/MINND_TrainingDataGen_v1_cpp/caffe/build/lib/libcaffe.so /usr/local/cuda-7.5/lib64/libcudart.so /usr/local/cuda-7.5/lib64/libcublas.so /usr/local/cuda-7.5/lib64/libcurand.so /usr/lib/x86_64-linux-gnu/libglog.so /usr/lib/x86_64-linux-gnu/libgflags.so /usr/lib/x86_64-linux-gnu/libprotobuf.so /usr/lib/x86_64-linux-gnu/libboost_filesystem.so /usr/lib/x86_64-linux-gnu/libboost_system.so -lm /usr/lib/x86_64-linux-gnu/libboost_thread.so /usr/local/cuda-7.5/lib64/libcudnn.so /usr/lib/libblas.so -lpthread -ldl `pkg-config --libs opencv` `pkg-config --libs zlib` /usr/lib/x86_64-linux-gnu/libhdf5.so /usr/lib/x86_64-linux-gnu/libhdf5_hl.so  

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_validate_v1

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_validate_v1: /usr/lib/x86_64-linux-gnu/libhdf5_hl_cpp.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_validate_v1: /usr/lib/x86_64-linux-gnu/libhdf5_cpp.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_validate_v1: /home/byrdie/NetBeansProjects/MINND_TrainingDataGen_v1/MINND_TrainingDataGen_v1_cpp/caffe/build/lib/libcaffe.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_validate_v1: /usr/local/cuda-7.5/lib64/libcudart.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_validate_v1: /usr/local/cuda-7.5/lib64/libcublas.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_validate_v1: /usr/local/cuda-7.5/lib64/libcurand.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_validate_v1: /usr/lib/x86_64-linux-gnu/libglog.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_validate_v1: /usr/lib/x86_64-linux-gnu/libgflags.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_validate_v1: /usr/lib/x86_64-linux-gnu/libprotobuf.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_validate_v1: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_validate_v1: /usr/lib/x86_64-linux-gnu/libboost_system.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_validate_v1: /usr/lib/x86_64-linux-gnu/libboost_thread.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_validate_v1: /usr/local/cuda-7.5/lib64/libcudnn.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_validate_v1: /usr/lib/libblas.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_validate_v1: /usr/lib/x86_64-linux-gnu/libhdf5.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_validate_v1: /usr/lib/x86_64-linux-gnu/libhdf5_hl.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_validate_v1: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_validate_v1 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/home/byrdie/NetBeansProjects/MINND_TrainingDataGen_v1/MINND_TrainingDataGen_v1_cpp/caffe/include -I/usr/local/cuda-7.5/include -I/home/byrdie/NetBeansProjects/MINND_TrainingDataGen_v1/MINND_TrainingDataGen_v1_cpp/caffe/build/src `pkg-config --cflags opencv` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_validate_v1

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
