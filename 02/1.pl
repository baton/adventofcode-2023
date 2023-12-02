#

use strict;

my $sum = 0;

MAIN: while( <> )
{
	chomp;
	my( $g, $id, $t ) = split( ' ', $_, 3 );
	$id =~ s/://;
	
	my @a = split( '; ', $t );
	foreach( @a )
	{
		my( $r, $g, $b ) = ( 0, 0, 0 );
		my @b = split( ', ', $_ );
		foreach( @b )
		{
			$r = $1 if( m/(\d+) red/ );
			$g = $1 if( m/(\d+) green/ );
			$b = $1 if( m/(\d+) blue/ );
		}
		next MAIN if( ( $r > 12 ) || ( $g > 13 ) || ( $b > 14 ) );
	}

	$sum += $id;
}

print "result = $sum\n";