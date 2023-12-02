#

use strict;

my $sum = 0;

while( <> )
{
	chomp;
	my( $g, $id, $t ) = split( ' ', $_, 3 );
	
	my( $mr, $mg, $mb ) = ( 0, 0, 0 );
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
		$mr = $r if( $mr < $r );
		$mg = $g if( $mg < $g );
		$mb = $b if( $mb < $b );
	}

	$sum += $mr * $mg * $mb;
}

print "result = $sum\n";