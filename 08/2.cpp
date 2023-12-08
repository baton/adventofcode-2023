#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <numeric>


using map_t = std::map< std::string, std::pair< std::string, std::string > >;


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );

	std::string instructions;
	std::getline( ifs, instructions );

	std::string s;
	std::getline( ifs, s ); // eat epmty line

	map_t m;
	while( !ifs.eof() )
	{
		std::getline( ifs, s );
		if( !s.empty() );
		{
			std::string::const_iterator b( s.begin() );
			m[ std::string( b, b + 3 ) ] =
				{ std::string( b + 7, b + 10 ), std::string( b + 12, b + 15 ) };
		}
	}

	std::vector< std::string > ps;
	for( auto const & [ k, v ] : m )
		if( k[ 2 ] == 'A' )
			ps.push_back( k );

	uint64_t steps_all{ 1 };
	for( std::string & p : ps )
	{
		uint64_t steps{ 0 };
		while( p[ 2 ] != 'Z' )
		{
			char const i( instructions[ steps % instructions.length() ] );
			p = ( i == 'L' ) ? m[ p ].first : m[ p ].second;
			++steps;
		}

		steps_all = std::lcm( steps_all, steps );
	}

	std::cout << "result = " << steps_all << std::endl;

	return 0;
}