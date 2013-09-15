#include <map>
#include <string>
#include "Material.h"

class MaterialLibrary {
    public:
        MaterialLibrary(std::string p);

        Material * operator[](std::string material_name);

    private:
        std::string path;
        std::map<std::string, Material *> materials;
        void load();
};
