#pragma once
#include <iostream>
class map {
private:
	
public:
	int MapLayout[9999];
	int mapx, mapy,maps;
	map(std::string filepath);
	~map();
};