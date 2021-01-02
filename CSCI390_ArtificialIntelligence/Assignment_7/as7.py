import numpy as np
import math
#Input: the lists of prior probabilities, likelihood, and test data
#Output: list of corresponding posterior probabilities
#
def posteriorFunc(priorProb, likhd, data):
	posProb = []
	sum = 0
	a = 0
	b= 0
	for z in data:
		if z == 1:
			a = a + 1
		if z == 0:
			b = b + 1
	for x, y in zip(priorProb, likhd):
		sum = sum + x*(y**a)*((1-y)**b)
	sum = 1/sum
	for x, y in zip(priorProb, likhd):
		posProb.append(sum*x*((y**a)*((1-y)**b)))
	return posProb
#Input the lists of prior probabilites, likhd/likelihood, training data, and one test datapoint
#Output: probability that the test datapoint happens
#Note: this function will call posteriorFunc to calculate the posterior probabilites 
def predictionFunc (priorProb, likhd, data, fPoint):
	posProb = posteriorFunc(priorProb, likhd, data)
	predictProb = 0
	for x, y in zip(posProb, likhd):
		predictProb = predictProb + x * y
	if fPoint == 0:
		predictProb = 1- predictProb
	return predictProb