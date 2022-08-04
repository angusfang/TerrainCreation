#version 410

layout(triangles, equal_spacing, cw) in;
in vec3 pos_tcs[];
in vec2 texPos_tcs[];
out vec2 texPos_tes;
out float depth_tes;
uniform mat4 mv;
uniform mat4 p;
uniform sampler2D tex;

void main()
{
	vec2 px_ = gl_TessCoord.x * texPos_tcs[0];
	vec2 py_ = gl_TessCoord.y * texPos_tcs[1];
	vec2 pz_ = gl_TessCoord.z * texPos_tcs[2];
	texPos_tes = px_+py_+pz_;
	vec3 px = gl_TessCoord.x * pos_tcs[0];
	vec3 py = gl_TessCoord.y * pos_tcs[1];
	vec3 pz = gl_TessCoord.z * pos_tcs[2];
	depth_tes = texture(tex, texPos_tes).x;
	gl_Position =p*mv*vec4(px+py+pz+vec3(0.f,0.f,depth_tes)*0.5f, 1.0f);
	
	
}