#version 410

layout(vertices = 3) out;
in vec3 pos_vs[];
in vec2 texPos_vs[];
out vec3 pos_tcs[];
out vec2 texPos_tcs[];
uniform int wheel;

void main()
{
	pos_tcs[gl_InvocationID] = pos_vs[gl_InvocationID];
	texPos_tcs[gl_InvocationID] = texPos_vs[gl_InvocationID];

	if(gl_InvocationID==0){
	gl_TessLevelInner[0] = wheel;
	gl_TessLevelOuter[0] = wheel;
	gl_TessLevelOuter[1] = wheel;
	gl_TessLevelOuter[2] = wheel;
	}
	
}