#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>
#include <array>
#include <map>
#include <set>
#include <memory>


using point_t = std::pair< int, int >;
using pipes_t = std::map< char, std::map< point_t, point_t > >;
using loop_t = std::set< point_t >;

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

	std::vector< std::string > lines{ std::istream_iterator< std::string >( ifs ), std::istream_iterator< std::string >() };

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
	point_t d0{ d };

	loop_t loop;
	loop.insert( s );
	for( ; x != s; x = x + d )
	{
		loop.insert( x );
		char const c{ lines[ x.second ][ x.first ] };
		d = pipes.at( c ).at( d );
	}

	for( auto const & [ k, v ] : pipes )
		if( v.count( d ) && ( v.at( d ) == d0 ) )
		{
			lines[ s.second ][ s.first ] = k;
			break;
		}

	size_t insides{ 0 };
	for( x.second = 0; x.second != lines.size(); ++x.second )
	{
		bool inside{ false };
		char t{ '.' };

		for( x.first = 0; x.first != lines[ x.second ].size(); ++x.first )
		{
			if( loop.count( x ) )
			{
				char const c{ lines[ x.second ][ x.first ] };
				switch( c )
				{
					case '|': inside = !inside; break;
					case '-': break;
					default:
						if( t == '.' )
						{
							t = c;
						}
						else
						{
							if( ( ( c == '7' ) && ( t == 'L' ) )
								|| ( c == 'J' ) && ( t == 'F' ) )
								inside = !inside;
							t = '.';
						}
						break;
				}
			}
			else
			{
				if( inside )
					++insides;
			}
		}
	}

	std::cout << "result = " << insides << std::endl;

	return 0;
}