BIN = bin/main
CC = g++
FLAGS = -Wall -pedantic -std=c++17
INC = -I common/include
LOC_LIB = common/linux_x86_64/libGLEW.a -lglfw
SYS_LIB = -lglut -lGL -lGLU
SRC = $(wildcard src/*.cpp)

all:
	@mkdir -p bin  # Esto crea el directorio bin si no existe
	@echo
	@echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	@echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~Building GNU/LINUX 64-bit~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	@echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	@echo
	${CC} ${FLAGS} -o ${BIN} ${SRC} ${INC} ${LOC_LIB} ${SYS_LIB}
