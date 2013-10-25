#include <vector>

#include "vertex.h"

namespace obj {
  class face {
    private:
      std::vector<int> verts;
      std::vector<int> norms;
      std::vector<int> texts;

    public:
      void push_vertex(int v);
      void push_normal(int n);
      void push_texture(int t);
      void average_vertex(std::vector<obj::vertex *> v);

      std::vector<int> get_verts(void);
      std::vector<int> get_norms(void);
      std::vector<int> get_texts(void);
  };
}
