#include <vector>

class Group {
  private:
    std::vector<int> faces;

  public:
    void push_face(int f);

    std::vector<int> get_faces(void);
};
