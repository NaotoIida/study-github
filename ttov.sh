#!/bin/bash
origintext=$1
nkf -Z $origintext > data/hansu_${origintext#*/}

mecab data/hansu_${origintext#*/} -o data/mecab_${origintext#*/}

./clm_fil.o data/mecab_${origintext#*/} data/svd_${origintext#*/}

cut -f 1 data/svd_${origintext#*/} > data/firclm_${origintext#*/}
cut -f 6 data/svd_${origintext#*/} > data/sixclm_${origintext#*/}

line=$(wc -l data/wakati_${origintext#*/} | grep -o '[0-9]*')
