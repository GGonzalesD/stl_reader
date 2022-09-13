#include <iostream>
#include <fstream>

#include "stl_reader.hpp"

int main(int argc, const char ** argv){

    stl::Model model = stl::Model::read("model.stl");

    std::cout << model << std::endl;

    model.write("model.edit.stl");

}