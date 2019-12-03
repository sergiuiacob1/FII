import os
import sys


def ex7(container_path, ext):
    container_dir = os.path.dirname(container_path)
    archive = open(container_path, 'rb')
    # origin = archive.copy()
    archive.seek(len('CONTAINER'))
    no_of_files = int.from_bytes(
        bytes=archive.read(1), byteorder=sys.byteorder)
    for _ in range(0, no_of_files):
        file_size = int.from_bytes(bytes=archive.read(4), byteorder='little')
        file_name = archive.read(50).decode(encoding="utf-8").strip()
        if file_name.endswith(ext):
            print(
                f'Extracting {file_name} to {os.path.join(container_dir, file_name)}')
            with open(os.path.join(container_dir, file_name), 'wb') as f:
                f.write(archive.read(file_size))
        else:
            archive.seek(file_size, 1)

    archive.close()


ex7('/Users/sergiuiacob/work/FII/an3/python/lab9/container.dms', 'abc')
