#

use strict;

my @ts = split '\s+', <>; shift @ts;
my @ds = split '\s+', <>; shift @ds;

my $ws = 1;
for my $t ( @ts )
{
	my $d = shift @ds;
	my $w = 0;

	for( my $tt = 0; $tt != $t; ++$tt )
	{
		++$w if( $tt * ( $t - $tt ) > $d );
	}

	$ws *= $w;
}

print "result = $ws\n";