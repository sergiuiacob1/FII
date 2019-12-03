import os


def search_by_content(target, to_search):
    target_path = os.path.abspath(target)
    if os.path.exists(target_path) is False:
        return []

    files = []
    search_recursively(files, target_path, to_search)
    return files


def search_recursively(files, path, to_search):
    for _, d, f in os.walk(path):
        for file in f:
            if file.startswith('.'):
                continue
            if file_contains_to_search(os.path.join(path, file), to_search):
                files.append(os.path.join(path, file))

        for directory in d:
            search_recursively(files, os.path.join(path, directory), to_search)


def file_contains_to_search(file, to_search):
    try:
        content =open(file, 'r').read()
    except:
        print (f'Could not read {file}')
        return False
    return (to_search in content)

if __name__ == '__main__':
    print(search_by_content('/Users/sergiuiacob/work/FII/an3/python', 'prime'))