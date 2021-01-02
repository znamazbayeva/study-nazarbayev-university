import numpy as np
import math
import random

in_dim = 785 # input dimension
out_dim = 10 # number of classes (0-9)
eta = 1 # Learning rate. You might try different rates (between 0.001 and 1) to maximize the accuracy

def Weight_update(feature, label, weight_i2o):
	weight1= weight_i2o
	predicted = get_predictions(np.transpose(weight1), feature)
	weight2 = np.zeros(np.shape(weight_i2o))
	# feature = np.reshape(feature, (785))
	lind = int(label)

	lala = -1
	for ins in range(10):  
		lala = np.dot(weight_i2o[:, ins], feature)
		if lala > lind:
			lala= lind
	# feature = np.reshape(feature, (785, 1))
	# predicted = get_predictions(np.transpose(weight_i2o), feature)
	# weight_temp = np.zeros(np.shape(weight_i2o))
	# # fe = np.reshape(feature, (785))
	# maxind = 0
	# cu = -1
	# la = int(label)
	# l = -1
	# for ind in range(10):  
	# 	l = np.dot(weight_i2o[:, ind], feature)
	# 	if l > curm:
	# 		curm = l
	# 		maxind = ind



	# d = weight_i2o[lala] - weight_i2o[lind]

	# d = np.reshape(d, (1,10))
	# weight1[:] = 1*feature

	weight_temp = np.zeros(np.shape(weight_i2o))
	y = int(label)
	weight_temp[:,y] = 1*feature
	# l = get_predictions(feature, weight_i2o)
	d = np.argmax(np.dot(feature, weight_i2o))
	weight_temp1 = np.zeros(np.shape(weight_i2o))
	weight_temp1[:,d] = 1*feature
	difference = np.subtract(weight_temp,weight_temp1)
	return weight_i2o + difference


def get_predictions(dataset, weight_i2o):
	predictions = []
	for i in range(len(dataset)):
		predictions.append(np.argmax(np.dot(dataset[i], weight_i2o)))
	return np.array(predictions)
	# predictions = np.dot(dataset, weight_i2o)
	# return np.argmax(predictions, axis =1)

def train(train_set, labels, weight_i2o):
    for i in range(0, train_set.shape[0]):        
        weight_i2o = Weight_update(train_set[i, :], labels[i], weight_i2o)        
    return weight_i2o