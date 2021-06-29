import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import load_files
import zipfile
import glob
import os
import shutil
import sys
from sklearn.model_selection import train_test_split
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.naive_bayes import MultinomialNB
from sklearn.metrics import classification_report, accuracy_score
from sklearn.svm import SVC
from sklearn.neighbors import KNeighborsClassifier
import pickle
import pickle


def main(argv):

    str = argv[1]
    size = len(str)
    sub = str[size-3:size]
    path_trailer = str[0:size-3]

    vectorizer_filename = 'vectorizer.pkl'
    vectorizer = pickle.load(open(vectorizer_filename,'rb'))

    pkl_filename = argv[0]
    pickle_model = pickle.load(open(pkl_filename, 'rb'))
        
    new_path = ""
    p1h1 = ""
    if sub == "zip":
        with zipfile.ZipFile(argv[1], "r") as zip_ref:
            zip_ref.extractall("./" + path_trailer)

        p1h1 = path_trailer

    else :
        p1h1 = str

    new_path = p1h1 + "/" + p1h1
    paths = glob.glob(new_path + "/*.txt")
    
    sorted_path = [''] * len(paths)

    for i in range(len(paths)):

        istart = paths[i].find('\\')
        iend = paths[i].find('_')

        index = int(paths[i][istart+1:iend])
        sorted_path[index - 1] = paths[i]

    abc = []

    oku = ''

    for i in range(len(sorted_path)): 
        f = open(sorted_path[i],encoding='utf8', errors='ignore')
        text = f.read()
        abc.append(text)

    data = load_files(new_path, encoding="utf-8", decode_error="replace")

    new_y_train = []
    for i in range(len(sorted_path)):
        if sorted_path[i][-5] == 'P':
            new_y_train.append(1)
        elif sorted_path[i][-5] == 'N':
            new_y_train.append(0)
        elif sorted_path[i][-5] == 'Z':
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

    myReel =  []

    for i in range(len(new_y_train)):
        if new_y_train[i] == 0:
            myReel.append('N')
        if new_y_train[i] == 1:
            myReel.append('P')
        if new_y_train[i] == 2:
            myReel.append('Z')
        
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
    print(accuracy_score_of_MNB)
    print(acc_macro)


if __name__ == "__main__":
   main(sys.argv[1:])