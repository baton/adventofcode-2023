#

use strict;

my @c = ();
$c[ 1 ] = 1;
my $n = 1;
while( <> )
{
	$c[ $n ] = 1 if( !exists( $c[ $n ] ) );
	chomp;
	s/^[^:]+:\s//;
	my( $a, $b ) = split ' \| ';
	my %n = map{ $_ => 1 } split ' ', $b;

	my $v = 0;
	foreach my $x ( split ' ', $a )
	{
		++$v if( exists( $n{ $x } ) );
	}

	if( $v )
	{
		for ( 1 .. $v )
		{
			print ($n + $_ );print" ";
			$c[ $n + $_ ] = 1 if( !exists $c[ $n + $_ ] );
			$c[ $n + $_ ] += $c[ $n ];
		}
	}

	++$n;
}

my $sum = 0;
$sum += $_ for( @c );
print "result = $sum\n";