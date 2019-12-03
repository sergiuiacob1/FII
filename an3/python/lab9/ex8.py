import os


def ex8(path, tree_depth, filesize, filecount, dircount):
    if tree_depth <= 0:
        return

    if os.path.exists(path) is False:
        os.makedirs(path)

    for i in range(0, dircount):
        ex8(os.path.join(path, f'dir{i}'), tree_depth -
            1, filesize, filecount, dircount - 1)
    for i in range(0, filecount):
        with open(os.path.join(path, f'file{i}'), 'w') as f:
            f.seek(filesize - 1)
            f.write('\0')


ex8('/Users/sergiuiacob/work/FII/an3/python/lab9/test', 2, 1024, 3, 3)
