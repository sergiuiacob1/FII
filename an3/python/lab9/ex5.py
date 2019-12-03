import os

def ex5(source, directory, buffer_size):
    file_name = os.path.basename(source)
    with open (os.path.join(directory, file_name), 'w') as fw:
        with open (source, 'r') as fr:
            while True:
                next = fr.read(buffer_size)
                if not next:
                    break
                fw.write(next)

ex5('/Users/sergiuiacob/work/FII/an3/python/lab9/test.txt', '/Users/sergiuiacob/work/FII/an3/python/lab9/delete_me', 1)