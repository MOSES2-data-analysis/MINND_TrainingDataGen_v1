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
LDLIBSOPTIONS=/usr/lib/x86_64-linux-gnu/libboost_filesystem.a /usr/lib/x86_64-linux-gnu/libboost_system.a /usr/lib/x86_64-linux-gnu/libgflags.a /usr/lib/x86_64-linux-gnu/libglog.a /usr/lib/x86_64-linux-gnu/libhdf5_cpp.a /usr/lib/x86_64-linux-gnu/libhdf5_hl_cpp.a /usr/lib/x86_64-linux-gnu/libprotobuf.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_validate_v1

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_validate_v1: /usr/lib/x86_64-linux-gnu/libboost_filesystem.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_validate_v1: /usr/lib/x86_64-linux-gnu/libboost_system.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_validate_v1: /usr/lib/x86_64-linux-gnu/libgflags.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_validate_v1: /usr/lib/x86_64-linux-gnu/libglog.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_validate_v1: /usr/lib/x86_64-linux-gnu/libhdf5_cpp.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_validate_v1: /usr/lib/x86_64-linux-gnu/libhdf5_hl_cpp.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_validate_v1: /usr/lib/x86_64-linux-gnu/libprotobuf.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_validate_v1: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/minnd_validate_v1 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

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
