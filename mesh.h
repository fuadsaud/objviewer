#include <vector>
#include <map>
#include <OpenGL/GLU.h>

#include "vertex.h"
#include "vertex2.h"
#include "group.h"
#include "material_library.h"

namespace obj {
    class mesh {
        public:
            std::vector<obj::vertex *> get_verts();
            std::vector<obj::vertex *> get_norms();
            std::vector<obj::vertex2 *> get_texts();
            std::vector<obj::group *> get_groups();

            obj::group* group_at(int i);
            void push_group(obj::group * g);
            void push_vertex(obj::vertex * v);
            void push_normal(obj::vertex * n);
            void push_texture(obj::vertex2 * t);
            void set_material_library(std::string lib);

            void render();

        private:
            std::vector<obj::group *> groups;
            std::vector<obj::vertex *> verts;
            std::vector<obj::vertex *> norms;
            std::vector<obj::vertex2 *> texts;
            obj::material_library * materials;
    };
}
