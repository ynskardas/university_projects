import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import load_files
import zipfile
import glob
import os
import shutil
import sys

def main(argv):
    with zipfile.ZipFile("TRAIN.zip", "r") as zip_ref:
        zip_ref.extractall("./datadir")

    paths = glob.glob("datadir/TRAIN/*.txt")
    pList = list(filter(lambda path: path[-5] == 'P', paths))
    nList = list(filter(lambda path: path[-5] == 'N', paths))
    zList = list(filter(lambda path: path[-5] == 'Z', paths))

    path = './datadir/TRAIN'

    os.mkdir(path+'/P')
    os.mkdir(path+'/Z')
    os.mkdir(path+'/N')

    for f in pList:
        shutil.move(f, path+'/P')
    for f in nList:
        shutil.move(f, path+'/N')
    for f in zList:
        shutil.move(f, path+'/Z')


    DATA_DIR = "./datadir/TRAIN/"

    data = load_files(path, encoding="utf-8", decode_error="replace")

    labels, counts = np.unique(data.target, return_counts=True)

    labels_str = np.array(data.target_names)[labels]

    from sklearn.model_selection import train_test_split
    X_train, X_test, y_train, y_test = train_test_split(data.data, data.target)

    from sklearn.feature_extraction.text import TfidfVectorizer
    vectorizer = TfidfVectorizer(stop_words="english", max_features=1000, decode_error="ignore")

    vectorizer.fit(X_train)

    from sklearn.naive_bayes import MultinomialNB
    cls1 = MultinomialNB()
    cls1.fit(vectorizer.transform(X_train), y_train)

    from sklearn.metrics import classification_report, accuracy_score

    y_pred = cls1.predict(vectorizer.transform(X_test))
    accuracy_score_of_MNB = accuracy_score(y_test, y_pred)


    from sklearn.svm import SVC

    cls2 = SVC(C=1.0, kernel='linear', degree=3, gamma='auto')
    cls2.fit(vectorizer.transform(X_train), y_train)
    y_pred = cls2.predict(vectorizer.transform(X_test))
    accuracy_score_of_SVM = accuracy_score(y_test, y_pred)


    from sklearn.neighbors import KNeighborsClassifier

    cls3 = KNeighborsClassifier(n_neighbors=7, algorithm='auto')

    cls3.fit(vectorizer.transform(X_train), y_train)

    y_pred = cls3.predict(vectorizer.transform(X_test))
    accuracy_score_of_KNN = accuracy_score(y_test, y_pred)

    maxRatio = max(accuracy_score_of_MNB, max(accuracy_score_of_SVM, accuracy_score_of_KNN))
    if maxRatio == accuracy_score_of_MNB:
        cls = cls1

    elif maxRatio == accuracy_score_of_SVM:
        cls = cls2
    else:
        cls = cls3

    import pickle
    pkl_filename = "step2_model_PudraSekerim.pkl"
    with open(pkl_filename, 'wb') as file:
        pickle.dump(cls, file)

    import pickle

    pkl_filename = argv[0]

    with open(pkl_filename, 'rb') as file:
        pickle_model = pickle.load(file)

    with zipfile.ZipFile(argv[1], "r") as zip_ref:
        zip_ref.extractall("./VAL")

    paths = glob.glob("VAL/VAL/*.txt")
    pList = list(filter(lambda path: path[-5] == 'P', paths))
    nList = list(filter(lambda path: path[-5] == 'N', paths))
    zList = list(filter(lambda path: path[-5] == 'Z', paths))

    abc = []

    for i in range(len(paths)):
        f = open(paths[i],encoding='utf8', errors='ignore')
        text = f.read()
        abc.append(text)

    path = './datadir/VAL'
    os.mkdir(path)

    os.mkdir(path+'/P')
    os.mkdir(path+'/Z')
    os.mkdir(path+'/N')

    for f in pList:
        shutil.move(f, path+'/P')
    for f in nList:
        shutil.move(f, path+'/N')
    for f in zList:
        shutil.move(f, path+'/Z')


    data = load_files(path, encoding="utf-8", decode_error="replace")

    new_y_train = []
    for i in range(len(paths)):
        if paths[i][-5] == 'P':
            new_y_train.append(1)
        elif paths[i][-5] == 'N':
            new_y_train.append(0)
        elif paths[i][-5] == 'Z':
            new_y_train.append(2)

    arr = np.array(new_y_train)

    y_pred = pickle_model.predict(vectorizer.transform(abc))
    accuracy_score_of_MNB = accuracy_score(arr, y_pred)


    count_p_tn = 0
    count_p_fn = 0
    count_p_tp = 0
    count_p_fp = 0

    count_n_tn = 0
    count_n_fn = 0
    count_n_tp = 0
    count_n_fp = 0

    count_z_tn = 0
    count_z_fn = 0
    count_z_tp = 0
    count_z_fp = 0

    data_size = len(abc)
    output = ""

    for i in range(data_size):
        if y_pred[i] == 0:
            if arr[i]==0:
                count_n_tp+=1
                count_p_tn+=1
                count_z_tn+=1
            elif arr[i]==1:
                count_n_fp+=1
                count_p_fn+=1
                count_z_tn+=1
            elif arr[i]==2:
                count_n_fp+=1
                count_p_tn+=1
                count_z_fn+=1
            output += "N"
        elif y_pred[i] == 1:
            if arr[i]==0:
                count_n_fn+=1
                count_p_fp+=1
                count_z_tn+=1
            elif arr[i]==1:
                count_n_tn+=1
                count_p_tp+=1
                count_z_tn+=1
            elif arr[i]==2:
                count_n_tn+=1
                count_p_fp+=1
                count_z_fn+=1
            output += "P"
        elif y_pred[i] == 2:
            if arr[i]==0:
                count_n_fn+=1
                count_p_tn+=1
                count_z_fp+=1
            elif arr[i]==1:
                count_n_tn+=1
                count_p_fn+=1
                count_z_fp+=1
            elif arr[i]==2:
                count_n_tn+=1
                count_p_tn+=1
                count_z_tp+=1
            output += "Z"

    accuracy_n = (count_n_tp+count_n_tn)/(count_n_fn+count_n_tn+count_n_tp+count_n_fp)
    accuracy_p = (count_p_tp+count_p_tn)/(count_p_fn+count_p_tn+count_p_tp+count_p_fp)
    accuracy_z = (count_z_tp+count_z_tn)/(count_z_fn+count_z_tn+count_z_tp+count_z_fp)

    precision_n = count_n_tp / (count_n_tp + count_n_fp)
    precision_z = count_z_tp / (count_z_tp + count_z_fp)
    precision_p = count_p_tp / (count_p_tp + count_p_fp)

    racall_n = count_n_tp / (count_n_tp+count_n_fn)
    racall_z = count_z_tp / (count_n_tp+count_z_fn)
    racall_p = count_p_tp / (count_p_tp+count_p_fn)

    acc_macro = (accuracy_n+accuracy_p+accuracy_z) / 3
    acc_precision =(precision_n+precision_p+precision_z) / 3
    acc_racall = (racall_n+racall_p+racall_z) / 3

    print(output)


if __name__ == "__main__":
   main(sys.argv[1:])