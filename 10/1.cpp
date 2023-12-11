#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>
#include <array>
#include <map>
#include <memory>


using point_t = std::pair< int, int >;
using pipes_t = std::map< char, std::map< point_t, point_t > >;

pipes_t const pipes{
	{ '|', { { { 0, 1 }, { 0, 1 } }, { { 0, -1 }, { 0, -1 } } } },
	{ '-', { { { 1, 0 }, { 1, 0 } }, { { -1, 0 }, { -1, 0 } } } },
	{ 'F', { { { 0, -1 }, { 1, 0 } }, { { -1, 0 }, { 0, 1 } } } },
	{ '7', { { { 1, 0 }, { 0, 1 } }, { { 0, -1 }, { -1, 0 } } } },
	{ 'J', { { { 0, 1 }, { -1, 0 } }, { { 1, 0 }, { 0, -1 } } } },
	{ 'L', { { { 0, 1 }, { 1, 0 } }, { { -1, 0 }, { 0, -1 } } } },
};
point_t const ds[ 4 ]{ { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };

inline point_t operator+( point_t const & a, point_t const & b )
{
	return { a.first + b.first, a.second + b.second };
}

inline bool valid( point_t const & p, std::vector< std::string > const & lines )
{
	if( p.first < 0 )
		return false;
	if( p.second < 0 )
		return false;
	if( p.second >= lines.size() )
		return false;
	if( p.first >= lines[ p.second ].size() )
		return false;

	return true;
}


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );

	std::vector< std::string > const lines{ std::istream_iterator< std::string >( ifs ), std::istream_iterator< std::string >() };

	point_t s; bool found{ false };
	for( s.second = 0; s.second != lines.size() && !found; ++s.second )
		for( s.first = 0; s.first != lines[ s.second ].size() && !found; ++s.first )
			found = lines[ s.second ][ s.first ] == 'S';
	--s.first; --s.second;

	point_t x, d;
	for( point_t const t : ds )
	{
		x = s + t;
		if( valid( x, lines ) )
		{
			char const c{ lines[ x.second ][ x.first ] };

			if( pipes.count( c ) && pipes.at( c ).count( t ) )
			{
				d = t;

				break;
			}
		}
	}

	size_t length{ 1 };
	for( ; x != s; x = x + d, ++length )
	{
		char const c{ lines[ x.second ][ x.first ] };
		d = pipes.at( c ).at( d );
	}
	length >>= 1;

	std::cout << "result = " << length << std::endl;

	return 0;
}