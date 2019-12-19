import os
import sys
import hashlib
import time
import re

sync_interval = 10


def sync_file_to_second_path(dir1_original_path, relative_file_path, dir2_original_path):
    ...

def sync_first_to_second(first_path, second_path, r):
    for current_path, files, dirs in os.walk(first_path):
        for file_name in files:
            if r.match(file_name) is False:
                continue
            sync_file_to_second_path('...')


def sync_dirs(dir1_path, dir2_path, r):
    sync_first_to_second(dir1_path, dir2_path, r)
    sync_first_to_second(dir2_path, dir1_path, r)


if __name__ == '__main__':
    dir1_path, dir2_path = sys.argv[1], sys.argv[2]
    r = re.compile(sys.argv[3])
    while True:
        sync_dirs(dir1_path, dir2_path, r)
