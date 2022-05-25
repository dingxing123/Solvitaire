#!/bin/bash

echo "根据spider.json求解：指定种子范围"

if [ "$#" != 3 ]; then
    echo "Usage: <from> <to> <output_file>"
    echo "e.g.: ./solvability-range.sh 10000 10001  output/test1"
    exit 1
fi

from="$1"
to="$2"
cores=6 #"$3"
#sol_command="$3"
minramfree="1G"
out="$3"
time_command="/usr/bin/time -f \" %e, %U, %S\""
combine_command="sed -n '/,/p'"

echo "Attempted Seed, Outcome, Time Taken(ms), States Searched, Unique States Searched, Backtracks, Dominance Moves, States Removed From Cache, Final States In Cache, Final Buckets In Cache, Maximum Search Depth, Final Search Depth, real (time), user (time), sys (time) " > "$out.csv"

seq $from $to | parallel --joblog $out.log --progress --memfree $minramfree -j"$cores" "exec $time_command ./solvitaire --custom-rules customRules/Spider.json --timeout 30000 --str smart-solvability --ra {} --class   | $combine_command  >> $out.csv"


