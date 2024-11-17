#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 vertexColor;

uniform mat4 TransformationMatrix;

out vec4 theColor;

void main()
{
	vec4 v = TransformationMatrix * position;
	gl_Position = v;
	theColor = vertexColor;
}

#shader fragment
#version 330 core

out vec4 color;
in vec4 theColor;

//uniform vec4 u_Color;

void main()
{
   color = theColor;
}
