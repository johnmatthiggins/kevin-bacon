#!/usr/bin/env zsh
ACTORS_FILE='name.basics.tsv.gz'
MOVIES_FILE='title.basics.tsv.gz'
BASE_URL='https://datasets.imdbws.com/'
ACTORS_URL="$(printf '%s%s' $BASE_URL $ACTORS_FILE)"
MOVIES_URL="$(printf '%s%s' $BASE_URL $MOVIES_FILE)"

curl $ACTORS_URL -o $ACTORS_FILE
curl $MOVIES_URL -o $MOVIES_FILE

gzip -dk $ACTORS_FILE
gzip -dk $MOVIES_FILE

if test -f "data"; then
else
    mkdir "data"
fi

# move them all to the data file which is .gitignore'd
mv *.tsv data/
