CXX=g++ 
CXXFLAGS=-std=c++14 -Wall -O -g -MMD -Werror=vla # use -MMD to generate dependencies
SOURCES=$(wildcard *.cc)   # list of all .cc files in the current directory
PLAYERS1= player/shade.cc 
PLAYERS2= player/drow.cc
PLAYERS3= player/vampire.cc
PLAYERS4= player/troll.cc
PLAYERS5= player/goblin.cc
ENEMIES1= enemy/dwarf.cc
ENEMIES2= enemy/orcs.cc
OBJECTS=${SOURCES:.cc=.o} ${PLAYERS1:.cc=.o} ${PLAYERS2:.cc=.o} ${PLAYERS3:.cc=.o} ${PLAYERS4:.cc=.o} ${PLAYERS5:.cc=.o} ${ENEMIES1:.cc=.o} ${ENEMIES2:.cc=.o} # .o files depend upon .cc files with same names
DEPENDS=${OBJECTS:.o=.d}   # .d file is list of dependencies for corresponding .cc file
EXEC=cc3k

# First target in the makefile is the default target.
$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -g $(OBJECTS) -o $(EXEC)

%.o: %.cc 
	$(CXX) -c -o $@ $< $(CXXFLAGS) 

-include ${DEPENDS}

.PHONY: clean
clean:
	rm  -f $(OBJECTS) $(DEPENDS) $(EXEC)
