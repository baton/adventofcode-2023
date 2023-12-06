#

use strict;

my @ts = split '\s+', <>; shift @ts;
my @ds = split '\s+', <>; shift @ds;

my $t = join '', @ts;
my $d = join '', @ds;

my $w = 0;

for( my $tt = 0; $tt != $t; ++$tt )
{
	++$w if( $tt * ( $t - $tt ) > $d );
}

print "result = $w\n";