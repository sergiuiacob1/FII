import hashlib
import datetime
import os
import time


def ex9(path):
    data = {}
    add_data(os.path.abspath(path), data)
    return data


def add_data(path, data):
    for dir_path, dirs, files in os.walk(path):
        for d in dirs:
            add_data(os.path.join(dir_path, d), data)
        for f in files:
            f_path = os.path.join(dir_path, f)
            info = []
            sha256 = hashlib.sha256()
            sha256.update(open(f_path, 'rb').read())
            md5 = hashlib.md5()
            md5.update(open(f_path, 'rb').read())
            timestamp_str = datetime.datetime.fromtimestamp(
                os.stat(f_path).st_ctime).strftime('%Y-%m-%d-%H:%M')
            info.extend([md5.hexdigest(), sha256.hexdigest()])
            info.extend([os.stat(f_path).st_size, timestamp_str])
            data[f] = info


print(ex9('.'))
