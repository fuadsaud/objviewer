#include <vector>
#include <map>
#include <OpenGL/GLU.h>
#include "Vertex.h"
#include "Group.h"
#include "MaterialLibrary.h"

class Mesh {
    public:
        std::vector<Vertex *> get_verts();
        std::vector<Vertex *> get_norms();
        std::vector<Group *> get_groups();

        void push_group(Group * g);
        void push_vertex(Vertex * v);
        void push_normal(Vertex * n);
        void set_material_library(std::string lib);

        void render();

    private:
        std::vector<Group *> groups;
        std::vector<Vertex *> verts;
        std::vector<Vertex *> norms;
        MaterialLibrary * materials;
};
