mainfile=main.c
headers=stl_reader.h
sources=stl_reader.c
compiler=gcc
standard=gnu99
flags=-Wall
output=main

all: compile run

compile: ${mainfile} ${headers} ${sources}
	${compiler} ${mainfile} ${sources} -std=${standard} ${flags} -o ${output}

run: ${output}
	./${output}
