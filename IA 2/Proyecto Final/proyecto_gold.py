
import numpy as np
from sklearn.svm import SVR
import matplotlib.pyplot as plt
import pdb
import Quandl
import math

###############################################################################

tok = 'uAzFhTzQixa5Mfns-min'

''' DATOS DE ENTRENAMIENTO '''

mydata = Quandl.get(["BUNDESBANK/BBK01_WT5511","LBMA/SILVER.1"], trim_start="2013-01-01", trim_end="2014-6-30",returns="numpy",transformation="diff" , authtoken=tok)
X = []
y = []
for i in range(len(mydata)-1):
	X.append( [ mydata[i][1] , mydata[i][2] , i/float(len(mydata)) ] )
	y.append( mydata[i+1][1] )

''' DATOS DE PRUEBA '''

mydata2 = Quandl.get(["BUNDESBANK/BBK01_WT5511","LBMA/SILVER.1"], trim_start="2014-7-01", trim_end="2014-11-25",returns="numpy",transformation="diff" , authtoken=tok)
X2 = []
y2 = []

for i in range(len(mydata2)-1):
	X2.append( [ mydata2[i][1] if not math.isnan(mydata2[i][1]) else 0  , mydata2[i][2] if not math.isnan(mydata2[i][2]) else 0 , 1.0 ] )
	y2.append( mydata2[i+1][1] if not math.isnan(mydata2[i+1][1]) else 0 )

# Generate sample data
#X = np.sort(5 * np.random.rand(40, 1), axis=0)
#y = np.sin(X).ravel()

###############################################################################
# Fit regression model
svr_rbf = SVR(kernel='rbf', C=1e1, gamma=1.0)

malos = 0
buenos = 0
i = 0
for datos in X2:

	y_rbf = svr_rbf.fit(X + X2[0:i] , y + y2[0:i] )
	pred = y_rbf.predict([ datos ])
	print "%s -> %s  |  %s" % (i,pred[0],y2[i])

	if (pred[0] < 0 and y2[i] < 0) or (pred[0] > 0 and y2[i] > 0):
		buenos+=1
	else:
		malos+=1

	i+=1

print "Buenos: %s | Malos: %s | Porc: %s" % ( buenos , malos , buenos/float(buenos+malos) )