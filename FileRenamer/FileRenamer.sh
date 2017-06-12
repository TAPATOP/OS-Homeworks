#!/bin/bash

if [ $# -ne 1 ]; then
  echo "Hi, I am an Albanian virus but because of poor technology in my country unfortunately I am not able to harm your computer. Please be so kind to delete one of your important files yourself and then forward me to other users. Many thanks for your cooperation! Best regards, Albanian virus
P.S: Try giving me exactly one argument next time"
  exit 1
fi

#dpkg -l | grep exiftool>/dev/null
#if [ $? -eq 1 ]; then
#  echo If you want to have the full functionality, install exiftool, please.
#else
#  STATUS=1
#fi

for foldr in `find "$1" -type d | sed '1d'`; do
  if [[ -e "$foldr.log" ]]; then
    CNTR=0
    FILES=()
    INDEX=0

    for FILE in `ls ./"$foldr" -lctr | grep ".jpg" | tr -s " " | cut -f 9 -d " "`;do
      FILES+=($FILE)
    done

    while read LINE; do
      VAR=`printf "%d" "'$LINE"`
      CNTR=$(($CNTR+1))
      if [ $CNTR -lt 3 ]; then
        if [ $CNTR -eq 1 ]; then
	  DATE=$(echo $LINE | cut -f 1 -d ' ')
	  DDATE=$(date --date=@$DATE -Is | cut -f 1,2 -d ':' | tr -d ':')
	  COORDS=$(echo $LINE | cut -f 2 -d ' ')
	  LONGITUDE=$(echo $COORDS | cut -f 1 -d ',')
	  LATITUDE=$(echo $COORDS | cut -f 2 -d ',')
	else
	  TRANS=$(echo $LINE | tr [:upper:] [:lower:] | tr " " "_" | sed 's/[^[:alnum:]|_]//g')
          NEWNAME="$DDATE"_"$TRANS".jpg
	  mv "$foldr"/"${FILES[$INDEX]}" "$foldr"/"$NEWNAME"
	  INDEX=$((INDEX+1))
#	  if [ $STATUS -eq 1 ]; then
#	    exiftool -GPSLongitude="$LONGITUDE" -GPSLatitude="$LATITUDE" -overwrite_original_in_place "$foldr"/"$NEWNAME"
#  	  fi
	fi
      continue
      fi
      
      if [[ "$VAR" -eq 0 ]]; then
        CNTR=0
      fi
    done<$foldr.log
  fi
done
