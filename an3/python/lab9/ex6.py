import os


def get_total_size(path):
    res = 0
    for _, r, f in os.walk(path):
        for file in f:
            if os.path.exists(os.path.join(path, file)):
                res += os.path.getsize(os.path.join(path, file))
        for directory in r:
            res += get_total_size(os.path.join(path, directory))

    return res


def ex6(dir_path):
    res = dict()
    res['full_path'] = os.path.abspath(dir_path)
    res['total_size'] = get_total_size(dir_path)
    res['files'] = [f for f in os.listdir(dir_path) if os.path.isfile(f)]
    res['dirs'] = [f for f in os.listdir(dir_path) if os.path.isdir(f)]
    return res


print(ex6('/Users/sergiuiacob/work/FII/an3/python/lab9'))
