#version 410

uniform sampler2D tex;
in vec2 texPos_vs;
layout(location = 0) out vec4 fragColor;

void main()
{
    fragColor = texture(tex, texPos_vs);
}