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
CND_PLATFORM=GNU-Linux-x86
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
	${OBJECTDIR}/aleatorio.o \
	${OBJECTDIR}/analise.o \
	${OBJECTDIR}/analise_incremental.o \
	${OBJECTDIR}/analise_termica.o \
	${OBJECTDIR}/barra1d.o \
	${OBJECTDIR}/barra2d.o \
	${OBJECTDIR}/barra3d.o \
	${OBJECTDIR}/c_contorno.o \
	${OBJECTDIR}/elcal1d2n.o \
	${OBJECTDIR}/elcal2d4n.o \
	${OBJECTDIR}/elcal2d4nnl.o \
	${OBJECTDIR}/elcal2d8n.o \
	${OBJECTDIR}/elemento.o \
	${OBJECTDIR}/elemento2d3n.o \
	${OBJECTDIR}/elemento2d4n.o \
	${OBJECTDIR}/elemento2d8n.o \
	${OBJECTDIR}/elemento2d9n.o \
	${OBJECTDIR}/elemento3d.o \
	${OBJECTDIR}/elemento3d3n.o \
	${OBJECTDIR}/elemento_poligonal2d.o \
	${OBJECTDIR}/elemento_poligonal2d5n.o \
	${OBJECTDIR}/elemento_poligonal2d6n.o \
	${OBJECTDIR}/elemento_poligonal2d7n.o \
	${OBJECTDIR}/elemento_poligonal2d8n.o \
	${OBJECTDIR}/iscal1d.o \
	${OBJECTDIR}/iscal2d.o \
	${OBJECTDIR}/isop2d.o \
	${OBJECTDIR}/mat_linear_elastico.o \
	${OBJECTDIR}/mat_termico.o \
	${OBJECTDIR}/mat_termico_nao_linear.o \
	${OBJECTDIR}/material.o \
	${OBJECTDIR}/mef.o \
	${OBJECTDIR}/nlcal2d4n.o \
	${OBJECTDIR}/no.o \
	${OBJECTDIR}/no1d.o \
	${OBJECTDIR}/no2d.o \
	${OBJECTDIR}/no3d.o \
	${OBJECTDIR}/tubo.o \
	${OBJECTDIR}/ufesApp.o \
	${OBJECTDIR}/ufesMain.o \
	${OBJECTDIR}/viga2d.o \
	${OBJECTDIR}/viga3d.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=`wx-config --cxxflags` 
CXXFLAGS=`wx-config --cxxflags` 

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=`wx-config --libs` 

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ufes

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ufes: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ufes ${OBJECTFILES} ${LDLIBSOPTIONS} `wx-config --libs`

${OBJECTDIR}/aleatorio.o: aleatorio.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/aleatorio.o aleatorio.cpp

${OBJECTDIR}/analise.o: analise.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/analise.o analise.cpp

${OBJECTDIR}/analise_incremental.o: analise_incremental.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/analise_incremental.o analise_incremental.cpp

${OBJECTDIR}/analise_termica.o: analise_termica.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/analise_termica.o analise_termica.cpp

${OBJECTDIR}/barra1d.o: barra1d.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/barra1d.o barra1d.cpp

${OBJECTDIR}/barra2d.o: barra2d.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/barra2d.o barra2d.cpp

${OBJECTDIR}/barra3d.o: barra3d.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/barra3d.o barra3d.cpp

${OBJECTDIR}/c_contorno.o: c_contorno.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/c_contorno.o c_contorno.cpp

${OBJECTDIR}/elcal1d2n.o: elcal1d2n.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/elcal1d2n.o elcal1d2n.cpp

${OBJECTDIR}/elcal2d4n.o: elcal2d4n.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/elcal2d4n.o elcal2d4n.cpp

${OBJECTDIR}/elcal2d4nnl.o: elcal2d4nnl.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/elcal2d4nnl.o elcal2d4nnl.cpp

${OBJECTDIR}/elcal2d8n.o: elcal2d8n.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/elcal2d8n.o elcal2d8n.cpp

${OBJECTDIR}/elemento.o: elemento.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/elemento.o elemento.cpp

${OBJECTDIR}/elemento2d3n.o: elemento2d3n.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/elemento2d3n.o elemento2d3n.cpp

${OBJECTDIR}/elemento2d4n.o: elemento2d4n.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/elemento2d4n.o elemento2d4n.cpp

${OBJECTDIR}/elemento2d8n.o: elemento2d8n.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/elemento2d8n.o elemento2d8n.cpp

${OBJECTDIR}/elemento2d9n.o: elemento2d9n.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/elemento2d9n.o elemento2d9n.cpp

${OBJECTDIR}/elemento3d.o: elemento3d.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/elemento3d.o elemento3d.cpp

${OBJECTDIR}/elemento3d3n.o: elemento3d3n.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/elemento3d3n.o elemento3d3n.cpp

${OBJECTDIR}/elemento_poligonal2d.o: elemento_poligonal2d.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/elemento_poligonal2d.o elemento_poligonal2d.cpp

${OBJECTDIR}/elemento_poligonal2d5n.o: elemento_poligonal2d5n.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/elemento_poligonal2d5n.o elemento_poligonal2d5n.cpp

${OBJECTDIR}/elemento_poligonal2d6n.o: elemento_poligonal2d6n.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/elemento_poligonal2d6n.o elemento_poligonal2d6n.cpp

${OBJECTDIR}/elemento_poligonal2d7n.o: elemento_poligonal2d7n.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/elemento_poligonal2d7n.o elemento_poligonal2d7n.cpp

${OBJECTDIR}/elemento_poligonal2d8n.o: elemento_poligonal2d8n.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/elemento_poligonal2d8n.o elemento_poligonal2d8n.cpp

${OBJECTDIR}/iscal1d.o: iscal1d.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/iscal1d.o iscal1d.cpp

${OBJECTDIR}/iscal2d.o: iscal2d.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/iscal2d.o iscal2d.cpp

${OBJECTDIR}/isop2d.o: isop2d.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/isop2d.o isop2d.cpp

${OBJECTDIR}/mat_linear_elastico.o: mat_linear_elastico.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/mat_linear_elastico.o mat_linear_elastico.cpp

${OBJECTDIR}/mat_termico.o: mat_termico.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/mat_termico.o mat_termico.cpp

${OBJECTDIR}/mat_termico_nao_linear.o: mat_termico_nao_linear.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/mat_termico_nao_linear.o mat_termico_nao_linear.cpp

${OBJECTDIR}/material.o: material.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/material.o material.cpp

${OBJECTDIR}/mef.o: mef.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/mef.o mef.cpp

${OBJECTDIR}/nlcal2d4n.o: nlcal2d4n.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/nlcal2d4n.o nlcal2d4n.cpp

${OBJECTDIR}/no.o: no.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/no.o no.cpp

${OBJECTDIR}/no1d.o: no1d.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/no1d.o no1d.cpp

${OBJECTDIR}/no2d.o: no2d.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/no2d.o no2d.cpp

${OBJECTDIR}/no3d.o: no3d.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/no3d.o no3d.cpp

${OBJECTDIR}/tubo.o: tubo.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tubo.o tubo.cpp

${OBJECTDIR}/ufesApp.o: ufesApp.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ufesApp.o ufesApp.cpp

${OBJECTDIR}/ufesMain.o: ufesMain.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ufesMain.o ufesMain.cpp

${OBJECTDIR}/viga2d.o: viga2d.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/viga2d.o viga2d.cpp

${OBJECTDIR}/viga3d.o: viga3d.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/viga3d.o viga3d.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ufes

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
