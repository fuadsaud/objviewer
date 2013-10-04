#include <map>
#include <string>

#include "material.h"

namespace obj {
  class material_library {
      public:
          material_library(std::string p);

          obj::material * operator[](std::string material_name);
          obj::material * at(std::string material_name);

      private:
          std::string path;
          std::map<std::string, obj::material *> materials;
          void load();
  };
}
