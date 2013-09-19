#include <math.h>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#define PI 3.141592653589

#define SPEED 3

namespace obj {
    class camera {
        private:
            float angle;
            void refresh_direction(void);

        public:
            float * i;
            float * d;

            camera();
            camera(float init_angle);

            float get_sin(void);
            float get_cos(void);

            void change_angle(float angle2);
            void set_direction_y(float y);
            void set_eye(int x, int y, int z);
            void move(int direction);
            void move_side(int direction);

            void refresh_look_at();
            void reset_view(int width, int height);
    };
}
