#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>
#include <map>
#include <algorithm>


using point_t = std::pair< int, int >;


void roll_north( std::vector< std::string > & rocks )
{
	for( int i{ 1 }; i != rocks.size(); ++i )
		for( int j{ 0 }; j != rocks[ i ].length(); ++j )
			if( rocks[ i ][ j ] == 'O' )
				for( int k{ i - 1 }; ( k != -1 ) && ( rocks[ k ][ j ] == '.' ); --k )
				{
					rocks[ k ][ j ] = 'O';
					rocks[ k + 1 ][ j ] = '.';
				}
}

void roll_south( std::vector< std::string > & rocks )
{
	for( int i( rocks.size() - 1 ); i != -1; --i )
		for( int j{ 0 }; j != rocks[ i ].length(); ++j )
			if( rocks[ i ][ j ] == 'O' )
				for( int k{ i + 1 }; ( k != rocks.size() ) && ( rocks[ k ][ j ] == '.' ); ++k )
				{
					rocks[ k ][ j ] = 'O';
					rocks[ k - 1 ][ j ] = '.';
				}
}

void roll_west( std::vector< std::string > & rocks )
{
	for( std::string & s : rocks )
		for( int i{ 1 }; i != s.length(); ++i )
			if( s[ i ] == 'O' )
				for( int j{ i - 1 }; ( j != -1 ) && ( s[ j ] == '.' ); --j )
				{
					s[ j ] = 'O';
					s[ j + 1 ] = '.';
				}
}

void roll_east( std::vector< std::string > & rocks )
{
	for( std::string & s : rocks )
		for( int i( s.length() - 1 ); i != -1; --i )
			if( s[ i ] == 'O' )
				for( int j{ i + 1 }; ( j != s.length() ) && ( s[ j ] == '.' ); ++j )
				{
					s[ j ] = 'O';
					s[ j - 1 ] = '.';
				}
}


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );

	std::vector< std::string > rocks{ std::istream_iterator< std::string >( ifs ), std::istream_iterator< std::string >() };

	using cache_t = std::map< std::vector< std::string >, uint64_t >;
	cache_t cache;

	for( uint64_t cycles{ 0ULL }, total_cycles{ 1000000000ULL }; cycles != total_cycles; ++cycles )
	{
		cache_t::const_iterator i( cache.find( rocks ) );
		if( i != cache.end() )
		{
			cache_t::const_iterator x( std::find_if( cache.begin(), cache.end(),
				[ & ]( auto const & v ) -> bool
				{
					return v.second == i->second + ( ( total_cycles - i->second ) % ( cycles - i->second ) );
				}
			) );
			if( x != cache.end() )
			{
				rocks = x->first;
				break;
			}
		}
		else
			cache[ rocks ] = cycles;

		roll_north( rocks );
		roll_west( rocks );
		roll_south( rocks );
		roll_east( rocks );
	}


	size_t sum{ 0 }, x{ 0 };
	for( std::string const & s : rocks )
		sum += x += std::count( s.begin(), s.end(), 'O' );

	std::cout << "result = " << sum << std::endl;

	return 0;
}