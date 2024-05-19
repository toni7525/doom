#pragma once
#include <math.h>
struct vec2
{
	float x;
	float y;
};
struct vec3
{
	float x;
	float y;
	float z;
	
};
struct vec4
{
	float x;

	float y;
	float z;
	float W;
	
};
inline float dis(vec2 startp, vec2 endp) {
	return sqrt((startp.x - endp.x)* (startp.x - endp.x)+ (startp.y - endp.y)* (startp.y - endp.y));
};
struct Vertex
{
	vec3 pos;
};
struct Raydata
{
	float dis;
	int col;
};
inline void rotatevec2(float amount, vec2& dir) {
	float OldDirx = dir.x;
	dir.x = dir.x * cos(amount) - dir.y * sin(amount);
	dir.y = OldDirx * sin(amount) + dir.y * cos(amount);
}
