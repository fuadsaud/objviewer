#include <map>
#include <string>
#include <utility>
#include <OpenGL/GL.h>

#include "material.h"
#include "Image.h"

namespace obj {
  class material_library {
      public:
          material_library(std::string p);

          obj::material * operator[](std::string material_name);
          obj::material * at(std::string material_name);

          void load_textures();

      private:
          std::string path;
          std::map<std::string, obj::material *> materials;
          void load();

          int texture_count;
  };
}
