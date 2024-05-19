#include "Map.h"
#include <fstream>
map::map(std::string filepath)
{
	std::ifstream mappat(filepath);
	int x,i=0,off = 0,ai=0;
	mappat >> x;
	mapx = x;
	mappat >> x;
	mapy = x;
	mappat >> x;
	maps = x;
	
	mapx = mapx * maps; 
	
	while (mappat >> x) {
		for (int j = 0;j < maps;j++) {
			MapLayout[i] = x;
			i++;
		}	
	}
	int oldmapy = mapy;
	mapy = mapy * maps;
	//copy from line x to y
	int cl , pl;
	for (int j = oldmapy;j >= 0;j--) {
		cl = j;
		for (int p = 0;p < maps;p++) {
			pl = j * maps - p;
			for (int l = 0;l < mapx;l++) {
				MapLayout[l + pl * mapx] = MapLayout[l + cl * mapx];
			}
		}
	}
}

map::~map()
{
}
