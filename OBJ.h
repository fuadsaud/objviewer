#include <vector>
#include <string>
#include <fstream>

#include "Utils.h"
#include "Mesh.h"

class OBJ {
    public:
        OBJ(std::string p);
        OBJ(const char * p);

        void load(Mesh * m);

    private:
        const char * path;
};
