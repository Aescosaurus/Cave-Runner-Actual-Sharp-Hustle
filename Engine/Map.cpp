#include "Map.h"

std::vector<char> Map::Data;

void Map::Load( const std::string& filePath )
{
	Data.clear();

	std::ifstream in( filePath );
	assert( in.good() );

	for( int y = 0; y < Height; ++y )
	{
		for( int x = 0; x < Width; ++x )
		{
			const char next = in.get();
			Data.emplace_back( next );
		}
	}
}

char Map::Get( int x,int y )
{
	assert( x >= 0 && x < Width );
	assert( y >= 0 && y < Height );
	return( Get( y * Width + x ) );
}

char Map::Get( int index )
{
	assert( index >= 0 && index < Width * Height );
	return( Data.data()[index] );
}