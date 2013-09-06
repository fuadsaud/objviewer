#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#include "Mesh.h"

class OBJReader {
public:
  OBJReader(std::string p, Mesh * m);

  void load();

private:
  std::vector<std::string> split(const std::string &s, char delim);
  std::vector<std::string>& split(const std::string &s, char delim,
                                 std::vector<std::string> &elems);
};
