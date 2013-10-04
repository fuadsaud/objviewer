#include <vector>
#include <map>
#include <OpenGL/GLU.h>

#include "vertex.h"
#include "group.h"
#include "material_library.h"

namespace obj {
    class mesh {
        public:
            std::vector<obj::vertex *> get_verts();
            std::vector<obj::vertex *> get_norms();
            std::vector<obj::group *> get_groups();

            void push_group(obj::group * g);
            void push_vertex(obj::vertex * v);
            void push_normal(obj::vertex * n);
            void set_material_library(std::string lib);

            void render();

        private:
            std::vector<obj::group *> groups;
            std::vector<obj::vertex *> verts;
            std::vector<obj::vertex *> norms;
            obj::material_library * materials;
    };
}
