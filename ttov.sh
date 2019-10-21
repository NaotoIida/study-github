#!/bin/bash

#i---Change zenkaku number to hankaku number.
#ii--Use mecab to text.
#iii-Change , to \t on result of mecab.
#iv--Pick up first clumn and six clumn of macab and make each files.
#v---Count the number of lines of words,text.
#vi--Integrate first clumn and six clumn.
#vii--words in the text convert vector.
#viii-text segmentated by ruby

origintext=$1
nkf -Z $origintext > data/hansu_${origintext#*/}
echo finish converting from Zenkaku to Hankaku.

mecab data/hansu_${origintext#*/} -o data/mecab_${origintext#*/}
echo finish mecab.

./clm_fil.o data/mecab_${origintext#*/} data/svd_${origintext#*/}
echo finish clm_frl.o.

cut -f 1 data/svd_${origintext#*/} > data/firclm_${origintext#*/}
cut -f 6 data/svd_${origintext#*/} > data/sixclm_${origintext#*/}
echo finish cutting up svddata.

lines=$(wc -l data/firclm_${origintext#*/} | grep -o '[0-9]*')
echo finish extract lines.

./clm_intg.o data/firclm_${origintext#*/} data/sixclm_${origintext#*/} data/intgclm_${origintext#*/} $lines
echo finish clm_intg.o.

./tchanv.o word2vec/wikivectors-v2.bin $lines data/intgclm_${origintext#*/} data/desrep_${origintext#*/}
echo finish tchanv.o.

ruby tex_seg.rb data/desrep_${origintext#*/} data/cal_${origintext#*/}
echo complete ttov.sh.
