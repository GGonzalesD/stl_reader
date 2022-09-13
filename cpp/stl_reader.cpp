#include "stl_reader.hpp"

namespace stl{

Vector3 Vector3::read(std::ifstream& file){
    float x, y, z;
    file.read((char*)&x, sizeof(float));
    file.read((char*)&y, sizeof(float));
    file.read((char*)&z, sizeof(float));
    return {x, y, z}; 
}
void Vector3::write(std::ofstream& file){
    file.write((char*)&this->x, sizeof(float));
    file.write((char*)&this->y, sizeof(float));
    file.write((char*)&this->z, sizeof(float));
}


Triangle Triangle::read(std::ifstream& file){
    Vector3 vertex[3];
    u_short attrib;
    Vector3 normal = Vector3::read(file);
    for(size_t i=0; i<3; i++)
        vertex[i] = Vector3::read(file);
    file.read((char*)&attrib, sizeof(u_short));
    return Triangle(normal, vertex, attrib);
}

void Triangle::write(std::ofstream& file){
    normal.write(file);
    for(size_t i=0; i<3; i++)
        vertex[i].write(file);
    file.write((char*)&this->attrib, sizeof(u_short));
}


Model Model::read(const std::string& filename){
    std::ifstream file(filename, std::ios::in | std::ios::binary);
    u_char header[80];
    u_int size;
    file.read((char*)header, sizeof(u_char)*80);
    file.read((char*)&size, sizeof(u_int));

    std::vector<Triangle> triangles(size);
    for(size_t i=0; i<size; i++)
        triangles[i] = Triangle::read(file);
    file.close();

    return Model(header, triangles);
}
void Model::write(const std::string& filename){
    std::ofstream file(filename, std::ios::out | std::ios::binary);
    u_int size = triangles.size();
    if(header.size() > 80){
        file.write((char*)header.c_str(), sizeof(u_char)*80);
    } else {
        file.write((char*)header.c_str(), sizeof(u_char)*header.size());
        for(size_t i=0; i<80-header.size(); i++)
            file.put(0);
    }
    file.write((char*)&size, sizeof(u_int));
    for(Triangle& triangle: triangles)
        triangle.write(file);
    file.close();
}

}

std::ostream& operator << (std::ostream &os, const stl::Vector3 &s){
    return (os << "V3(" << s.getX() << ", " << s.getY() << ", " << s.getZ() << ")");
}

std::ostream& operator << (std::ostream &os, const stl::Triangle &t){
    return (os << "Triangle(" << t.getNormal()
        << ", Vertex(" << t.getVertex()[0]
        << ", " << t.getVertex()[1]
        << ", " << t.getVertex()[2]
        << ")), " << t.getAttrib() << ")");
}

std::ostream& operator << (std::ostream &os, const stl::Model &t){
    return (os << "Model('" << t.getHeader() << "', triangles(" << t.getSize() << "))");
}