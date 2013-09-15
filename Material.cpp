#include "Material.h"

Material::Material(std::string p) {
    path = p;
}

float Material::get_shininess() {
    return shininess;
}

float * Material::get_ambient() {
    return ambient;
}

float * Material::get_diffuse() {
    return diffuse;
}

float * Material::get_specular() {
    return specular;
}

void Material::set_shininess(float sh) {
    shininess = sh;
}

void Material::set_ambient(float * a) {
    ambient = a;
}

void Material::set_diffuse(float * d) {
    diffuse = d;
}

void Material::set_specular(float * s) {
    specular = s;
}

