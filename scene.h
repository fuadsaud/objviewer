#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#include "mesh.h"
#include "camera.h"

namespace obj {
    class scene {
        public:
            scene(bool hud = true, bool fps = true, bool axis = true);

            void push_mesh(obj::mesh * mesh);

            void initialize();
            void render();
            void idle();

            void set_hud_visibility(bool v);
            void set_fps_visibility(bool v);
            void set_axis_visibility(bool v);

            void toggle_hud();
            void toggle_fps();
            void toggle_axis();

            /* void move_camera_left(); */
            /* void move_camera_right(); */
            /* void move_camera_front(); */
            /* void move_camera_back(); */
            void look(float x, float y);

        private:
            void render_hud();
            void render_fps();
            void render_axis(float size = 9);
            void render_string(
                    char * string,
                    float x,
                    float y,
                    float r,
                    float g,
                    float b);

            void go2d();

            void refresh_fps();
            float fps();

            int width();
            int height();

            obj::mesh * mesh;
            /* obj::camera camera; */

            int current_time;
            int timebase;
            int frames;

            bool will_render_hud;
            bool will_render_fps;
            bool will_render_axis;
    };
}
