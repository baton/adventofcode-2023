#

use strict;

my %hands = ();
while( <> )
{
	chomp;
	my( $h, $s ) = split '\s+';
	$hands{ $h } = $s;
}

my $sum = 0;
my $r = 1;
$sum += $r++ * $hands{ $_ } foreach( sort handcmp keys %hands );

print "result = $sum\n";

sub handcmp
{
	my @aa = split '', $a;
	my @bb = split '', $b;

	my @ia = map { index( "23456789TJQKA", $_ ) } @aa;
	my @ib = map { index( "23456789TJQKA", $_ ) } @bb;

	my %ta = ();
	++$ta{ $_ } foreach( @aa );
	my $tas = keys %ta;
	my %tb = ();
	++$tb{ $_ } foreach( @bb );
	my $tbs = keys %tb;

	if( $tas != $tbs )
	{
		return $tbs <=> $tas;
	}

	if( $tas == 1 )
	{
		return $ib[ 0 ] <=> $ia[ 0 ];
	}

	my @va = sort values %ta;
	my @vb = sort values %tb;

	if( $tas == 2 )
	{
		return $va[ 1 ] <=> $vb[ 1 ] if( $va[ 1 ] != $vb[ 1 ] );
	}

	if( $tas == 3 )
	{
		return $va[ 2 ] <=> $vb[ 2 ] if( $va[ 2 ] != $vb[ 2 ] );
	}

	for( my $i = 0; $i != $#ia+1; ++$i )
	{
		return $ia[ $i ] <=> $ib[ $i ] if( $ia[ $i ] != $ib[ $i ] );
	}

	return 0;
}
