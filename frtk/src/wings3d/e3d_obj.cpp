#include <wings3d/wings.h>


struct drag {
    float x;
    float y;
    float xs = 0;
    float ys = 0;
    auto tvs;
    auto constraint;
    shape shapes;
};

struct ost {
    std::vector<glm::vec3> v;					//Vertices.
    std::vector<glm::vec3> 	 vt;					//Texture vertices.
    std::vector<glm::vec3> vn =;					//Vertice normals.
    std::vector<face> f ;					//Faces.
    std::vector<Material>mat = [];				//Current material.
    std::vector<std::string> matdef;				//Material definitions.
    std::string name;					//Object name.
    std::string dir;					//Directory of .obj file.
};