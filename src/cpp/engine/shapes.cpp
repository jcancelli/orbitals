#include "shapes.hpp"

#include "../math/coordinates.hpp"

namespace orbitals {

namespace engine {

std::shared_ptr<Mesh> sphere(std::shared_ptr<Material> material, unsigned instancesCount,
                             unsigned meridians, unsigned parallels) {
  std::vector<Vertex> vertices;
  std::vector<GLuint> indices;

  double r = 0.5;
  double phiStep = (M_PI * 2) / meridians;
  double thetaStep = M_PI / (parallels + 1);

  // set vertices
  vertices.push_back(Vertex(math::cartesian(r, 0, 0)));
  for (double theta = thetaStep; theta <= M_PI - thetaStep; theta += thetaStep) {
    for (double phi = 0; phi <= M_PI * 2 - phiStep; phi += phiStep) {
      vertices.push_back(Vertex(math::cartesian(r, theta, phi)));
    }
  }
  vertices.push_back(Vertex(math::cartesian(r, M_PI, 0)));

  // set indices
  for (int i = 1; i < meridians; i++) {
    indices.push_back(0);
    indices.push_back(i);
    indices.push_back(i + 1);
  }
  indices.push_back(0);
  indices.push_back(meridians);
  indices.push_back(1);

  for (int parallel = 0; parallel < parallels - 1; parallel++) {
    for (int meridian = 0; meridian < meridians - 1; meridian++) {
      indices.push_back(1 + parallel * meridians + meridian);
      indices.push_back(1 + parallel * meridians + meridian + meridians);
      indices.push_back(1 + parallel * meridians + meridian + 1);

      indices.push_back(1 + parallel * meridians + meridian + meridians);
      indices.push_back(1 + parallel * meridians + meridian + meridians + 1);
      indices.push_back(1 + parallel * meridians + meridian + 1);
    }
    indices.push_back(1 + parallel * meridians + meridians - 1);
    indices.push_back(1 + parallel * meridians + meridians - 1 + meridians);
    indices.push_back(1 + parallel * meridians);

    indices.push_back(1 + parallel * meridians + meridians - 1 + meridians);
    indices.push_back(1 + parallel * meridians + meridians);
    indices.push_back(1 + parallel * meridians);
  }

  const int lastIndex = vertices.size() - 1;
  for (int i = lastIndex - meridians; i < lastIndex - 1; i++) {
    indices.push_back(lastIndex);
    indices.push_back(i + 1);
    indices.push_back(i);
  }
  indices.push_back(lastIndex);
  indices.push_back(lastIndex - meridians);
  indices.push_back(lastIndex - 1);

  return std::shared_ptr<Mesh>(new Mesh(vertices, indices, material, instancesCount));
}

std::shared_ptr<Mesh> cube(std::shared_ptr<Material> material, unsigned instancesCount) {
  // FIXME: Fix cube normals, 24 vertices needed
  std::vector<Vertex> vertices{
      Vertex(-0.5, -0.5, -0.5), Vertex(-0.5, 0.5, -0.5),  // left front 	0 1
      Vertex(0.5, -0.5, -0.5),  Vertex(0.5, 0.5, -0.5),   // right front  2 3
      Vertex(-0.5, -0.5, 0.5),  Vertex(-0.5, 0.5, 0.5),   // left back	4 5
      Vertex(0.5, -0.5, 0.5),   Vertex(0.5, 0.5, 0.5),    // right back	6 7
  };                                                      //
  std::vector<GLuint> indices{
      0, 2, 3, 0, 3, 1,                                   //
      2, 6, 3, 6, 3, 7,                                   //
      0, 4, 1, 4, 1, 5,                                   //
      6, 4, 7, 4, 7, 5,                                   //
      1, 3, 5, 3, 5, 7,                                   //
      0, 2, 4, 2, 4, 6                                    //
  };                                                      //
  return std::shared_ptr<Mesh>(new Mesh(vertices, indices, material, instancesCount));
}

}  // namespace engine

}  // namespace orbitals
