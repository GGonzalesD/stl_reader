#!/usr/bin/python3

from stl_reader import Stl, Triangle, Vec3

if __name__ == '__main__':
    stl = Stl.read("model.stl")

    print(stl)

    stl.triangles.append(
        Triangle(Vec3(0, 0, 1), [Vec3(10, -5, 0), Vec3(0, 5, 0), Vec3(-10, -5, 0)], 1)
    )

    stl.write("model.edit.stl")