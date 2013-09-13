#include <vector>
#include "Vertex.h"
#include "Group.h"

class Mesh {
  private:
    std::vector<Group *> groups;
    std::vector<Vertex *> verts;
    std::vector<Vertex *> norms;

  public:
    std::vector<Vertex *> get_verts();
    std::vector<Vertex *> get_norms();
    std::vector<Group *> get_groups();

    void push_group(Group * g);
    void push_vertex(Vertex * v);
    void push_normal(Vertex * v);
};
