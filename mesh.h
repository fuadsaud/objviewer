#include <vector>
#include <map>
#include <OpenGL/GLU.h>

#include "vertex2.h"
#include "group.h"
#include "material_library.h"

namespace obj {
    class mesh {
        public:
            typedef struct face_selection {
                int group_position;
                int face_position;
                obj::face * face;
            } face_selection;

            mesh();

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
            void toggle_render_mode();

            void render();

            void set_selection(int group, int face);
            void delete_selection();

        private:
            void set_render_mode(int rm);
            void render_faces();
            void render_verts();

            std::vector<obj::group *> groups;
            std::vector<obj::vertex *> verts;
            std::vector<obj::vertex *> norms;
            std::vector<obj::vertex2 *> texts;
            obj::material_library * materials;

            int render_mode;

            obj::mesh::face_selection selected_face;
    };
}
