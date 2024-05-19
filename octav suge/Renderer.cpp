#include "Renderer.h"
#include <GL/glew.h>
#include <Windows.h>
#include "Input.h"
Renderer::Renderer(map& map):Map(map)
{
}
void Renderer::render(shader& shade, Raycaster raycast, vec2 dir, vec2 playerpos,int quality,float fov,float spacing)
{ 
        shade.Bind();
        shade.SetUniform1i("coltipe", 0);  
        rotatevec2(fov ,dir);
        for (int i = 0;i < fov * quality;i++) {
            Raydata ray = raycast.ShotRayAccurate(playerpos, dir);
            //vec4(0.6f,0.3f,0.3f,1.0f)
            double offset = i * spacing / quality;
            shade.SetUniform1f("depth", ray.dis);
            shade.SetUniform1f("offsetx", offset);
            switch (ray.col) {
                //brown
            case 1:shade.SetUniform4f("wallcol", 0.6f, 0.3f, 0.3f, 1.0f);
                break;
                //red
            case 2:shade.SetUniform4f("wallcol", 1.0f, 0.0f, 0.0f, 1.0f);
                break;
                //blue
            case 3:shade.SetUniform4f("wallcol", 0.0f, 0.0f, 1.0f, 1.0f);
                break;
                //grene
            case 4:shade.SetUniform4f("wallcol", 0.0f, 1.0f, 0.1f, 1.0f);
                break;
                //purple
            case 5:shade.SetUniform4f("wallcol", 0.6f, 0.3f, 1.0f, 1.0f);
                break;
                //yellow
            case 6:shade.SetUniform4f("wallcol", 1.0f, 1.0f, 0.0f, 1.0f);
                break;
            }
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
            rotatevec2(1.0f / (10 * quality),dir);
        }
}

void Renderer::rendermap(vec2 ppos)
{
	for (int i = 0;i < Map.mapx * Map.mapy;i++) {
		if (i % Map.mapx == 0) {
			std::cout << std::endl;
		}
		if ((int)ppos.x == i % Map.mapy + 1 && (int)ppos.y == i / Map.mapy + 1) {
			std::cout << "o";
		}
		else if (Map.MapLayout[i] >= 1) {
			std::cout << "#";
		}
		else {
			std::cout << " ";
		}
	}
}

void Renderer::NewMap(map& map, Raycaster ray)
{
	ray.NewMap(map);
	Map = map;
}

void Renderer::ClearConsole()
{
	system("CLS");
}

void Renderer::ClearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT);
}
