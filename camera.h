#include <math.h>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#define PI 3.141592653589

#define SPEED 3

namespace obj {
    class camera {
        public:
            const static int LEFT  = 0x01;
            const static int RIGHT = 0x02;
            const static int FRONT = 0x03;
            const static int BACK  = 0x04;

            float * i;
            float * d;

            camera(float init_angle = 0);

            void reset_view(int width, int height);
            void change_angle(float angle2);
            void set_direction_y(float y);

            void move(int direction);

        private:
            float angle;
            void refresh_direction(void);
            int modifier_for_direction(int direction);

            float get_sin(void);
            float get_cos(void);

            void set_eye(int x, int y, int z);

            void refresh_look_at();
    };
}
