#!/bin/bash

ORIG=$IFS
IFS=$'\0'
FLAG=0
if [ $# -eq 1 ]; then
  SPATH="./$1"
  ARRAY=()
  while read -r -d '' FILE; do
    ARRAY+=($FILE)
  done< <(find "$SPATH" -type f -print0)

  IFS=$ORIG

  LIMIT=${#ARRAY[@]}
  COUNT=$LIMIT

  for i in `seq 0 $(($LIMIT-1))`;
  do
    if [ -f "${ARRAY[$i]}" ]; then
      for j in `seq $(($i+1)) $(($LIMIT-1))`;
      do
        if [ -f "${ARRAY[$j]}" ]; then
          cmp "${ARRAY[$i]}" "${ARRAY[$j]}" >/dev/null
          if [ $? -eq 0 ]; then
            rm "${ARRAY[$j]}"
            COUNT=$(($COUNT-1))
            FLAG=1
          fi
        fi
      done
      if [ $FLAG -eq 1 ]; then
        rm "${ARRAY[$i]}"
        FLAG=0
      fi
    fi
  done
  echo $COUNT
else
  echo pls gib one argument
fi