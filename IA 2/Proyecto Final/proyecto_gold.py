import numpy as np
from sklearn.svm import SVR
import matplotlib.pyplot as plt
import pdb
import Quandl
import math
import pdb
"""Predictor de los precios del oro.
"""

tok = 'uAzFhTzQixa5Mfns-min'

def obtain_gold_value1(mydata):
        """ Obtiene el valor del oro.
           @return y Retorna el valor del oro.
        """
        y = []
        for i in range(len(mydata)-1):
                y.append( mydata[i+1][1] )
        return y

def append_age_feature(mydata):
        """ Funcion que obtiene la data y le agrega el feature de vejez.
            @return X Retorna la data con la vejez agregada.
        """
        X = []
        for i in range(len(mydata)-1):
                tmp = []
                for j in range(1,len(mydata[i])):
                        tmp.append(mydata[i][j])
                tmp.append( i / float(len(mydata)))
                X.append(tmp)
        return X

def delete_nan(X2):
        """Funcion que elimina los NaN de los datos. 
           Vamos a considerar que datos que no se encuentren son los mismos que el dia anterior.
           En un lenguaje mas tecnico esto es 'extrapolar'.
           Por ultimo se le agrega el valor del tiempo como 1.0 para representar que son datos del presente.
           @param mydata2 Data obtenida de Quand
        """
        result = []
        for i in range(len(X2)):
                tmp = []
                for j in range(1, len(X2[i])):
                        tmp.append(X2[i][j] if not math.isnan(X2[i][j]) else 0)
                result.append(tmp)
        return result

def delete_nan_simple(y):
        """ Elimina los nan como la funcion anterior pero 
            con un arreglo unidimensional
            @param y Arreglo unidimensional posiblemente con NaN
            @return result Arreglo unidimensional sin Nan
        """
        result = []
        for i in range(len(y)):
                result.append(y[i] if not math.isnan(y[i]) else 0)
        return result

def normalize(X2):
        """ Funcion que normaliza los datos.
            Los datos vamos a normalizarnos de la siguiente manera:
            dato[i][j] / abs(dato[i][j])
        """
        result = []
        for i in range(len(X2)):
                tmp = []
                for j in range(1, len(X2[i])):
                        tmp.append(X2[i][j] / (abs(X2[i][j])) if X2[i][j] != 0 else 0)
                result.append(tmp)
        return result

def simple_normalize(y):
        result = []
        for i in range(len(y)):
                result.append( y[i] / abs(y[i]) if y[i] != 0 else y[i] )
        return result


''' DATOS DE ENTRENAMIENTO '''

datos_deseados = ["BUNDESBANK/BBK01_WT5511","LBMA/SILVER.1", "JOHNMATT/PLAT.3", "CURRFX/USDAUD.1", "CURRFX/USDCNY.1"]

print "Descargando Datos..."

mydata = Quandl.get(datos_deseados, trim_start="2013-01-01", trim_end="2014-6-30",returns="numpy",transformation="diff" , authtoken=tok)

''' DATOS DE PRUEBA '''

mydata2 = Quandl.get(datos_deseados, trim_start="2014-7-01", trim_end="2014-11-25",returns="numpy",transformation="diff" , authtoken=tok)

print "Realizando calculos..."

X= append_age_feature(mydata)
X = delete_nan(X)
y = obtain_gold_value1(mydata)
X = normalize(X)
y = simple_normalize(y)




X2 = append_age_feature(mydata2)
X2 = delete_nan(X2)
y2 = obtain_gold_value1(mydata2)
y2 = delete_nan_simple(y2)

X2 = normalize(X2)
y2 = simple_normalize(y2)

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
