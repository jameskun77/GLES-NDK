#version 300 es
precision mediump float;

in vec3 ourColor;
in vec2 texCoord;

out vec4 FragColor;

uniform sampler2D texture1;

void main()
{
  FragColor = texture(texture1,texCoord);
}