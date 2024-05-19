#pragma once
#include "mymath.h"
#include "Map.h"
class Raycaster
{
private:
	map Map;
public:
	Raycaster(map& newmap);
	float ShotRay(vec2 &ppos,vec2 dirv,vec2 &plane);
	Raydata ShotRayAccurate(vec2& ppos, vec2 dirv);
	void NewMap(map& newmap);
};