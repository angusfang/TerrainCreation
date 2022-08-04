#version 410

in vec2 texPos_tes;
in float depth_tes;
uniform sampler2D tex;
layout(location = 0) out vec4 fragColor;

void main()
{
    //fragColor = texture(tex, texPos_tes);
    fragColor = vec4(vec3(depth_tes), 1.0f);
    //fragColor = vec4(vec3(0.9f), 1.0f);
}