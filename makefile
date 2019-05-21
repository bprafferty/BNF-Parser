##################################################################
#                   -- Program Assignment #3 -- 
#          Brian Rafferty -- cssc0475 -- redID: 816988452
##################################################################
COMPILER=g++
FLAGS=-c -Wall

SRCFILE=exp.cpp
OBJFILE=$(SRCFILE:.cpp=.o)
EXE=exp

all: $(SRCFILE) $(EXE)
	
$(EXE): $(OBJFILE)
	$(COMPILER) $(OBJFILE) -o $@

.cpp.o:
	$(COMPILER) $(FLAGS) $< -o $@

#######################[ EOF: makefile ]##########################