from sklearn import cluster, metrics
from gensim.models.word2vec import Word2Vec
from gensim.summarization.textcleaner import get_sentences, split_sentences
import pandas as pd
import nltk
from nltk.cluster import KMeansClusterer
from sklearn.manifold import TSNE
import matplotlib.pyplot as plt


print('Done importing libraries')


def tsne_plot(model):
    "Creates and TSNE model and plots it"
    labels = []
    tokens = []

    for word in model.wv.vocab:
        tokens.append(model.wv[word])
        labels.append(word)

    tsne_model = TSNE(perplexity=40, n_components=2,
                      init='pca', n_iter=250, random_state=23, verbose=True)
    print('Starting TNSE')
    new_values = tsne_model.fit_transform(tokens)
    print('TNSE done')

    x = []
    y = []
    for value in new_values:
        x.append(value[0])
        y.append(value[1])

    plt.figure(figsize=(16, 16))
    for i in range(len(x)):
        plt.scatter(x[i], y[i])
        plt.annotate(labels[i],
                     xy=(x[i], y[i]),
                     xytext=(5, 2),
                     textcoords='offset points',
                     ha='right',
                     va='bottom')
    plt.show()


def part1():
    # Read data
    file_path = "~/Downloads/dataset.csv"
    data = pd.read_csv(file_path, encoding="ISO-8859-1")

    # Getting sentences
    # print ('Processing text')
    # tok_corp = [nltk.word_tokenize(x) for x in data["SentimentText"].values.tolist()]

    # print ('Training model')
    # model = Word2Vec(sentences=tok_corp, workers=4)
    # model.save("model.pkl")

    print('Loading model')
    model = Word2Vec.load("model.pkl")

    words = ["awesome", "doubt", "marvelous", "brilliant", "model",
             "thrilling", "fabulous", "super", "superb", "outstanding"]
    print(model.wv.most_similar(positive=words))
    tsne_plot(model)
    print('Plot shown')


def part2():
    print('Loading model')
    model = Word2Vec.load("model.pkl")
    X = model.wv.vectors[:2000]
    no_clusters = 5
    kclusterer = KMeansClusterer(
        no_clusters, distance=nltk.cluster.util.cosine_distance, repeats=5)
    assigned_clusters = kclusterer.cluster(X, assign_clusters=True)

    words = list(model.wv.vocab)[:2000]
    filtered = [list()] * no_clusters
    for index, word in enumerate(words):
        filtered[assigned_clusters[index]].append(word)

    print (filtered[0][:10])
    # for i in range(0, no_clusters):
        # print(filtered[i])


part2()
