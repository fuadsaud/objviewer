#include "face.h"
#include <iostream>

void obj::face::push_vertex(int v) {
    verts.push_back(v);
}

void obj::face::push_normal(int n) {
    norms.push_back(n);
}

void obj::face::push_texture(int t) {
    texts.push_back(t);
}

std::vector<int> obj::face::get_verts(void) {
    return verts;
}

std::vector<int> obj::face::get_norms(void) {
    return norms;
}

std::vector<int> obj::face::get_texts(void) {
    return texts;
}

void obj::face::average_vertex(std::vector<obj::vertex *> v) {
    unsigned int verts_size = verts.size();
    float ptr[3]  = { 0, 0, 0 };

    for (int i : verts) {
        float * coords = v[i]->get_coords();

        ptr[0] += coords[0] / verts_size;
        ptr[1] += coords[1] / verts_size;
        ptr[2] += coords[2] / verts_size;
    }

    std::cout << ptr[0] << std::endl;
    std::cout << ptr[1] << std::endl;
    std::cout << ptr[2] << std::endl;
}
