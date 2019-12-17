import math
import itertools
import sys
from nltk import tokenize
if True:
    print('Loading Wordnet...')
    from nltk.corpus import wordnet as wn
    print('Wordnet Loaded!')


def get_first_hypernym(word):
    syns = wn.synsets(word, pos=wn.NOUN)
    if len(syns) == 0:
        return None
    if len(syns[0].hypernyms()) == 0:
        return syns[0].lemmas()[0].name()
    return syns[0].hypernyms()[0].lemmas()[0].name()


def calculate_distances(text):
    sentences = tokenize.sent_tokenize(text)
    distances = []
    for sentence in sentences:
        words = sentence.split()
        max_distance = -1
        for word1, word2 in itertools.combinations(words, 2):
            if word1 == word2:
                continue
            try:
                first = wn.synsets(word1)[0]
                second = wn.synsets(word2)[0]
                distance = first.shortest_path_distance(second)
                max_distance = max(max_distance, distance)
            except:
                pass
        print(f'Distance found: {max_distance}')
        distances.append(max_distance)

    result = ''
    for x, y in zip(sentences, distances):
        result += x
        result += ' (' + str(y) + ') '
    return result


def replace_nouns_with_hypernyms(text):
    result = ''
    for word in text.split():
        hypernym = get_first_hypernym(word)
        if hypernym is not None:
            print(f'Replaced {word} with {hypernym}')
            result += ' ' + hypernym
        else:
            result += ' ' + word
    return result.strip()


if __name__ == '__main__':
    file_path = sys.argv[1]
    text = open(file_path, 'rt').read()
    result = replace_nouns_with_hypernyms(text)
    open(file_path, 'wt').write(result)
    distances_result = calculate_distances(text)
    open('distances.txt', 'wt').write(distances_result)
