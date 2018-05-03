#pragma once

#include <string>
#include <vector>
#include "Platform.h"
#include "Spike.h"
#include "Enemy.h"
#include "Grass.h"

class MapLoader
{
public:
	static std::vector<Platform> LoadMap( const std
		::string& fileName,const Vei2& posOffset );
	static void AddPlats( const std::string& fileName,
		const Vei2& posOffset,
		std::vector<Platform>& plats,
		std::vector<Spike>& spikes,
		std::vector<Enemy>& enemies,
		std::vector<Grass>& grasses );
	static std::string GetLevel( int n );
	static void UpdateNLevels( int& n );
private:
};