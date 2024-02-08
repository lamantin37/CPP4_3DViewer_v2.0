#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "auxiliary_modules.h"

int parser_counter(std::ifstream &file, Object &object) {
  file.clear();
  file.seekg(0, std::ios::beg);
  std::string line;
  while (std::getline(file, line)) {
    if (!line.empty() && line[0] != '#') {
      std::stringstream ss(line);
      std::string token;
      ss >> token;
      if (token == "f")
        object.num_of_polygons++;
      else if (token == "v")
        object.num_of_vertices++;
    }
  }
  return object.num_of_vertices;
}

void object_parser(std::ifstream &file, Object &object) {
  file.clear();
  file.seekg(0, std::ios::beg);

  std::vector<Vertex> vertices;
  std::string line;
  while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string token;
    ss >> token;
    if (token == "v") {
      Vertex vertex;
      if (ss >> vertex.x >> vertex.y >> vertex.z) {
        vertex.vertex_number = vertices.size() + 1;
        vertices.push_back(vertex);
      }
    } else if (token == "f") {
      int v1, v2, v3;
      if (ss >> v1 >> v2 >> v3) {
        Polygon polygon;
        polygon.vertices.push_back(vertices[v1 - 1]);
        polygon.vertices.push_back(vertices[v2 - 1]);
        polygon.vertices.push_back(vertices[v3 - 1]);
        object.polygons.push_back(polygon);
      }
    }
  }
}