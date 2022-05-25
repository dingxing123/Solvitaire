#!/bin/bash

echo "根据spider.json求解：指定种子范围，可自定义运行参数"

if [ "$#" != 4 ]; then
    echo "Usage: <from> <to> \"<solvitaire_command>\" <output_file>"
    echo "e.g.: ./solvability-range-param.sh 10000 10001 \"./solvitaire --custom-rules customRules/Spider.json --timeout 30000 --str smart-solvability --ra {} --class\" output/test1"
    exit 1
fi

from="$1"
to="$2"
cores=6 #"$3"
sol_command="$3"
minramfree="1G"
out="$4"
time_command="/usr/bin/time -f \" %e, %U, %S\""
combine_command="sed -n '/,/p'"

echo "Attempted Seed, Outcome, Time Taken(ms), States Searched, Unique States Searched, Backtracks, Dominance Moves, States Removed From Cache, Final States In Cache, Final Buckets In Cache, Maximum Search Depth, Final Search Depth, real (time), user (time), sys (time) " > "$out.csv"

seq $from $to | parallel --joblog $out.log --progress --memfree $minramfree -j"$cores" "exec $time_command $sol_command | $combine_command >> $out.csv"


