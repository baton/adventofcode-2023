#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <string>
#include <list>
#include <map>
#include <algorithm>


struct rule_t
{
	bool is_condition{ false };
	bool is_gt{ false };
	int cmp{ 0 };
	std::string in, out;
};
using workflow_t = std::list< rule_t >;
using workflows_t = std::map< std::string, workflow_t >;

using part_t = std::map< std::string, int >;


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );

	workflows_t workflows;
	for( std::string wfs; std::getline( ifs, wfs ) && !wfs.empty(); )
	{
		wfs.pop_back(); // '}'
		size_t const br{ wfs.find( '{' ) };

		workflow_t & wf{ workflows[ wfs.substr( 0, br ) ] };

		std::istringstream iss( wfs.substr( br + 1 ) );
		for( std::string s; std::getline( iss, s, ',' ); )
		{
			rule_t & r{ wf.emplace_back() };
			if( ( s.length() > 2 ) && ( ( s[ 1 ] == '>' ) || ( s[ 1 ] == '<' ) ) )
			{
				r.is_condition = true;
				r.in.push_back( s[ 0 ] );
				r.is_gt = ( s[ 1 ] == '>' );
				s = s.substr( 2 );
				size_t const sc{ s.find( ':' ) };
				r.cmp = std::stoi( s.substr( 0, sc ) );
				r.out = s.substr( sc + 1 );
			}
			else
			{
				r.out = s;
			}
		}
	}

	int sum{ 0 };
	for( std::string ps; std::getline( ifs, ps ); )
	{
		ps.pop_back(); // '{', '}'

		part_t p;

		std::istringstream iss( ps.substr( 1 ) );
		for( std::string s; std::getline( iss, s, ',' ); )
			p[ s.substr( 0, 1 ) ] = std::stoi( s.substr( 2 ) );

		std::string label{ "in" };
		while( ( label != "A" ) && ( label != "R" ) )
		{
			workflow_t const & w{ workflows[ label ] };
			for( rule_t const & r : w )
			{
				if( r.is_condition )
				{
					if( r.is_gt )
					{
						if( p[ r.in ] < r.cmp )
							continue;
					}
					else
					{
						if( p[ r.in ] > r.cmp )
							continue;
					}
				}
				label = r.out;
				break;
			}
		}

		if( label == "A" )
			for( auto const & [ k, v ] : p )
				sum += v;
	}

	std::cout << "result = " << sum << std::endl;

	return 0;
}
