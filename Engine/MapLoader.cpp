#include "MapLoader.h"
#include "Map.h"

std::vector<Platform> MapLoader::LoadMap( const std
	::string& fileName,const Vei2& posOffset )
{
	std::vector<Platform> plats;

	Map::Load( fileName );

	for( int y = 0; y < Map::Height; ++y )
	{
		for( int x = 0; x < Map::Width; ++x )
		{
			if( Map::Get( x,y ) == '1' )
			{
				plats.emplace_back( Platform( { posOffset
					.x + x * 32,posOffset.y + y * 32 } ) );
			}
		}
	}

	return plats;
}

void MapLoader::AddPlats( const std::string& fileName,
	const Vei2& posOffset,std::vector<Platform>& plats,
	std::vector<Spike>& spikes,std::vector<Enemy>& enemies )
{
	Map::Load( fileName );

	for( int y = 0; y < Map::Height; ++y )
	{
		for( int x = 0; x < Map::Width; ++x )
		{
			if( Map::Get( x,y ) == '1' )
			{
				plats.emplace_back( Platform( { posOffset
					.x + x * 32,posOffset.y + y * 32 } ) );
			}
			else if( Map::Get( x,y ) == '2' )
			{
				spikes.emplace_back( Spike( Vec2( Vei2{ posOffset
					.x + x * 32,posOffset.y + y * 32 } ) ) );
			}
			else if( Map::Get( x,y ) == '3' )
			{
				enemies.emplace_back( Enemy( Vec2( Vei2{ posOffset
					.x + x * 32,posOffset.y + y * 32 } ) ) );
			}
		}
	}
}

std::string MapLoader::GetLevel( int n )
{
	return( "Maps/Level" + std::to_string( n ) + ".lvl" );
}

void MapLoader::UpdateNLevels( int& n )
{
	for( int i = n; i < 9999999; ++i )
	{
		const std::string name = "Maps/Level" + std::to_string( i ) + ".lvl";
		std::ifstream test( name );

		if( test.good() )
		{
			n = i;
		}
		else
		{
			break;
		}
	}
}
