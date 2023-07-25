#version 330 core 

out vec4 FragColor; //pixel color

uniform vec3 lightColor;

void main()
{//					  r		g	   b	a
	//FragColor = vec4(1.0f, 0.4f, 0.8f, 1.0f);

	FragColor = vec4(lightColor, 1.0);
}