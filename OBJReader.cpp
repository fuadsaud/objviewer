#include "OBJReader.h"

OBJReader::OBJReader(std::string p, Mesh * m) {

}

void OBJReader::load() {

}

std::vector<std::string> OBJReader::split(const std::string &s, char delim) {
  std::vector<std::string> elems;
  split(s, delim, elems);
  return elems;
}

std::vector<std::string>& OBJReader::split(const std::string &s, char delim, std::vector<std::string> &elems) {
  std::stringstream ss(s);
  std::string item;
  while (std::getline(ss, item, delim)) {
    elems.push_back(item);
  }
  return elems;
}
