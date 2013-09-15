#include <vector>
#include <string>
#include "Face.h"

class Group {
public:
    Group(std::string n = "");

    void push_face(Face * f);
    void set_material(std::string m);

    std::string get_material();
    std::vector<Face *> get_faces(void);

private:
    std::string material;
    std::string name;
    std::vector<Face *> faces;
};
