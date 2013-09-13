#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <boost/algorithm/string/split.hpp>

#include "Mesh.h"

class OBJ {
public:
  OBJ(std::string p);
  OBJ(char * p);

  void load(Mesh * m);

private:
  char * path;
  std::vector<std::string> split(const std::string &s, char delim);
  std::vector<std::string>& split(const std::string &s, char delim,
                                 std::vector<std::string> &elems);
};
