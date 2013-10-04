#include <string>
#include <fstream>
#include <iostream>

#include "utils.h"

namespace obj {
    class material {
    public:
        material(std::string p);

        float get_shininess();
        float * get_ambient();
        float * get_diffuse();
        float * get_specular();
        void set_shininess(float sh);
        void set_ambient(int index, float a);
        void set_diffuse(int index, float d);
        void set_specular(int index, float s);

    private:
        std::string path;
        float shininess;
        float * ambient;
        float * diffuse;
        float * specular;
    };
}
