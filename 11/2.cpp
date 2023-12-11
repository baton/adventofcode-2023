#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>
#include <set>
#include <memory>
#include <cmath>


using point_t = std::pair< int, int >;
using exp_t = std::set< int >;

uint64_t exp_dist( int const a, int  const b, exp_t const & e )
{
	uint64_t r{ 0 };
	int const d( a < b ? 1 : -1 );
	for( int t{ a }; t != b; t += d )
		if( e.count( t ) )
			r += 1000000;
		else
			r += 1;
	return r;
}


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );

	std::vector< std::string > lines{ std::istream_iterator< std::string >( ifs ), std::istream_iterator< std::string >() };

	exp_t ex;
	for( int x{ 0 }; x != lines[ 0 ].size(); ++x )
	{
		bool empty{ true };
		for( size_t y{ 0 }; y != lines.size(); ++y )
			empty &= lines[ y ][ x ] == '.';
		if( empty )
		 	ex.insert( x );
	}

	exp_t ey;
	for( int y{ 0 }; y != lines.size(); ++y )
		if( lines[ y ].find( '#' ) == std::string::npos )
			ey.insert( y );

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
			sum += exp_dist( a.first, b.first, ex ) + exp_dist( a.second, b.second, ey );
	}

	std::cout << "result = " << sum << std::endl;

	return 0;
}