#pragma once
#include"RayCaster.h"
#include"shader.h"
class Renderer {
private:
    map Map;
public:
    Renderer(map& map);
    void render(shader& shade, Raycaster raycast, vec2 dir, vec2 playerpos, int quality, float fov,float spacing);
    void rendermap(vec2 ppos);
    void NewMap(map& map,Raycaster ray);
    void ClearConsole();
    void ClearScreen();
};