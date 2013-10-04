#include "material.h"

obj::material::material(std::string p) {
    path = p;
    ambient = new float[4];
    diffuse = new float[4];
    specular = new float[4];

    ambient[3] = 1;
    diffuse[3] = 1;
    specular[3] = 1;
}

float obj::material::get_shininess() {
    return shininess;
}
float * obj::material::get_ambient() {
    return ambient;
}

float * obj::material::get_diffuse() {
    return diffuse;
}

float * obj::material::get_specular() {
    return specular;
}

void obj::material::set_shininess(float sh) {
    shininess = sh;
}

void obj::material::set_ambient(int index, float a) {
    ambient[index] = a;
}

void obj::material::set_diffuse(int index, float d) {
    diffuse[index] = d;
}

void obj::material::set_specular(int index, float s) {
    specular[index] = s;
}

