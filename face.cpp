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

obj::vertex * obj::face::centroid(std::vector<obj::vertex *> v) {
    unsigned int verts_size = verts.size();

    float centroid[3]  = { 0, 0, 0 };

    for (int i : verts) {
        float * coords = v[i]->get_coords();

        centroid[0] += coords[0] / verts_size;
        centroid[1] += coords[1] / verts_size;
        centroid[2] += coords[2] / verts_size;
    }

    return new vertex(centroid);
}
