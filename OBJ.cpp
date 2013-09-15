#include "OBJ.h"

OBJ::OBJ(std::string p) {
    path = p.c_str();
}

OBJ::OBJ(const char * p) {
    path = p;
}

void OBJ::load(Mesh * m) {
    std::ifstream in(path);

    Group * g = new Group();
    m->push_group(g);

    Vertex * v;
    Face * face;
    std::vector<std::string> f;
    std::vector<std::string> tokens;
    bool use_default_group = true;

    while(!in.eof()) {
        std::string line;
        std::getline(in, line);

        if (line.empty()) { continue; }

        tokens = split(line.c_str(), ' ');

        switch(line[0]) {
            case 'v':
                if (tokens.size() == 4) {
                    v = new Vertex(
                            atof(tokens.at(1).c_str()),
                            atof(tokens.at(2).c_str()),
                            atof(tokens.at(3).c_str()));

                    switch(line[1]) {
                        case 't': break; //TODO
                        case 'n': m->push_normal(v); break;
                        default:  m->push_vertex(v); break;
                    }
                }

                break;
            case 'f':
                face = new Face();

                for (int i = 1; i < tokens.size(); i++) {
                    f = split(tokens[i], '/');

                    face->push_vertex(atoi(f[0].c_str()) - 1);

                    if (f.size() > 1) {
                        /* face->push_vertex(f[1]); */
                        face->push_normal(atoi(f[2].c_str()) - 1);
                    }
                }

                g->push_face(face);

                break;
            case 'g':
                if(use_default_group) {
                    use_default_group = false;
                } else {
                    if (tokens.size() == 1) {
                        g = new Group();
                    } else {
                        g = new Group(tokens.at(1));
                    }

                    m->push_group(g);
                }

                break;
            case 'm':
                m->set_material_library("fixtures/" + tokens[1]);

                break;
            case 'u':
                std::string material(tokens[1]);
                g->set_material(material);

                break;
        }
    }
}

