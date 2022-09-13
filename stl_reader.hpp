#pragma once

#include <fstream>
#include <vector>
#include <cstring>

namespace stl{

class Vector3{
private:
    float x, y, z;

public:
    Vector3(float x_, float y_, float z_){
        x = x_; y = y_; z = z_;
    }
    Vector3(){x=0; y=0; z=0;}
    ~Vector3(){}

    static Vector3 read(std::ifstream& file);
    void write(std::ofstream& file);

    float getX() const { return x; }
    float getY() const { return y; }
    float getZ() const { return z; }

    void setX(float x_){ x = x_; }
    void setY(float y_){ y = y_; }
    void setZ(float z_){ z = z_; }
};

class Triangle{
private:
    Vector3 normal;
    Vector3 vertex[3];
    u_short attrib;

public:
    Triangle(const Vector3& normal_, const Vector3 vertex_[3], u_short attrib_){
        normal = normal_;
        for(size_t i=0; i<3; i++)
            vertex[i] = vertex_[i];
        attrib = attrib_;
    }
    Triangle(){attrib = 0;}
    ~Triangle(){}

    static Triangle read(std::ifstream& file);
    void write(std::ofstream& file);

    Vector3 getNormal() const { return normal; }
    Vector3* getVertex() const { return (Vector3*)vertex; }
    u_short getAttrib() const { return attrib; }
    void setNormal(const Vector3& normal_){ normal = normal_; }
    void setVertex(const Vector3& vertex_, size_t index){ vertex[index] = vertex_; }
    void setAttrib(u_short attrib_){ attrib = attrib_; }
};

class Model{
private:
    std::string header;
    std::vector<Triangle> triangles;

public:
    Model(const u_char header_[80], const std::vector<Triangle>& triangles_){
        header = (char*)header_;
        triangles = triangles_;
    }
    Model(){
        header[0] = 0;
        triangles = {};
    }

    static Model read(const std::string& filename);
    void write(const std::string& filename);

    std::string getHeader() const { return header; }
    std::vector<Triangle>& getTriangles() { return triangles; }
    u_int getSize() const { return triangles.size(); }

    void setHeader(const u_char header_[80]){
        header = (char*)header_;
    }
    void setTriangles(const std::vector<Triangle>& triangles_){
        triangles = triangles_;
    }
};

}

std::ostream& operator << (std::ostream &os, const stl::Vector3 &s);
std::ostream& operator << (std::ostream &os, const stl::Triangle &t);
std::ostream& operator << (std::ostream &os, const stl::Model &t);