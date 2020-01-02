import sys
from sklearn.preprocessing import StandardScaler
from sklearn.multiclass import OneVsRestClassifier
from sklearn.cluster import KMeans
from sklearn import svm

datasetpath = '/usr/local/src/datasets/dataset.txt'
train_split = 0.7

exportPath = sys.argv[sys.argv.index('-e') + 1] if '-e' in sys.argv else None

#Read dataset
data = {}
with open(datasetpath, 'r') as f:
	f.readline()
	for line in f:
		features = line[:-1].split(',')
		cls,ft = int(features[0]), [float(x) for x in features[1:]]
		if cls not in data: data[cls] = [ft]
		else: data[cls].append(ft)

#Split dataset
X_train, y_train, X_test, y_test = [], [], [], []
for cls,d in data.items():
	max_train_index = len(d) * train_split
	for i,f in enumerate(d):
		if i < max_train_index:
			X_train.append(f)
			y_train.append(cls)
		else:
			X_test.append(f)
			y_test.append(cls)

#Train & test
km = KMeans(n_clusters = 6)
km.fit(X_train)
pred = km.predict(X_test)

#Cluster assigment
ca = {}
trainpred = km.predict(X_train)
for i,p in enumerate(trainpred):
	if p not in ca: ca[p] = [y_train[i]]
	else : ca[p].append(y_train[i])
for p in ca: ca[p] = max(set(ca[p]), key=ca[p].count)

for i,p in enumerate(pred): print('pred : {} -- cls : {}'.format(ca[p], y_test[i]))
if exportPath is not None:
	with open(exportPath, 'w') as outf:
		for i,p in enumerate(pred):
			outf.write('{},{}\n'.format(y_test[i], ca[p]))
