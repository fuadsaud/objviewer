#include <vector>
#include <string>

#include "face.h"

namespace obj {
  class group {
  public:
      group(std::string n = "");

      void push_face(obj::face * f);
      obj::face * get_face_at(int i);
      void erase_face_at(int i);
      void set_material(std::string m);
      void hide();
      bool is_visible();

      std::string get_material();
      std::vector<obj::face *> get_faces(void);

  private:
      std::string material;
      std::string name;
      std::vector<obj::face *> faces;
      bool visible;
  };
}
