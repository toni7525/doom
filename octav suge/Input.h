#pragma once
#include "mymath.h"
#include<windowsx.h>
inline void MovePlayer(float amount, map Map, Raycaster& raycast,vec2 &ppos,vec2 dir) {
    float distance;
    if (amount >= 0) {
        distance = raycast.ShotRayAccurate(ppos,dir).dis;
        if (distance > amount) {
            ppos.x += dir.x * amount;
            ppos.y += dir.y * amount;
        }
        else {
            ppos.x += dir.x * (distance - 1);
            ppos.y += dir.y * (distance - 1);
        }
    }
    else {
        distance = -raycast.ShotRayAccurate(ppos, { -dir.x, -dir.y }).dis;
        if (distance < amount) {
            ppos.x += dir.x * amount;
            ppos.y += dir.y * amount;
        }
        else {
            ppos.x -= dir.x * (distance - 1);
            ppos.y -= dir.y * (distance - 1);
        }
    }
}
inline void wob(float& woble, int& lastoffsety, float& offsety) {
    if (woble >= 0.3f) {
        switch (lastoffsety)
        {
        case 0:
            offsety = 0.0f;
            lastoffsety = 1;
            break;
        case 1:
            offsety = 0.025f;
            lastoffsety = 2;
            break;
        case 2:
            offsety = 0.0f;
            lastoffsety = 3;
            break;
        case 3:
            offsety = -0.025f;
            lastoffsety = 0;
            break;
        }
        woble = 0;
    }
}
inline void input(map Map, Raycaster &ray,float rotationspeed,float movespeed, vec2 &ppos, vec2 &dir,
    float deltatime,float &offsety,int &lastoffsety,float &woble,bool &in,vec2 deltamouseposition,bool &shoted, bool& lockcursor)
{

    rotatevec2(rotationspeed * deltamouseposition.x / 10, dir);
    //leftclick
    if (GetKeyState(XBUTTON1) & 0x8000) {
        shoted=true;
    }   
    if (GetKeyState('E') & 0x8000) {
        lockcursor = true;
    }
    if (GetKeyState('Q') & 0x8000) {
        lockcursor = false;
    }
    if (GetKeyState(VK_RIGHT) & 0x8000) {
        rotatevec2(rotationspeed / 3,dir);
    }
    if (GetKeyState(VK_LEFT) & 0x8000) {
        rotatevec2(-rotationspeed / 3, dir);
    }
    if (GetKeyState(VK_UP) & 0x8000) {
        MovePlayer(movespeed, Map, ray,ppos,dir);
        wob(woble, lastoffsety, offsety);
        in = false;
    }
    if (GetKeyState(VK_DOWN) & 0x8000) {
        MovePlayer(-movespeed, Map, ray, ppos, dir);
        wob(woble, lastoffsety, offsety);
        in = false;

    }
    if (GetKeyState('D') & 0x8000) {
        MovePlayer(movespeed, Map, ray, ppos, { dir.x * cos(1.56f) - dir.y * sin(1.56f),dir.x * sin(1.56f) + dir.y * cos(1.56f) });
        wob(woble, lastoffsety, offsety);
        in = false;
    }
    if (GetKeyState('A') & 0x8000) {
        MovePlayer(movespeed, Map, ray, ppos, { dir.x * cos(-1.56f) - dir.y * sin(-1.56f),dir.x * sin(-1.56f) + dir.y * cos(-1.56f) });
        wob(woble, lastoffsety, offsety);
        in = false;
    }
    if (GetKeyState('W') & 0x8000) {
        MovePlayer(movespeed, Map, ray, ppos, dir);
        wob(woble, lastoffsety, offsety);
        in = false;
    }
    if (GetKeyState('S') & 0x8000) {
        MovePlayer(-movespeed, Map, ray, ppos, dir);
        wob(woble, lastoffsety, offsety);
        in = false;

    }
    if (in) {
        lastoffsety = 0;
        offsety = 0.0f;
    }
    woble += deltatime;

}