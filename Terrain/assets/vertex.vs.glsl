#version 410
/*
layout(location=0)in vec3 ver;
layout(location=1)in vec2 texCoord;
*/
out vec2 texPos_vs;
out vec3 pos_vs;

vec3 ver[] = vec3[](
	vec3(-1.f, -1.f, 0.f),
	vec3(-1.f, 1.f, 0.f),
	vec3(1.f, -1.f, 0.f),

	vec3(-1.f, 1.f, 0.f),
	vec3(1.f, -1.f, 0.f),
	vec3(1.f, 1.f, 0.f)
);
vec2 texCoord[] = vec2[](
	vec2(0.f, 0.f),
	vec2(0.f, 1.f),
	vec2(1.f, 0.f),
	vec2(0.f, 1.f),
	vec2(1.f, 0.f),
	vec2(1.f, 1.f)
);

void main()
{
/*
	gl_Position = vec4(ver, 1.0);
    texPos_vs = texCoord;
	pos_vs = ver;
*/
	//gl_Position = vec4(ver[gl_VertexID], 1.0);
    texPos_vs = texCoord[gl_VertexID];
	pos_vs = ver[gl_VertexID];


}