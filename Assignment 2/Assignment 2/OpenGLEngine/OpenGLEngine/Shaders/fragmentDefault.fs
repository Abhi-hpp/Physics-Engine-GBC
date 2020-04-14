#version 420 core
out vec4 FragColor;

in vec2 TexCoords;


uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;


void main()
{    
    FragColor = texture(texture_diffuse1, TexCoords);
	//FragColor = vec4(1,0,0,1);

}