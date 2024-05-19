#include "RayCaster.h"

Raycaster::Raycaster(map& newmap) :Map(newmap)
{
}

float Raycaster::ShotRay(vec2& ppos, vec2 dirv, vec2& plane)
{
    //double cameraX = 2 * x / double(w) - 1;
    double rayDirX = dirv.x ;
    double rayDirY = dirv.y ;
    int mapX = int(ppos.x);
    int mapY = int(ppos.y);

    //length of ray from current position to next x or y-side
    double sideDistX;
    double sideDistY;

    //length of ray from one x or y-side to next x or y-side
    double deltaDistX = (rayDirX == 0) ? 1e30 : std::abs(1 / rayDirX);
    double deltaDistY = (rayDirY == 0) ? 1e30 : std::abs(1 / rayDirY);
    double perpWallDist;

    //what direction to step in x or y-direction (either +1 or -1)
    int stepX;
    int stepY;

    int hit = 0; //was there a wall hit?
    int side; //was a NS or a EW wall hit?

    if (rayDirX < 0)
    {
        stepX = -1;
        sideDistX = (ppos.x - mapX) * deltaDistX;
    }
    else
    {
        stepX = 1;
        sideDistX = (mapX + 1.0 - ppos.x) * deltaDistX;
    }
    if (rayDirY < 0)
    {
        stepY = -1;
        sideDistY = (ppos.y - mapY) * deltaDistY;
    }
    else
    {
        stepY = 1;
        sideDistY = (mapY + 1.0 - ppos.y) * deltaDistY;
    }
    while (hit == 0)
    {
        //jump to next map square, either in x-direction, or in y-direction
        if (sideDistX < sideDistY)
        {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0;
        }
        else
        {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = 1;
        }
        //Check if ray has hit a wall
        if (Map.MapLayout[Map.mapx * mapY + mapX -1] > 0) 
            hit = 1;
    }
    if (side == 0) perpWallDist = (sideDistX - deltaDistX);
    else          perpWallDist = (sideDistY - deltaDistY);
    return perpWallDist;
}

Raydata Raycaster::ShotRayAccurate(vec2& ppos, vec2 dirv)
{
   
    double rayDirX = dirv.x;
    double rayDirY = dirv.y;
    int mapX = int(ppos.x);
    int mapY = int(ppos.y);

    double sideDistX;
    double sideDistY;

    double deltaDistX = (rayDirX == 0) ? 1e30 : std::abs(1 / rayDirX);
    double deltaDistY = (rayDirY == 0) ? 1e30 : std::abs(1 / rayDirY);
    double perpWallDist;

    int stepX;
    int stepY;

    int hit = 0; //was there a wall hit?
    int side; //was a NS or a EW wall hit?

    if (rayDirX < 0)
    {
        stepX = -1;
        sideDistX = (ppos.x - mapX) * deltaDistX;
    }
    else
    {
        stepX = 1;
        sideDistX = (mapX + 1.0 - ppos.x) * deltaDistX;
    }
    if (rayDirY < 0)
    {
        stepY = -1;
        sideDistY = (ppos.y - mapY) * deltaDistY;
    }
    else
    {
        stepY = 1;
        sideDistY = (mapY + 1.0 - ppos.y) * deltaDistY;
    }
    int hitnr;
    while (hit == 0)
    {
        if (sideDistX < sideDistY)
        {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0;
        }
        else
        {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = 1;
        }
        if (Map.MapLayout[Map.mapx * mapY + mapX - 1] > 0) {
            hitnr=Map.MapLayout[Map.mapx * mapY + mapX - 1];
            hit = 1;
        }
    }
    if (side == 0) perpWallDist = (sideDistX - deltaDistX);
    else          perpWallDist = (sideDistY - deltaDistY);
    return { (float)perpWallDist,hitnr };
}

void Raycaster::NewMap(map& newmap)
{
    Map = newmap;
}

