#include "Face.h"

void obj::face::push_vertex(int v) {
    verts.push_back(v);
}

void obj::face::push_normal(int n) {
    norms.push_back(n);
}

void obj::face::push_texture(int t) {
    /* printf("sdjsdka\n"); */
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
