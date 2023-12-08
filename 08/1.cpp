#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <map>
#include <memory>


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

	std::string p{ "AAA" };
	size_t steps{ 0 };
	while( p != "ZZZ" )
	{
		char const i( instructions[ steps % instructions.length() ] );
		p = ( i == 'L' ) ? m[ p ].first : m[ p ].second;
		++steps;
	}

	std::cout << "result = " << steps << std::endl;

	return 0;
}