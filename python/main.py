#!/usr/bin/python3

from stl_reader import Stl, Triangle, Vec3

if __name__ == '__main__':
    #stl = Stl.read("model.stl")
    stl = Stl.generate_empty()

    stl.add_triangle(Vec3(5, 5, 0), Vec3(0, -5, 0), Vec3(-5, 5, 0))
    stl.add_triangle(Vec3(5, 5, 0), Vec3(-5, 5, 0), Vec3(0, 5, 5))

    print(stl)

    stl.write("model.edit.stl")