# Project: Undertale

CPP      = g++.exe
CC       = gcc.exe
WINDRES  = windres.exe
OBJ      = source/MainMenu.o utils/UtilData.o
LINKOBJ  = source/MainMenu.o utils/UtilData.o
# LIBS	 = 
# INCS	 = 
BIN      = "A_Dance_of_Fire_and_Ice.exe"
CXXFLAGS = $(CXXINCS) 
# CFLAGS   = 

.PHONY: all all-before all-after build clean clean-custom

build: all-before $(BIN) all-after

# clean: clean-custom
# 	del /s *.o
# 	$(RM_OBJ)
# 	$(RM_BIN)

all: clean build 

source/MainMenu.o: source/MainMenu.c
	$(CC) -c source/MainMenu.c -o source/MainMenu.o 

utils/UtilData.o: utils/UtilData.c
	$(CC) -c utils/UtilData.c -o utils/UtilData.o
	
# Automatically Run
$(BIN): $(OBJ)
	$(CC) $(LINKOBJ) -o $(BIN) 