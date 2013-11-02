#pragma once

#include <math.h>
#include <cmath>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

namespace obj {
    class camera {
        public:
            const static unsigned char speed = 1;

            const static unsigned int left  = 0x01;
            const static unsigned int right = 0x02;
            const static unsigned int front = 0x03;
            const static unsigned int back  = 0x04;

            camera(float init_angle = 0);

            void reset_view(int width, int height);
            void change_angle(float angle2);
            void set_direction_y(float y);

            void move(int direction);

        private:
            float angle;
            float * i;
            float * d;

            void set_eye(int x, int y, int z);
            void refresh_look_at();
            void refresh_direction(void);

            int modifier_for_direction(int direction);

            float get_sin(void);
            float get_cos(void);
    };
}
