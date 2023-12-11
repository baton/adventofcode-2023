#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>
#include <memory>
#include <cmath>


using point_t = std::pair< int, int >;


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );

	std::vector< std::string > lines{ std::istream_iterator< std::string >( ifs ), std::istream_iterator< std::string >() };

	for( size_t x{ 0 }; x != lines[ 0 ].size(); ++x )
	{
		bool empty{ true };
		for( size_t y{ 0 }; y != lines.size(); ++y )
			empty &= lines[ y ][ x ] == '.';
		if( empty )
		{
			for( std::string & s : lines )
				s.insert( x, "." );
			++x;
		}
	}
	for( std::vector< std::string >::const_iterator i{ lines.begin() }; i != lines.end(); ++i )
		if( i->find( '#' ) == std::string::npos )
			lines.insert( i++, *i );

	std::vector< point_t > points;
	
	for( int y{ 0 }; y != lines.size(); ++y )
		for( int x{ 0 }; x != lines[ y ].size(); ++x )
			if( lines[ y ][ x ] == '#' )
				points.emplace_back( x, y );
			
	size_t sum{ 0 };
	while( !points.empty() )
	{
		point_t a( points.back() );
		points.pop_back();

		for( point_t const & b : points )
			sum += std::abs( a.first - b.first ) + std::abs( a.second - b.second );
	}

	std::cout << "result = " << sum << std::endl;

	return 0;
}