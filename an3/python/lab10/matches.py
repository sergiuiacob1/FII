import os
import random
import sys


def match(team_paths, dates_path):
    teams_1, teams_2, dates = set(), set(), set()
    with open(team_paths[0], 'r') as f1, open(team_paths[1], 'r') as f2:
        for line in f1:
            teams_1.add(line.strip())
        for line in f2:
            teams_2.add(line.strip())
    with open(dates_path, 'r') as f:
        for line in f:
            dates.add(line.strip())
    
    while len(teams_1) > 0 and len (teams_2) > 0 and len(dates) > 0:
        random_date = dates.pop()
        random_team_1 = teams_1.pop()
        random_team_2 = teams_2.pop()
        print (f'{random_team_1} will play with {random_team_2} on {random_date}')


if __name__ == '__main__':
    match(sys.argv[1:3], sys.argv[3])
