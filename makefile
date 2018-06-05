#########################################################
# CS 325 - Project Makefile
# Group 45
#########################################################


CXX = g++ -std=c++11

CXXFLAGS += -Wall
CXXFLAGS += -pedantic-errors
CXXFLAGS += -g

# Program Name
PROGRAM = SolveTSP

# Header Files
HEADERS = City.h Node.h SpatialTree.h Problem.h Solution.h TSPExactSolver.h SolveTSP.h

# Source Files
SOURCES = ${HEADERS:.h=.cpp} Main.cpp

# Object Files
OBJECTS = ${SOURCES:.c=.o}

# Documents
DOCUMENTS = README.txt

# ZIP File
ZIP = CS325_group45_${PROGRAM}.zip


default:
	${CXX} ${SOURCES} ${HEADERS} -o ${PROGRAM}

all:
	${CXX} ${CXXFLAGS} ${SOURCES} ${HEADERS} -o ${PROGRAM}

# Executable dependencies
${PROGRAM} : ${OBJECTS} ${HEADERS}
	${CXX} ${OBJECTS} -o ${PROGRAM}

# Object file dependencies
${OBJECTS}: ${SOURCES}
	${CXX} ${CXXFLAGS} -c $(@:.o=.c)	

zip:
	zip ${ZIP} ${SOURCES} ${HEADERS} ${DOCUMENTS} makefile

clean: 
	rm -f ${PROGRAM} *.o *~

clear tour:
	rm -f $(PROGRAM) *.o *~ *.tour*
