#include <stdio.h>

#include "stl_reader.h"

int main(int args, const char ** argv){
    MODEL * model = stl_load("model.stl");

    stl_print(*model);

    stl_save("model.stl", model);
    
    stl_free(model);
    return 0;
}