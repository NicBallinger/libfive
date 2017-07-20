#pragma once

#include <vector>
#include <Eigen/Eigen>

#include "ao/render/octree.hpp"
#include "ao/tree/tree.hpp"

namespace Kernel {

class Region;

struct Mesh
{
    /*
     *  Run dual contouring on the given evaluator, returning a Mesh
     *
     *  This involves sampling the evaluator on an octree (with QEF
     *  simplification to collapse leaf cells), then using DC to generate
     *  a triangle mesh.
     */
    static std::unique_ptr<Mesh> render(const Tree t, const Region& r);

    /*
     *  Saves the given mesh
     *
     *  filename must end in ".stl" or ".obj"
     *  Returns true on success, false if the extension isn't recognized
     */
    bool save(std::string filename);
    void writeSTL(std::ostream& out);
    void writeOBJ(std::ostream& out);

    /*
     *  Returns the unit-length normal of the i'th triangle
     */
    Eigen::Vector3f norm(unsigned i) const;

    /*  Vertices in 3D space  */
    std::vector<Eigen::Vector3f> verts;

    /*  Triangles in the mesh (as indices in verts list)  */
    std::vector<Eigen::Vector3i> tris;
};

}   // namespace Kernel