#include <vector>

namespace obj {
  class face {
    private:
      std::vector<int> verts;
      std::vector<int> norms;

    public:
      void push_vertex(int v);
      void push_normal(int n);

      std::vector<int> get_verts(void);
      std::vector<int> get_norms(void);
  };
}
