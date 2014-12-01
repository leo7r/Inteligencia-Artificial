"""Predictor de los precios del oro.
   Se necesitan las siguientes librerias para ejecutarlo:
   Quandl
   numpy
   Scikit-learn
   Una vez instaladas las librerias tan solo es necesario realizar:
   python proyecto_gold.py
"""
print(__doc__)

import numpy as np
from sklearn.svm import SVR
import matplotlib.pyplot as plt
import pdb
import Quandl
import math

sample_size = 100


tok = 'SGhcp7jtU_SqUxpRcGxg'

#Clases
class QuandGetter:
        """Clase que sirve para obtener los datos en Quandl
           y de esa forma usar el minimo numero de consultas.
           @attr results Datos obtenidos
        """
        def __init__(self, fuentes_, trim_start_, trim_end_, returns_, transformation_, authtoken_, arch_args_,arch_result_):
                """Inicializador de la clase.
                   Utiliza los mismos argumentos que Quandl.get, revisar eso.
                   @param fuentes_ Datos a buscar de Quandl
                   @param trim_start_ Cuando debe empezar a buscar los datos
                   @param trim_end_ Cuando debe terminar de buscar los datos
                   @param returns_ El tipo que debe retornar QuandGetter 
                   @param transformation_ La transformacion que se le debe aplicar a los datos.
                   @param authtoken_ El token del autor de Quandl. Ese es Ruben. Mas de 500 no pueden hacerse.
                   @param arch_args_ Nombre del archivo de argumentos
                   @param arch_results_ Nombre del archivo que debe guardarse.
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
                   @return self.results
                """
                return self.results


#Funciones auxiliares

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
            @param mydata Datos a agregarle la vejez.
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
                for j in range(0, len(X2[i])):
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

def normalize(data):
        """ Funcion que normaliza los datos.
            La normalizacion se hara de la siguiente manera:
            N(x(t)) = (x(t) - x(t-d))/x(t-d)
            Donde t es dia actual y d es el dia anterior.
            @param data Datos obtenidos para normalizar
            @return ndata Datos normalizados.
        """
        ndata = []
        ndata.append(data[0])
        for i in range(1,len(data)):
                tmp = []
                tmp.append(data[i][0])
                for j in range(1,len(data[0])):
                        tmp.append((data[i][j]-data[i-1][j])/float(abs(data[i-1][j])))
                ndata.append(tmp)
        return ndata


def predict(svr, X, y, X2, y2):
        """Realiza predicciones con el svr dado.
           @param svr Tipo de svr a utilizar
           @param X Datos de entrenamiento
           @param y Datos de target para entrenamiento
           @param X2 Datos de prueba
           @param y2 Datos de target de prueba
           @return predicciones, target
        """
        predicciones = []
        targets = []
        malos = 0
        buenos = 0
        i = 0
        error_cuadratico_medio = 0
        for datos in X2:

                y_rbf = svr.fit(X + X2[0:i] , y + y2[0:i] )
                pred = y_rbf.predict([ datos ])
                predicciones.append(pred[0])
                targets.append(y2[i])
                print "%s -> %s  |  %s" % (i,pred[0],y2[i])
                error_cuadratico_medio += (pred[0] - y2[i])**2

                if (pred[0] < 0 and y2[i] < 0) or (pred[0] > 0 and y2[i] > 0):
                        buenos+=1
                elif (y2[i] != 0): 
                        malos+=1

                i+=1

        error_cuadratico_medio = error_cuadratico_medio / float(i)
        print "Buenos: %s | Malos: %s | Porc: %s | Error Cuadratico Medio: %s" % ( buenos , malos , buenos/float(buenos+malos), error_cuadratico_medio )
        return predicciones,targets


#Datos obtenidos del Quandl
datos_deseados = [
"BUNDESBANK/BBK01_WT5511.1", #GOLD Bundesbank. Este es el que queremos predecir.
"OFDP/GOLD_2.1", #LBMA London Price Gold PM
"WSJ/AU_EIB.1", #Gold Engelhard industrial bulliard
"WSJ/AU_EFP",   #Gol Engelhard fabricated product
"OFDP/GOLD_1", #Gold LBMA London Price AM
"WSJ/AU_HHB", #Gold Handy and Harman base price
"WSJ/AU_HHF", #Gold Handy and Harman fabricated price
"WSJ/AU_ZAR", #Krugerrand
"WSJ/AU_MPL", #Maple leaf
"WSJ/AU_EGL", #American Eagle
"WSJ/AU_MXP", #Mexican Pesos (Hijole)
"WSJ/AU_CRN", #Austria Crown
"WSJ/AU_PHL", #Austria Phil
"WGC/GOLD_DAILY_USD", #WORLD GOLD COUNCIL
"WORLDBANK/WLD_GOLD", #WORLD BANK
"OFDP/SILVER_5.1",    #London Silver
"WSJ/AG_EIB", #Silver Engelhard industrial bullion
"WSJ/AG_EFP", #Silver Engelhard Fabricated Products
"WSJ/AG_HHB", #Silver Engelhard Base
"WSJ/AG_HHF", #Silver Engelhard fabric base
"WSJ/PL_MKT", #Free market Platinum
"WSJ/PL_EIB", #Platinum Engelhard industrial bullion
"WSJ/PL_EFP", #Platinum Engelhard fabricated
"JOHNMATT/PLAT.3", #John Matt Platinum 
"DOE/RWTC", #WTI Crude Oil Spot Price
"DOE/RBRTE", #Europe Brent Crude Oil Spot Price
"OPEC/ORB",  #OPEC Base Price
"CURRFX/USDAUD.1", #USD/Australian dollars
"CURRFX/USDCNY.1",  #USD/YEN
"CURRFX/USDEUR.1"  #USD/EUR
]

#Main

print "Descargando Datos..."

data_getter = QuandGetter(datos_deseados,"2012-01-01","2014-11-25","numpy","diff",tok,"args_quand.txt","results_quand.txt")

mydata = data_getter.get_data()

print "Realizando calculos..."

mydata2 = mydata[len(mydata)-sample_size:]
mydata = mydata[0:len(mydata)-sample_size]

y = obtain_gold_value1(mydata) 
y2 = obtain_gold_value1(mydata2)
y2 = delete_nan_simple(y2)


X= append_age_feature(mydata)
X = delete_nan(X)


X2 = append_age_feature(mydata2)
X2 = delete_nan(X2)

#El mejor hasta ahora es:
#C: 7.5
#gamma: 2**-13

svr_rbf = SVR(kernel='rbf', C=7.5, gamma=2**-13)
predicciones, target = predict(svr_rbf,X,y,X2,y2)

plt.plot(predicciones,color="red")
plt.ylabel("Diferencia del precio del oro")
plt.xlabel("Dias")
plt.plot(target)
plt.show()
