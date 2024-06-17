#version 430 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoord;


out vec3 ourColor;
out vec2 TexCoord;
uniform mat4 model;
uniform mat4 camMatrix;
void main()
{
    vec4 world_space = model * vec4(aPos, 1.0);
    gl_Position = camMatrix * world_space;
    ourColor = aColor;
    TexCoord = aTexCoord;
}
