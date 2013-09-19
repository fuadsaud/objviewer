#include "material_library.h"

obj::material_library::material_library(std::string p) {
    path = p;

    load();
}

obj::material * obj::material_library::operator[](std::string * material_name) {
    return at(material_name);
}

obj::material * obj::material_library::at(std::string * material_name) {
    return materials[material_name];
}

void obj::material_library::load() {
    std::ifstream in(path.c_str());

    obj::material * m;
    std::vector<std::string> tokens;

    while (!in.eof()) {
        std::string line;
        std::getline(in, line);

        tokens = split(line.c_str(), ' ');

        switch (line[0]) {
            case 'n':
                m = new obj::material(tokens[1]);
                materials[&tokens[1]] = m;

                break;
            case 'i':
                m->set_shininess(atof(tokens[1].c_str()));

                break;
            case 'K':
                switch (line[1]) {
                    case 'a':
                        float a[3];

                        for (int i = 1; i < 3; i++) {
                            a[i - 1] = atof(tokens[i].c_str());
                        }

                        m->set_ambient(a);

                        break;
                    case 'd':
                        float d[3];

                        for (int i = 1; i < 3; i++) {
                            d[i - 1] = atof(tokens[i].c_str());
                        }

                        m->set_diffuse(d);

                        break;
                }

                 break;
            case 'T':
                 float s[3];

                 for (int i = 1; i < 3; i++) {
                     s[i - 1] = atof(tokens[i].c_str());
                 }

                 m->set_specular(s);

                 break;
            case 'N': break;
        }
    }
}
