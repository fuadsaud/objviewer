#include "OBJ.h"

OBJ::OBJ(std::string p) {
  path = "";
}

OBJ::OBJ(char * p) {
  path = p;
}

void OBJ::load(Mesh * m) {
  std::ifstream in(path);

  std::vector<std::string> tokens;

  Group * g = new Group();
  m->push_group(g);

  Vertex * v;

  bool createGroup = false;

  Face * face;
  std::vector<std::string> f;

  while(!in.eof()) {
    std::string line;
    std::getline(in, line);

    tokens = split(line.c_str(), ' ');

    switch(line[0]) {
      case 'v':
        /* if (tokens.size() == 4) { */
        v = new Vertex(
            atof(tokens.at(1).c_str()),
            atof(tokens.at(2).c_str()),
            atof(tokens.at(3).c_str()));

        switch(line[1]) {
          case 't': break; //TODO
          case 'n': m->push_normal(v); break;
          default:  m->push_vertex(v); break;
        }
        /* } */

        break;
      case 'f':
        face = new Face();

        for (int i = 1; i < tokens.size(); i++) {
          f = split(tokens[i], '/');

          face->push_vertex(atoi(f[0].c_str()) - 1);
          /* face->push_vertex(f[1]); */
          face->push_normal(atoi(f[2].c_str()) - 1);
        }

        g->push_face(face);

        break;
      case 'g':
        if (createGroup) {
          if (tokens.size() == 1) {
            g = new Group();
          } else {
            g = new Group(tokens.at(1));
          }

          m->push_group(g);
        } else {
          createGroup = true;
        }

        break;
    }
  }
}

std::vector<std::string> OBJ::split(const std::string &s, char delim) {
  std::vector<std::string> elems;
  split(s, delim, elems);
  return elems;
}

std::vector<std::string>& OBJ::split(const std::string &s, char delim, std::vector<std::string> &elems) {
  std::stringstream ss(s);
  std::string item;

  while (std::getline(ss, item, delim)) {
    elems.push_back(item);
  }

  return elems;
}
