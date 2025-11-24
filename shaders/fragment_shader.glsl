#version 330 core
out vec4 FragColor;
in vec4 Color;

uniform vec4 u_Color;
uniform int u_UseUniformColor;

void main()
{
   if (u_UseUniformColor == 1) {
       FragColor = u_Color;
   } else {
       FragColor = Color;
   }
}
