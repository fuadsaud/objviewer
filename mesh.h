#pragma once

#include <vector>
#include <map>
#include <set>
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

            typedef struct vertex_selection {
                int vertex_position;
                obj::vertex * vertex;
            } vertex_selection;

            const static unsigned int face_mode = 0x01;
            const static unsigned int vertex_mode = 0x02;

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
            void enter_faces_render_mode();
            void enter_verts_render_mode();

            void render(bool select_mode);

            void set_selection(int group, int face);
            void erase_selection();
            void complexify_selection();
            void move_selection(int direction);

        private:
            void set_render_mode(int rm);
            void set_gl_render_mode(int gl_rm);

            void render_named_verts();
            void render_unnamed_verts();

            void complexify(obj::mesh::face_selection fs);
            void move(int direction, obj::mesh::vertex_selection vs);

            void erase_face(obj::mesh::face_selection fs);
            void erase_vertex(obj::mesh::vertex_selection vs);
            void clear_selection();
            bool has_selection();

            std::vector<obj::group *> groups;
            std::vector<obj::vertex *> verts;
            std::vector<obj::vertex *> norms;
            std::vector<obj::vertex2 *> texts;
            obj::material_library * materials;

            int render_mode;
            int gl_render_mode;

            obj::mesh::face_selection selected_face;
            obj::mesh::vertex_selection selected_vertex;
    };
}
