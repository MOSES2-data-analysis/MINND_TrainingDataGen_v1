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
	${OBJECTDIR}/fomod.o \
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
LDLIBSOPTIONS=-Wl,-rpath,/home/byrdie/NetBeansProjects/MINND_TrainingDataGen_v1/opencv-3.1.0/build/lib /home/byrdie/NetBeansProjects/MINND_TrainingDataGen_v1/opencv-3.1.0/build/lib/libopencv_core.so /home/byrdie/NetBeansProjects/MINND_TrainingDataGen_v1/opencv-3.1.0/build/lib/libopencv_highgui.so /home/byrdie/NetBeansProjects/MINND_TrainingDataGen_v1/opencv-3.1.0/build/lib/libopencv_imgproc.so /home/byrdie/NetBeansProjects/MINND_TrainingDataGen_v1/opencv-3.1.0/build/lib/libopencv_imgcodecs.so

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_trainingdatagen_v1_opencv

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_trainingdatagen_v1_opencv: /home/byrdie/NetBeansProjects/MINND_TrainingDataGen_v1/opencv-3.1.0/build/lib/libopencv_core.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_trainingdatagen_v1_opencv: /home/byrdie/NetBeansProjects/MINND_TrainingDataGen_v1/opencv-3.1.0/build/lib/libopencv_highgui.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_trainingdatagen_v1_opencv: /home/byrdie/NetBeansProjects/MINND_TrainingDataGen_v1/opencv-3.1.0/build/lib/libopencv_imgproc.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_trainingdatagen_v1_opencv: /home/byrdie/NetBeansProjects/MINND_TrainingDataGen_v1/opencv-3.1.0/build/lib/libopencv_imgcodecs.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_trainingdatagen_v1_opencv: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_trainingdatagen_v1_opencv ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/fomod.o: fomod.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/home/byrdie/NetBeansProjects/MINND_TrainingDataGen_v1/opencv-3.1.0/include -I/home/byrdie/NetBeansProjects/MINND_TrainingDataGen_v1/opencv-3.1.0/modules/core/include -I/home/byrdie/NetBeansProjects/MINND_TrainingDataGen_v1/opencv-3.1.0/modules/highgui/include -I/home/byrdie/NetBeansProjects/MINND_TrainingDataGen_v1/opencv-3.1.0/modules/imgcodecs/include -I/home/byrdie/NetBeansProjects/MINND_TrainingDataGen_v1/opencv-3.1.0/modules/imgproc/include -I/home/byrdie/NetBeansProjects/MINND_TrainingDataGen_v1/opencv-3.1.0/modules/videoio/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/fomod.o fomod.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/home/byrdie/NetBeansProjects/MINND_TrainingDataGen_v1/opencv-3.1.0/include -I/home/byrdie/NetBeansProjects/MINND_TrainingDataGen_v1/opencv-3.1.0/modules/core/include -I/home/byrdie/NetBeansProjects/MINND_TrainingDataGen_v1/opencv-3.1.0/modules/highgui/include -I/home/byrdie/NetBeansProjects/MINND_TrainingDataGen_v1/opencv-3.1.0/modules/imgcodecs/include -I/home/byrdie/NetBeansProjects/MINND_TrainingDataGen_v1/opencv-3.1.0/modules/imgproc/include -I/home/byrdie/NetBeansProjects/MINND_TrainingDataGen_v1/opencv-3.1.0/modules/videoio/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_trainingdatagen_v1_opencv

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
