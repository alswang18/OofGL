#version 430 core
out vec4 FragColor;
in vec3 ourColor;
in vec2 TexCoord;
uniform sampler2D tex0;
void main()
{
    FragColor = texture(tex0, TexCoord) * vec4(ourColor, 0.4);
}