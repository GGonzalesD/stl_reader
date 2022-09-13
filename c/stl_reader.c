#include "stl_reader.h"
#include <stdlib.h>

void __print_vector(VEC3 vec){
    printf("Vec3(%f, %f, %f)\n", vec.x, vec.y, vec.z);
}

void __print_triangle(TRIANGLE triangle){
    printf("Normal: ");
    __print_vector(triangle.normal);
    for(int i=0; i<3; i++){
        printf("Vertex[%d]: ", i);
        __print_vector(triangle.vertex[i]);
    }
    printf("Attrib: %u\n", triangle.attrib);
}

void __read_vec3_from_file(VEC3* vec3, FILE * file){
    fread(&vec3->x, sizeof(float), 1, file);
    fread(&vec3->y, sizeof(float), 1, file);
    fread(&vec3->z, sizeof(float), 1, file);
}

void __write_vec3_from_file(VEC3* vec3, FILE * file){
    fwrite(&vec3->x, sizeof(float), 1, file);
    fwrite(&vec3->y, sizeof(float), 1, file);
    fwrite(&vec3->z, sizeof(float), 1, file);
}

void __read_triangle_from_file(TRIANGLE* triangle, FILE * file){
    __read_vec3_from_file(&triangle->normal, file);
    for(int i=0; i<3; i++)
        __read_vec3_from_file(&triangle->vertex[i], file);
    fread(&triangle->attrib, sizeof(unsigned short), 1, file);
}

void __write_triangle_from_file(TRIANGLE* triangle, FILE * file){
    __write_vec3_from_file(&triangle->normal, file);
    for(int i=0; i<3; i++)
        __write_vec3_from_file(&triangle->vertex[i], file);
    fwrite(&triangle->attrib, sizeof(unsigned short), 1, file);
}

MODEL * stl_load(const char * filename){
    FILE * file = fopen(filename, "rb");

    MODEL * model = (MODEL*)malloc(sizeof(MODEL));
    model->header[80] = 0;

    fread(model->header, sizeof(unsigned char), 80, file);
    fread(&model->size, sizeof(unsigned int), 1, file);

    model->triangles = (TRIANGLE*)malloc(sizeof(TRIANGLE) * model->size);
    
    for(unsigned int i=0; i < model->size; i++){
        __read_triangle_from_file(&model->triangles[i], file);
    }

    fclose(file);
    return model;
}

void stl_save(const char * filename, MODEL * model){
    FILE * file = fopen(filename, "wb");

    fwrite(model->header, sizeof(unsigned char), 80, file);
    fwrite(&model->size, sizeof(unsigned int), 1, file);

    for(unsigned int i=0; i < model->size; i++){
        __write_triangle_from_file(&model->triangles[i], file);
    }

    fclose(file);
}

void stl_free(MODEL * model){
    free(model->triangles);
    free(model);
    model = NULL;
}

void stl_print(MODEL model){
    printf("Header: %s\n", model.header);
    printf("Triangles: %u\n", model.size);
    for(unsigned int i=0; i < model.size; i++){
        printf("Triangle #%u\n", i);
        __print_triangle(model.triangles[i]);
    }
}