import numpy as np
import matplotlib.pyplot as plt
from sklearn import svm, datasets
import pdb
from random import shuffle
import Quandl
import math

tok = 'SGhcp7jtU_SqUxpRcGxg'
sample_size = 100

class QuandGetter:
        """Clase que sirve para obtener los datos en Quandl
           y de esa forma usar el minimo numero de consultas.
        """
        def __init__(self, fuentes_, trim_start_, trim_end_, returns_, transformation_, authtoken_, arch_args_,arch_result_):
                """Inicializador de la clase.
                """
                file_args = open(arch_args_,"r")
                if file_args.read() == 'Quandl.get({0}, trim_start={1}, trim_end={2},returns={3},transformation={4} ,authtoken={5})'.format(fuentes_,trim_start_,trim_end_,returns_,transformation_,authtoken_):
                        self.results = np.load(arch_result_+".npy")
                else:
                        file_args.close()
                        file_args = open(arch_args_,"w")
                        file_args.write('Quandl.get({0}, trim_start={1}, trim_end={2},returns={3},transformation={4} ,authtoken={5})'.format(fuentes_,trim_start_,trim_end_,returns_,transformation_,authtoken_))
                        file_args.close()
                        self.results = Quandl.get(fuentes_, trim_start=trim_start_, trim_end=trim_end_,returns=returns_,transformation=transformation_ ,authtoken=authtoken_)
                        np.save(arch_result_,self.results)

        def get_data(self):
                """Obtiene la data
                """
                return self.results

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
                
                #tmp.append( i / float(len(mydata)))
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
                for j in range(0, len(X2[i])):
                	if not math.isnan(X2[i][j]):
                		tmp.append(X2[i][j])
                	else:
                		tmp.append(1.0)

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


datos_deseados = [
"NASDAQOMX/NQASPA.1", # Nasdaq
"YAHOO/INDEX_FTSE.4", # FTSE 100
"YAHOO/INDEX_GDAXI.4", # DAX
"CURRFX/AUDEUR.1", # AUD
"CHRIS/ICE_B1.1", # Oil
]

data_getter = QuandGetter(datos_deseados,"2013-01-04","2014-11-25","numpy","diff",tok,"args_quand.txt","results_quand.txt")
mydata = data_getter.get_data()

mydata2 = mydata[len(mydata)-sample_size:]
mydata = mydata[0:len(mydata)-sample_size]


X = append_age_feature(mydata)
X = delete_nan(X)
y = [ 1 if x >= 0 else -1 for x in obtain_gold_value1(mydata) ]

X2 = append_age_feature(mydata2)
X2 = delete_nan(X2)
y2 = [ 1 if x >= 0 else -1 for x in obtain_gold_value1(mydata2) ]

#pdb.set_trace()
### AQUI EL ALG ###

C = 3.0
h = .1  # step size in the mesh

rbf_svc = svm.SVC(kernel='rbf', gamma=0.1, C=C).fit(X, y)

i = 0
buenos = 0
malos = 0
for x in X2:
	res = rbf_svc.predict(x)
	print "%s | %s" % (res[0],y2[i])

	if res[0] == y2[i]:
		buenos+=1
	else:
		malos+=1
	i+=1
print "Buenos: %s | Malos: %s | Porc: %s" % ( buenos , malos , buenos/float(buenos+malos) )