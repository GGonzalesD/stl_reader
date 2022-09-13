#ifndef __STL_READER_H__
#define __STL_READER_H__

#include <stdio.h>

#define MODEL struct Model
#define VEC3 struct Vec3
#define TRIANGLE struct Triangle

VEC3 {
    float x, y, z;
};

TRIANGLE {
    struct Vec3 normal;
    struct Vec3 vertex[3];
    unsigned short attrib;
};

MODEL {
    unsigned char header[81];
    unsigned int size;
    struct Triangle * triangles;
};

void stl_print(MODEL model);
void stl_free(MODEL * model);
MODEL * stl_load(const char * filename);
void stl_save(const char * filename, MODEL * model);

#endif