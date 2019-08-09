#!/bin/bash

#i---Change zenkaku number to hankaku number.
#ii--Use mecab to text.
#iii-Change , to \t on result of mecab.
#iv--Pick up first clumn and six clumn of macab and make each files.
#v---Count the number of lines of words,text.
#vi--Integrate first clumn and six clumn.
#vii--words in the text convert vector.

origintext=$1
nkf -Z $origintext > data/hansu_${origintext#*/}

mecab data/hansu_${origintext#*/} -o data/mecab_${origintext#*/}

./clm_fil.o data/mecab_${origintext#*/} data/svd_${origintext#*/}

cut -f 1 data/svd_${origintext#*/} > data/firclm_${origintext#*/}
cut -f 6 data/svd_${origintext#*/} > data/sixclm_${origintext#*/}

lines=$(wc -l data/firclm_${origintext#*/} | grep -o '[0-9]*')

./clm_intg.o data/firclm_${origintext#*/} data/sixclm_${origintext#*/} data/intgclm_${origintext#*/} $lines

./tchanv.o word2vec/wikivectors-v2.bin $lines data/intgclm_${origintext#*/} data/desrep_${origintext#*/}
