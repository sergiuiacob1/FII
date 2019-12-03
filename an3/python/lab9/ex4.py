import os


def ex4(dir_path):
    files = os.listdir(dir_path)

    print(f'DIR: {dir_path}')

    for item in files:
        path = os.path.join(dir_path, item)
        if os.path.isdir(path):
            ex4(path)
        elif os.path.isfile(path):
            print(f'FILE: {path}')
        else:
            print(f'UNKOWN: {path}')


ex4('/Users/sergiuiacob/work/FII/an3/python')
