#!/usr/bin/env python3
from collections import defaultdict
import pandas as pd

ACTORS_FILE = 'data/name.basics.tsv'
CONNECTIONS_FILE = 'data/edges.tsv'

def main():
    df = pd.read_csv(ACTORS_FILE, sep='\t')

    # filter out all the actors that aren't known for movies.
    df = df[~df['knownForTitles'].isin(['\\N'])]

    multimap = defaultdict(set)

    for index, row in df.iterrows():
        print('[%d] Processing %s' %(index, row['primaryName']))
        titles = row['knownForTitles'].split(',')

        for title in titles:
            multimap[title].add(row['nconst'])

    del df

    f = open(CONNECTIONS_FILE, 'w')

    k = 0
    for key, value in multimap.items():
        actors = list([actor for actor in value])
        k += 1

        print('%d / %d' %(k, len(multimap)))

        for i in range(0, len(actors) - 1):
            for j in range(i + 1, len(actors)):
                f.write('%s\t%s\n' %(actors[i], actors[j]))

    f.close()

    print('FINISHED WRITING %d CONNECTIONS to data/edges.tsv')


if __name__ == '__main__':
    main()
