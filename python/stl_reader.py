#!/usr/bin/python3
from dataclasses import dataclass
from io import BufferedReader, BufferedWriter
import struct

@dataclass
class Vec3:
    x: float
    y: float
    z: float

    @classmethod
    def read(cls, file: BufferedReader):
        return Vec3(*struct.unpack("fff", file.read(12)))
    
    def write(self, file: BufferedWriter):
        file.write(struct.pack("fff", self.x, self.y, self.z))

@dataclass
class Triangle:
    normal: Vec3
    vertex: list[Vec3]
    attrib: int

    @classmethod
    def read(cls, file: BufferedReader):
        normal = Vec3.read(file)
        vertex = [ Vec3.read(file) for _ in range(3) ]
        (attrib,) = struct.unpack('H', file.read(2))
        return Triangle(normal, vertex, attrib)
    
    def write(self, file: BufferedWriter):
        self.normal.write(file)
        for vertex in self.vertex:
            vertex.write(file)
        file.write(struct.pack('H', self.attrib))

@dataclass
class Stl:
    header: str
    triangles: list[Triangle]

    @classmethod
    def read(cls, filename: str):

        with open(filename, "rb") as f:
            string = f.read(80).decode()
            (numbers,) = struct.unpack('I', f.read(4))
            triangles = [ Triangle.read(f) for _ in range(numbers) ]

        return Stl(string, triangles)
    
    def write(self, filename):

        with open(filename, "wb") as f:
            header_bytes = self.header[:80].encode()
            header_bytes = header_bytes + b'\x00' * (80 - len(header_bytes))
            f.write(header_bytes)
            f.write(struct.pack('I', len(self.triangles)))
            for triangle in self.triangles:
                triangle.write(f)
    
    def __repr__(self):
        return f"Stl('{self.header}', Triangles({len(self.triangles)}))"

            