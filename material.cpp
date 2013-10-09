#include "material.h"

obj::material::material(std::string p) {
    path = p;
    texture_name = "";
    ambient = new float[4];
    diffuse = new float[4];
    specular = new float[4];

    ambient[3] = 1;
    diffuse[3] = 1;
    specular[3] = 1;
}

std::string obj::material::get_texture_name() {
    return texture_name;
}

int obj::material::get_texture_id() {
    return texture_id;
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

void obj::material::set_texture_name(std::string tn) {
    texture_name = tn;
}

void obj::material::set_texture_id(int ti) {
    texture_id = ti;
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

bool obj::material::has_texture() {
    return !texture_name.empty();
}
