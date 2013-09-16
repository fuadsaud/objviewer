#include <vector>
#include <string>
#include <fstream>

#include "utils.h"
#include "mesh.h"

namespace obj {
  class loader {
      public:
          loader(std::string p);

          void load(obj::mesh * m);

      private:
        std::string path;
  };
}
