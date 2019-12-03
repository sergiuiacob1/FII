import os


def get_file_info(file_path):
    res = {}
    res['full_path'] = os.path.abspath(file_path)
    res['file_size'] = os.stat(file_path).st_size
    res['file_extension'] = file_path.split('.')[-1]
    res['can_read'] = os.access(file_path, os.R_OK)
    res['can_write'] = os.access(file_path, os.W_OK)
    return res


if __name__ == '__main__':
    print(get_file_info('test.txt'))
