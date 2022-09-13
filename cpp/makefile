mainfile=main.cpp
headers=stl_reader.hpp
sources=stl_reader.cpp
compiler=g++
standard=gnu++17
flags=-Wall
output=main

all: compile run

compile: ${mainfile} ${headers} ${sources}
	${compiler} ${mainfile} ${sources} -std=${standard} ${flags} -o ${output}

run: ${output}
	./${output}
