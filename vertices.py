#!/usr/bin/env python3

import pandas as pd

def main():
    df = pd.read_csv('data/edges.tsv', header=None, sep='\t')
    df_dict = df.head(100).to_dict('records')

    for row in df_dict[:]:
        print(row)


if __name__ == '__main__':
    main()
