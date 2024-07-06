// #include "Mesh.h"
// #include "VertexBufferObject.h"

// Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures)
// {
//     this->vertices = vertices;
//     this->indices = indices;
//     this->textures = textures;

//     VAO.Bind();

//     VertexBufferObject VBO(vertices);

//     ElementBufferObject EBO(indices);

//     VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
//     VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
//     VAO.LinkAttrib(VBO, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
//     VAO.LinkAttrib(VBO, 3, 3, GL_FLOAT, sizeof(Vertex), (void*)(8 * sizeof(float)));

//     VAO.Unbind();
//     VBO.Unbind();
//     EBO.Unbind();
// }

// void Mesh::Draw(ShaderProgram& shader, Camera& camera)
// {
//     shader.use();
//     VAO.Bind();

//     unsigned int numDiffuse = 0;
//     unsigned int numSpecular = 0;

//     for (unsigned int i = 0; i < textures.size(); i++) {
//         std::string num;
//         std::string type = textures[i].type;
//         if (type == "diffuse") {
//             num = std::to_string(numDiffuse);
//             numDiffuse++;
//         } else if (type == "specular") {
//             num = std::to_string(numSpecular);
//             numSpecular++;
//         }
//         textures[i].texUnit(shader, (type + num).c_str(), i);
//         textures[i].Bind();
//     }
// }