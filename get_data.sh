#!/usr/bin/env sh
# clean from previous
rm *.gz

ACTORS_FILE='name.basics.tsv.gz'
MOVIES_FILE='title.basics.tsv.gz'
BASE_URL='https://datasets.imdbws.com/'
ACTORS_URL="$(printf '%s%s' $BASE_URL $ACTORS_FILE)"
MOVIES_URL="$(printf '%s%s' $BASE_URL $MOVIES_FILE)"

wget $ACTORS_URL
wget $MOVIES_URL

gzip -dk $ACTORS_FILE
gzip -dk $MOVIES_FILE

if test -f data/; then
    echo 'Found data/ folder'
else
    echo 'Creating data/ folder'
    mkdir data
fi

# move them all to the data file which is .gitignore'd
mv *.tsv data/
