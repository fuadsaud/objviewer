#include "loader.h"

obj::loader::loader(std::string p) {
    path = p.c_str();
}

void obj::loader::load(obj::mesh * m) {
    std::ifstream in(path.c_str());

    obj::group * g = new obj::group();
    m->push_group(g);

    obj::vertex * v;
    obj::vertex2 * t;
    obj::face * face;
    std::vector<std::string> f;
    std::vector<std::string> tokens;

    while (!in.eof()) {
        std::string line;
        std::getline(in, line);

        if (line.empty()) continue;

        tokens = split(line, ' ', false);

        switch(line[0]) {
            case 'v':
                if (tokens.size() > 3) {
                    switch (line[1]) {
                        case 't':
                            m->push_texture(new obj::vertex2(
                                        atof(tokens.at(1).c_str()),
                                        atof(tokens.at(2).c_str())));
                        case 'n':
                            v = new obj::vertex(
                                    atof(tokens.at(1).c_str()),
                                    atof(tokens.at(2).c_str()),
                                    atof(tokens.at(3).c_str()));

                            m->push_normal(v); break;
                        default:
                            v = new obj::vertex(
                                    atof(tokens.at(1).c_str()),
                                    atof(tokens.at(2).c_str()),
                                    atof(tokens.at(3).c_str()));

                            m->push_vertex(v); break;
                    }
                } else {

                    m->push_texture(t);
                }

                break;
            case 'f':
                face = new obj::face();

                for (int i = 1; i < tokens.size(); i++) {
                    f = split(tokens[i], '/', true);

                    face->push_vertex(atoi(f[0].c_str()) - 1);

                    if (f.size() > 1 && !f[1].empty()) {
                        face->push_texture(atoi(f[1].c_str()) - 1);
                    }

                    if (f.size() > 2) {
                        face->push_normal(atoi(f[2].c_str()) - 1);
                    }
                }

                g->push_face(face);

                break;
            case 'g':
                if (!g->get_faces().empty()) {
                    if (tokens.size() == 1) {
                        g = new obj::group();
                    } else {
                        g = new obj::group(tokens.at(1));
                    }

                    m->push_group(g);
                }

                break;
            case 'm':
                m->set_material_library("fixtures/" + tokens[1]);

                break;
            case 'u':
                std::string material = std::string(tokens[1]);
                g->set_material(material);

                break;
        }
    }
}

