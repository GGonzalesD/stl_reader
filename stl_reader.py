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
class Triangles:
    normal: Vec3
    vertex: list[Vec3]
    attrib: int

    @classmethod
    def read(cls, file: BufferedReader):
        normal = Vec3.read(file)
        vertex = [ Vec3.read(file) for _ in range(3) ]
        attrib = int.from_bytes(file.read(2), "little", signed=False)
        return Triangles(normal, vertex, attrib)
    
    def write(self, file: BufferedWriter):
        self.normal.write(file)
        for vertex in self.vertex:
            vertex.write(file)
        file.write(self.attrib.to_bytes(2, 'little', signed=False))

@dataclass
class Stl:
    header: str
    triangles: list[Triangles]

    @classmethod
    def read(cls, filename: str):

        with open(filename, "rb") as f:
            string = f.read(80).decode()
            numbers = int.from_bytes(f.read(4), 'little', signed=False)

            triangles = [ Triangles.read(f) for _ in range(numbers) ]

        return Stl(string, triangles)
    
    def write(self, filename):

        with open(filename, "wb") as f:
            header_bytes = self.header[:80].encode()
            header_bytes = header_bytes + b'\x00' * (80 - len(header_bytes))
            f.write(header_bytes)
            numbers_bytes = len(self.triangles).to_bytes(4, 'little', signed=False)
            f.write(numbers_bytes)
            for triangle in self.triangles:
                triangle.write(f)
    
    def __repr__(self):
        return f"Stl('{self.header}', Triangles({len(self.triangles)}))"

            