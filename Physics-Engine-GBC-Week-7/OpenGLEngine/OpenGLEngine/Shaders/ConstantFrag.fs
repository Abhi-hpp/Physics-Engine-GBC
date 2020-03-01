#version 330 core
out vec4 FragColor;
uniform vec3 col;
void main()
{
    FragColor = vec4(col, 1.0); // set all 4 vector values to 1.0
}