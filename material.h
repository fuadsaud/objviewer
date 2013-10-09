#include <string>
#include <fstream>
#include <iostream>

#include "utils.h"

namespace obj {
    class material {
    public:
        material(std::string p);

        std::string get_texture_name();
        int get_texture_id();
        float get_shininess();
        float * get_ambient();
        float * get_diffuse();
        float * get_specular();
        void set_texture_id(int t);
        void set_texture_name(std::string name);
        void set_shininess(float sh);
        void set_ambient(int index, float a);
        void set_diffuse(int index, float d);
        void set_specular(int index, float s);
        bool has_texture();

    private:
        std::string path;
        std::string texture_name;
        int texture_id;
        float shininess;
        float * ambient;
        float * diffuse;
        float * specular;
    };
}
