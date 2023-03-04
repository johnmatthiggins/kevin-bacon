#!/usr/bin/env python3
import pandas as pd
from neo4j import GraphDatabase

URI = 'neo4j://localhost:7687'

def main():
    df = pd.read_csv('data/name.basics.tsv', sep='\t')

    user = 'neo4j'
    passwd = 'Minetime14@'

    driver = GraphDatabase.driver(URI, auth=(user, passwd))

    with driver.session(database="neo4j") as session:
        for index, row in df.iterrows():
            print(row['nconst'], row['primaryName'])
            session.write_transaction(write_person, row['nconst'], row['primaryName'])


def write_person(tx, id, name):
    cypher_cmd = 'CREATE (n:Person { name: $name, id: $id})'
    tx.run(cypher_cmd, name=name, id=id)


if __name__ == '__main__':
    main()
