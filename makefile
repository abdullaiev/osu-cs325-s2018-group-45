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
<<<<<<< HEAD
HEADERS = City.h Node.h SpatialTree.h Problem.h Solution.h SolveTSP.h
=======
HEADERS = City.h Node.h SpatialTree.h Problem.h Solution.h TSPExactSolver.h #Tour.h SolveTSP.h
>>>>>>> 11ffff1b872845e09de66036fe279636670bef3a

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
