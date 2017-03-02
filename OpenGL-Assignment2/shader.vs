#version 330 core


layout (location = 0) in vec3 position;
out vec3 ourColor;



void main()
{
	//gl_Position = projection * view * model * vec4(position, 1.0f);
	gl_Position = vec4(position, 1.0f);
	ourColor = vec3(.4-position.z, 0.5-position.z, 1.5-position.z);
}
