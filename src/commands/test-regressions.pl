#!/usr/bin/perl -w

use strict;
use IPC::Open2;


my ($regressionFilename, $commandPath) = @ARGV;
die unless defined $commandPath;

print "This is $0.\n";
print "Regressions read from file: $regressionFilename\n";
print "Command path: $commandPath\n";

if (! -e $commandPath)
{
    print "ERROR: $commandPath does not exist\n";
    exit 1;
}
if (! -f $commandPath)
{
    print "ERROR: $commandPath is not a regular file\n";
    exit 1;
}
if (! -x $commandPath)
{
    print "ERROR: $commandPath is not an executable file\n";
    exit 1;
}


sub runCommand($)
{
    my ($inputExpr) = @_;

    my ($reader, $writer);
    if (!open2($reader, $writer, $commandPath))
    {
        return "<failed to run $commandPath>";
    }

    print $writer "$inputExpr\n";
    if (!close($writer))
    {
        return "<failed to close writing pipe to $commandPath>";
    }

    my @lines;
    while (my $line = <$reader>)
    {
        push @lines, $line;
    }

    if (!close($reader))
    {
        return "<failed to close reading pipe to $commandPath>";
    }

    my $actualOutput = join("", @lines);
    $actualOutput =~ s/\n$//;  # remove trailing newline
    return $actualOutput;
}


my $regressionFile;
if (!open($regressionFile, $regressionFilename))
{
    print "ERROR: failed to open $regressionFilename: $!\n";
    exit 1;
}

my $numTests = 0;
my $numErrors = 0;

while (<$regressionFile>)
{
    if (/^(.*?)\s*=>\s+(.*?)$/)
    {
        my ($inputExpr, $expectedOutput) = ($1, $2);

        $numTests++;
        printf("Test at line %3u: %s => %s", $., $inputExpr, $expectedOutput);

        my $actualOutput = runCommand($inputExpr);

        if ($actualOutput ne $expectedOutput)
        {
            print "\nERROR: DNF of '$inputExpr' expected to be '$expectedOutput', got '$actualOutput'\n";
            $numErrors++;
        }
        else
        {
            print " => OK\n";
        }
    }
    elsif (/^#/ || /^\s*$/)  # ignore comments and blank lines
    {
    }
    else
    {
        print "ERROR: line $. of $regressionFilename contains invalid line: $_";
        exit 1;
    }
}

if (!close($regressionFile))
{
    print "ERROR: failed to close $regressionFilename: $!\n";
    exit 1;
}

print "End of $0: $numErrors error(s) out of $numTests tests.\n";
exit($numErrors != 0);
