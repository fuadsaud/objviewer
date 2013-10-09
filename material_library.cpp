#include "material_library.h"

obj::material_library::material_library(std::string p) {
    // FIXME: a wild \r appears at the end of the string
    if ((int) p[17] == 13) {
        p = std::string(p.begin(), p.end() - 1);
    }

    path = p;

    load();
}

obj::material * obj::material_library::operator[](std::string material_name) {
    return at(material_name);
}

obj::material * obj::material_library::at(std::string material_name) {
    return materials[material_name];
}

void obj::material_library::load_textures() {
    unsigned int * texture_ids = new unsigned int[texture_count];

    int i = 0;
    for (std::map<std::string, obj::material *>::iterator iterator = materials.begin(); iterator != materials.end(); iterator++) {
        /* for (std::pair<std::string, obj::material *> p : materials) { */
        /* obj::material * material = std::get<1>(p); */
        obj::material * material = iterator->second;

        if (material->has_texture()) {
            Image * img = new Image();
            img->loadPPM((std::string("fixtures/") + material->get_texture_name()).c_str());

            material->set_texture_id(texture_ids[i++]);

            glBindTexture(GL_TEXTURE_2D, material->get_texture_id());
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexImage2D(
                    GL_TEXTURE_2D,
                    0,
                    GL_RGB,
                    img->getWidth(),
                    img->getHeight(),
                    0,
                    GL_RGB,
                    GL_UNSIGNED_BYTE,
                    img->getPixels());

            free(img->getPixels());
        }
    }
}

void obj::material_library::load() {
    std::ifstream in(path.c_str());

    if (!in.is_open()) {
        std::cout << "nope, no file" << std::endl;
        return;
    }

    obj::material * m;
    std::vector<std::string> tokens;

    while (!in.eof()) {
        std::string line;
        std::getline(in, line);

        tokens = split(line.c_str(), ' ', false);

        switch (line[0]) {
            case 'n':
                m = new obj::material(tokens[1]);
                materials[tokens[1]] = m;

                break;
            case 'i': break;
            case 'K':
                      switch (line[1]) {
                          case 'a':
                              for (int i = 1; i <= 3; i++) {
                                  m->set_ambient(i - 1, atof(tokens[i].c_str()));
                              }

                              break;
                          case 'd':
                              for (int i = 1; i <= 3; i++) {
                                  m->set_diffuse(i - 1, atof(tokens[i].c_str()));
                              }

                              break;
                          case 's':
                              for (int i = 1; i <= 3; i++) {
                                  m->set_specular(i - 1, atof(tokens[i].c_str()));
                              }

                              break;
                      }

                      break;
            case 'T':
                      float s[3];

                      for (int i = 1; i <= 3; i++) {
                          m->set_specular(i - 1, atof(tokens[i].c_str()));
                      }

                      break;
            case 'N':
                      switch(line[1]) {
                          case 's':
                              m->set_shininess(atof(tokens[1].c_str()));
                              break;
                      }

                      break;
            case 'm':
                      texture_count++;
                      m->set_texture_name(tokens[1]);

                      break;
        }
    }

    load_textures();
}
