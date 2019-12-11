from owlready2 import get_ontology
import sys


def load_ontology():
    onto = get_ontology("./CSO.3.1.owl")
    print('Loading ontology...')
    onto.load()
    print('Ontology loaded!')
    return onto


def find_class(onto, class_name):
    classes = list(onto.classes())
    for onto_class in classes:
        if str(onto_class).endswith(class_name):
            return onto_class
    return None


if __name__ == '__main__':
    if len(sys.argv) < 2:
        raise Exception('No class argument found!')
    onto = load_ontology()
    x = find_class(onto, sys.argv[1])
    if x is not None:
        print(f'Found that class in the ontology: {x}')
    else:
        print('Did not find that class in the ontology')
