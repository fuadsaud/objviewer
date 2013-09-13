#include <vector>
#include <string>

class Group {
  public:
    Group(std::string n = "");

    void push_face(int f);
    std::vector<int> get_faces(void);

  private:
    std::string name;
    std::vector<int> faces;
};
