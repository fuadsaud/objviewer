#include "material.h"

obj::material::material(std::string p) {
    path = p;
}

float obj::material::get_shininess() {
    std::cout << "bol" << std::endl;
    std::cout << ambient << std::endl;
    std::cout << "lula" << std::endl;
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

void obj::material::set_ambient(float * a) {
    ambient = a;
}

void obj::material::set_diffuse(float * d) {
    diffuse = d;
}

void obj::material::set_specular(float * s) {
    specular = s;
}

