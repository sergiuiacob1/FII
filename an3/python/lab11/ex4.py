import os
import re


def ex4(xml_path, d):
    res = []
    xml_content = open(os.path.join(os.getcwd(), xml_path), 'r').read()
    r = r'<\s*\w+\s+'
    for key in d:
        r += key + r'\s+=\s+"' + d[key] + r'.+'
    r += r'>.+</.+>'
    r = re.compile(r)
    for line in xml_content.split('\n'):
        if r.match(line):
            res.append(line)
    return res


d = {
    "class": "url",
    "name": "url",
    "date-id": "item"
}
print(ex4('xml_file.xml', d))
