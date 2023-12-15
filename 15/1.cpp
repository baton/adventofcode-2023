#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );

	uint64_t sum{ 0 }, x{ 0 };
	std::for_each(
		std::istream_iterator< char >( ifs ), std::istream_iterator< char >(),
		[ &sum, &x ]( char const c )
		{
			if( c == ',' )
			{
				sum += x;
				x = 0;
			}
			else
			{
				x = ( ( x + c ) * 17 ) % 256;
			}	
		}
	);
	sum += x;

	std::cout << "result = " << sum << std::endl;

	return 0;
}
