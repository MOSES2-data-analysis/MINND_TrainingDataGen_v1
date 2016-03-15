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
	${OBJECTDIR}/lmbd_convert.o \
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
LDLIBSOPTIONS=-Lcaffe/src -Lcaffe/src/proto `pkg-config --libs protobuf` `pkg-config --libs libglog` `pkg-config --libs libgflags` -lboost_system -lboost_filesystem -lhdf5 -lhdf5_hl -lm  /usr/lib/x86_64-linux-gnu/libboost_filesystem.a /usr/lib/x86_64-linux-gnu/libboost_filesystem.so /usr/lib/x86_64-linux-gnu/libboost_system.a /usr/lib/x86_64-linux-gnu/libboost_system.so /usr/lib/x86_64-linux-gnu/libhdf5_cpp.a /usr/lib/x86_64-linux-gnu/libhdf5_cpp.so /usr/lib/x86_64-linux-gnu/libhdf5_hl_cpp.a /usr/lib/x86_64-linux-gnu/libhdf5_hl_cpp.so caffe/build/lib/libcaffe.a caffe/build/lib/libcaffe.so `pkg-config --libs protobuf-lite` /usr/lib/x86_64-linux-gnu/libprotobuf.a /usr/lib/x86_64-linux-gnu/libprotobuf.so /usr/lib/x86_64-linux-gnu/libglog.a /usr/lib/x86_64-linux-gnu/libglog.so /usr/lib/x86_64-linux-gnu/liblmdb.a /usr/lib/x86_64-linux-gnu/liblmdb.so  

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_trainingdatagen_v1_cpp

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_trainingdatagen_v1_cpp: /usr/lib/x86_64-linux-gnu/libboost_filesystem.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_trainingdatagen_v1_cpp: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_trainingdatagen_v1_cpp: /usr/lib/x86_64-linux-gnu/libboost_system.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_trainingdatagen_v1_cpp: /usr/lib/x86_64-linux-gnu/libboost_system.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_trainingdatagen_v1_cpp: /usr/lib/x86_64-linux-gnu/libhdf5_cpp.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_trainingdatagen_v1_cpp: /usr/lib/x86_64-linux-gnu/libhdf5_cpp.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_trainingdatagen_v1_cpp: /usr/lib/x86_64-linux-gnu/libhdf5_hl_cpp.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_trainingdatagen_v1_cpp: /usr/lib/x86_64-linux-gnu/libhdf5_hl_cpp.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_trainingdatagen_v1_cpp: caffe/build/lib/libcaffe.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_trainingdatagen_v1_cpp: caffe/build/lib/libcaffe.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_trainingdatagen_v1_cpp: /usr/lib/x86_64-linux-gnu/libprotobuf.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_trainingdatagen_v1_cpp: /usr/lib/x86_64-linux-gnu/libprotobuf.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_trainingdatagen_v1_cpp: /usr/lib/x86_64-linux-gnu/libglog.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_trainingdatagen_v1_cpp: /usr/lib/x86_64-linux-gnu/libglog.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_trainingdatagen_v1_cpp: /usr/lib/x86_64-linux-gnu/liblmdb.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_trainingdatagen_v1_cpp: /usr/lib/x86_64-linux-gnu/liblmdb.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_trainingdatagen_v1_cpp: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_trainingdatagen_v1_cpp ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/fomod.o: fomod.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Icaffe/include -Icaffe/build/src `pkg-config --cflags protobuf` `pkg-config --cflags libglog` `pkg-config --cflags libgflags` `pkg-config --cflags protobuf-lite` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/fomod.o fomod.cpp

${OBJECTDIR}/lmbd_convert.o: lmbd_convert.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Icaffe/include -Icaffe/build/src `pkg-config --cflags protobuf` `pkg-config --cflags libglog` `pkg-config --cflags libgflags` `pkg-config --cflags protobuf-lite` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lmbd_convert.o lmbd_convert.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Icaffe/include -Icaffe/build/src `pkg-config --cflags protobuf` `pkg-config --cflags libglog` `pkg-config --cflags libgflags` `pkg-config --cflags protobuf-lite` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_trainingdatagen_v1_cpp

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
