from sklearn import cluster, metrics
from gensim.models.word2vec import Word2Vec
from gensim.summarization.textcleaner import get_sentences, split_sentences
import pandas as pd
import nltk
from nltk.cluster import KMeansClusterer
from sklearn.manifold import TSNE
import matplotlib.pyplot as plt
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import accuracy_score

print('Done importing libraries')


def tsne_plot(model):
    "Creates and TSNE model and plots it"
    labels = []
    tokens = []

    for word in model.wv.vocab:
        tokens.append(model.wv[word])
        labels.append(word)

    tsne_model = TSNE(perplexity=5, n_components=2,
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


def get_data():
    file_path = "~/Downloads/dataset.csv"
    data = pd.read_csv(file_path, encoding="ISO-8859-1")
    return data


def part1():
    # Read data
    data = get_data()

    # Getting sentences
    # print ('Processing text')
    # tok_corp = [nltk.word_tokenize(x) for x in data["SentimentText"].values.tolist()]

    # print ('Training model')
    # model = Word2Vec(sentences=tok_corp, workers=4)
    # model.save("model.pkl")

    print('Loading model')
    model = Word2Vec.load("model.pkl")

    words = ["awesome", "dog", "building", "movie", "red",
             "device", "sky", "plant", "dark", "operate"]
    for w in words:
        print(model.wv.most_similar(positive=[w])[0])
    # words = ["awesome", "doubt", "marvelous", "brilliant", "model",
    #          "thrilling", "fabulous", "super", "superb", "outstanding"]
    # print(model.wv.most_similar(positive=words))

    # tsne_plot(model)
    # print('Plot shown')


def extract_features(df):
    cv = CountVectorizer(binary=True)
    cv.fit_transform(df["SentimentText"].values)
    train_feature_set = cv.transform(df["SentimentText"].values)
    return train_feature_set, cv


def part2():
    # GET FEATURES
    data = get_data()
    print ('Extracting features...')
    X, cv = extract_features(data)
    y = data["Sentiment"].values

    print ('Training model...')
    model = LogisticRegression()
    model.fit(X, y)

    print(f"Training data accuracy: {accuracy_score(y, model.predict(X))}")

    # data = get_data()
    # X = data["SentimentText"].values
    # y = data["Sentiment"].values
    # cv = CountVectorizer(binary=True)
    # cv.fit(X)
    # X = cv.transform(X)
    # X_test = cv.transform(y)

    # y = [1 if i < 12500 else 0 for i in range(25000)]

    # final_model = LogisticRegression(C=0.05)
    # final_model.fit(X, y)

    # print("Training data accuracy: %s" %
    #       accuracy_score(y, final_model.predict(X)))

    # print('Loading model')
    # model = Word2Vec.load("model.pkl")
    # no = 6000
    # X = model.wv.vectors[:no]
    # no_clusters = 5
    # kclusterer = KMeansClusterer(
    #     no_clusters, distance=nltk.cluster.util.cosine_distance, repeats=5)
    # print('Clustering...')
    # assigned_clusters = kclusterer.cluster(X, assign_clusters=True)

    # words = list(model.wv.vocab)[:no]
    # filtered = [list()] * no_clusters
    # for index, word in enumerate(words):
    #     filtered[assigned_clusters[index]].append(word)

    # print(filtered[1][:10])


# part1()
part2()
