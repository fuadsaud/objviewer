#include <vector>
#include <string>
#include "Face.h"

class Group {
  public:
    Group(std::string n = "");

    void push_face(Face * f);
    std::vector<Face *> get_faces(void);

  private:
    std::string name;
    std::vector<Face *> faces;
};
