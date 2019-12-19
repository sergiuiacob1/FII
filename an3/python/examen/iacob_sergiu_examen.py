# working version:
import os
import sys
import time
import re
import hashlib
import threading

sync_interval = 10


def sync_file(dir1_path, relative_file_path, dir2_path):
    print(
        f'Checking if {relative_file_path} from {dir1_path} exists in {dir2_path}')
    if os.path.exists(os.path.join(dir2_path, relative_file_path)):
        f_dir1 = open(os.path.join(dir1_path, relative_file_path), 'rb')
        f_dir2 = open(os.path.join(dir2_path, relative_file_path), 'rb')
        # get the binary data, only read once
        value_in_dir1 = f_dir1.read()
        value_in_dir2 = f_dir2.read()
        # close them for now
        f_dir1.close()
        f_dir2.close()
        # it exists; are the files the same?
        md5_dir1, md5_dir2 = hashlib.md5(), hashlib.md5()
        md5_dir1.update(value_in_dir1)
        md5_dir2.update(value_in_dir2)
        print(md5_dir1.hexdigest() == md5_dir2.hexdigest())
        if md5_dir1.hexdigest() != md5_dir2.hexdigest():
            # the contents are not the same, update the file in the other directory
            f_dir2 = open(os.path.join(dir2_path, relative_file_path), 'wb')
            f_dir2.write(value_in_dir1)
            f_dir2.close()
    else:
        print(f'File does not exist in {dir2_path}')
        # the file doesn't exist in dir2
        f_dir2 = open(os.path.join(dir2_path, relative_file_path), 'wb')
        with open(os.path.join(dir1_path, relative_file_path), 'rb') as f_dir1:
            f_dir2.write(f_dir1.read())
            # f_dir1 automatically closed (context manager)
        f_dir2.close()


def sync_single_dir(first_path, second_path, r):
    threads = []
    for path, dirs, files in os.walk(first_path):
        for file_name in files:
            if r.match(file_name) is False:
                continue
            # else, I should sync this
            # could use threads
            t = threading.Thread(target=sync_file, args=(
                path, file_name, second_path))
            t.start()
            threads.append(t)
            # synchronous version
            # sync_file(first_path, relative_file_path, second_path)
        for d in dirs:
            sync_dirs(os.path.join(first_path, path, d),
                      os.path.join(second_path, path, d), r)
    # wait for the dir1 to dir2 sync syncing dir2 to dir1
    for t in threads:
        t.join()


def sync_dirs(dir1_path, dir2_path, r):
    sync_single_dir(dir1_path, dir2_path, r)
    sync_single_dir(dir2_path, dir1_path, r)


if __name__ == '__main__':
    path1, path2 = sys.argv[1], sys.argv[2]
    # global orig_path1, orig_path2
    # orig_path1, orig_path2 = path1, path2
    r = sys.argv[3]
    # compile the regex here, only once
    r = re.compile(r)
    # path1 = os.path.abspath(os.path.join(os.getcwd(), path1))
    # path2 = os.path.abspath(os.path.join(os.getcwd(), path2))
    while True:
        sync_dirs(path1, path2, r)
        # sync every sync_interval seconds
        time.sleep(sync_interval)



# # better version, dar nu mai stiu cum creai un fisier care nu exista
# import os
# import sys
# import time
# import re
# import hashlib
# import threading

# sync_interval = 10


# def sync_file(dir1_path, relative_file_path, dir2_path):
#     print(
#         f'Checking if {relative_file_path} from {dir1_path} exists in {dir2_path}')
#     if os.path.exists(os.path.join(dir2_path, relative_file_path)):
#         f_dir1 = open(os.path.join(dir1_path, relative_file_path), 'rb')
#         f_dir2 = open(os.path.join(dir2_path, relative_file_path), 'rb')
#         # get the binary data, only read once
#         value_in_dir1 = f_dir1.read()
#         value_in_dir2 = f_dir2.read()
#         # close them for now
#         f_dir1.close()
#         f_dir2.close()
#         # it exists; are the files the same?
#         md5_dir1, md5_dir2 = hashlib.md5(), hashlib.md5()
#         md5_dir1.update(value_in_dir1)
#         md5_dir2.update(value_in_dir2)
#         print(md5_dir1.hexdigest() == md5_dir2.hexdigest())
#         if md5_dir1.hexdigest() != md5_dir2.hexdigest():
#             # the contents are not the same, update the file in the other directory
#             f_dir2 = open(os.path.join(dir2_path, relative_file_path), 'wb')
#             f_dir2.write(value_in_dir1)
#             f_dir2.close()
#     else:
#         print(f'File does not exist in {dir2_path}')
#         # the file doesn't exist in dir2
#         f_dir2 = open(os.path.join(dir2_path, relative_file_path), 'wb')
#         with open(os.path.join(dir1_path, relative_file_path), 'rb') as f_dir1:
#             f_dir2.write(f_dir1.read())
#             # f_dir1 automatically closed (context manager)
#         f_dir2.close()


# def sync_single_dir(first_path, second_path, r, orig_path1, orig_path2):
#     threads = []
#     for path, dirs, files in os.walk(first_path):
#         for file_name in files:
#             if r.match(file_name) is False:
#                 continue
#             # else, I should sync this
#             # could use threads
#             relative_file_path = path.replace(orig_path1, '')
#             if relative_file_path.startswith('/'):
#                 relative_file_path = relative_file_path[1:]
#             relative_file_path = os.path.join(relative_file_path, file_name)
#             t = threading.Thread(target=sync_file, args=(
#                 orig_path1, relative_file_path, orig_path2))
#             t.start()
#             threads.append(t)
#             # synchronous version
#             # sync_file(first_path, relative_file_path, second_path)
#         for d in dirs:
#             sync_dirs(os.path.join(first_path, path, d),
#                       os.path.join(second_path, path, d), r, orig_path1, orig_path2)
#     # wait for the dir1 to dir2 sync syncing dir2 to dir1
#     for t in threads:
#         t.join()


# def sync_dirs(dir1_path, dir2_path, r, orig_path1, orig_path2):
#     sync_single_dir(dir1_path, dir2_path, r, orig_path1, orig_path2)
#     sync_single_dir(dir2_path, dir1_path, r, orig_path2, orig_path1)


# if __name__ == '__main__':
#     path1, path2 = sys.argv[1], sys.argv[2]
#     global orig_path1, orig_path2
#     orig_path1, orig_path2 = path1, path2
#     r = sys.argv[3]
#     # compile the regex here, only once
#     r = re.compile(r)
#     # path1 = os.path.abspath(os.path.join(os.getcwd(), path1))
#     # path2 = os.path.abspath(os.path.join(os.getcwd(), path2))
#     while True:
#         sync_dirs(path1, path2, r, orig_path1, orig_path2)
#         # sync every sync_interval seconds
#         time.sleep(sync_interval)
