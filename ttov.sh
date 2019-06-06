#!/bin/bash
origintext=$1
nkf -Z $origintext > data/hansu_${origintext#*/}

mecab data/hansu_${origintext#*/} -o data/macab_${origintext#*/}

cut -f 1 data/macab_${origintext#*/} > data/firclm_${origintext#*/}
cut -f 2 data/macab_${origintext#*/} > data/subsixclm_${origintext#*/}

line=$(wc -l data/wakati_${origintext#*/} | grep -o '[0-9]*')
