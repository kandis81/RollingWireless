## -*- Makefile -*-
##
## User: johnny
## Time: 2023.02.20. 16:46:57
## Makefile created by Oracle Developer Studio.
##
## This file is generated automatically.
##


#### Compiler and tool definitions shared by all build targets #####
CCC = g++
CXX = g++
BASICOPTS = -g
CCFLAGS = $(BASICOPTS) -ggdb -std=c++17 -Wall
CXXFLAGS = $(BASICOPTS) -ggdb -std=c++17 -Wall
CCADMIN = 


# Define the target directories.
TARGETDIR_test=obj


all: $(TARGETDIR_test)/test

## Target: test
OBJS_test =  \
	$(TARGETDIR_test)/LifeSpace.o \
	$(TARGETDIR_test)/Animals.o \
	$(TARGETDIR_test)/main.o \
	$(TARGETDIR_test)/Ant.o
USERLIBS_test = $(SYSLIBS_test) 
DEPLIBS_test =  
LDLIBS_test = $(USERLIBS_test)


# Link or archive
$(TARGETDIR_test)/test: $(TARGETDIR_test) $(OBJS_test) $(DEPLIBS_test)
	$(LINK.cc) $(CCFLAGS_test) $(CPPFLAGS_test) -o $@ $(OBJS_test) $(LDLIBS_test)


# Compile source files into .o files
$(TARGETDIR_test)/LifeSpace.o: $(TARGETDIR_test) LifeSpace.cpp
	$(COMPILE.cc) $(CCFLAGS_test) $(CPPFLAGS_test) -o $@ LifeSpace.cpp

$(TARGETDIR_test)/Animals.o: $(TARGETDIR_test) Animals.cpp
	$(COMPILE.cc) $(CCFLAGS_test) $(CPPFLAGS_test) -o $@ Animals.cpp

$(TARGETDIR_test)/main.o: $(TARGETDIR_test) main.cpp
	$(COMPILE.cc) $(CCFLAGS_test) $(CPPFLAGS_test) -o $@ main.cpp

$(TARGETDIR_test)/Ant.o: $(TARGETDIR_test) Ant.cpp
	$(COMPILE.cc) $(CCFLAGS_test) $(CPPFLAGS_test) -o $@ Ant.cpp



#### Clean target deletes all generated files ####
clean:
	rm -f \
		$(TARGETDIR_test)/test \
		$(TARGETDIR_test)/LifeSpace.o \
		$(TARGETDIR_test)/Animals.o \
		$(TARGETDIR_test)/main.o \
		$(TARGETDIR_test)/Ant.o
	$(CCADMIN)
	rm -f -r $(TARGETDIR_test)


# Create the target directory (if needed)
$(TARGETDIR_test):
	mkdir -p $(TARGETDIR_test)


# Enable dependency checking
.KEEP_STATE:
.KEEP_STATE_FILE:.make.state.GNU-amd64-Linux

