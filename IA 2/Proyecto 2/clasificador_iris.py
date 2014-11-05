#!/usr/bin/python
""" Clasificador de Iris"""
import sys
import array, random
from deap import creator, base, tools, algorithms
import pdb

def mensaje_ayuda():
        """Imprime mensaje de ayuda"""
        print "Clasificador de Iris."
        print "Uso:"
        print "clasificador_iris.py -e <conjunto entrenamiento> -f <conjunto prueba> -p <seleccion padre> -s <seleccion sobrevivientes>"
        print "-s: "
        print "-p: "

def urange( bajo , alto , step ):
        v = bajo
        l = []
        while v < alto:
                l.append(v)
                v+=step
        return l

def convertir_regla(valor, rango_bajo, rango_alto, intervalo):
        """Convierte un flotante 
        """
        ret = []

        for step in urange(rango_bajo,rango_alto,intervalo):
                if (valor >= step and valor < step + intervalo):
                        ret.append(1)
                else:
                        ret.append(0)
        return ret

def convertir_clasificacion(clasificacion):
        if clasificacion == "Iris-setosa\n":
                return [1,0,0]
        elif clasificacion == "Iris-virginica\n":
                return [0,1,0]
        return [0,0,1]


def leer_datos(file):
        """Esta funcion lee los datos y los transforma en reglas.
           @param file Nombre de archivo
           @return ejemplos
        """
           
        ejemplos = []
        with open(file) as f:
                for line in f:
                        tok = line.split(',')

                        n1 = float(tok[0])
                        n2 = float(tok[1])
                        n3 = float(tok[2])
                        n4 = float(tok[3])

                        bin1 = convertir_regla(n1,4,8,1)
                        bin2 = convertir_regla(n2,2,4.5,0.5)
                        bin3 = convertir_regla(n3,1,7,1)
                        bin4 = convertir_regla(n4,0.0,3.0,0.5)

                        ejemplos.append( [ bin1+bin2+bin3+bin4 , convertir_clasificacion(tok[4]) ])
        return ejemplos
                        

def main():
        """Funcion principal de nuestro programa"""
        # Imprime mensaje de ayuda si no hay argumentos.
        if (len(sys.argv) <= 1):
                mensaje_ayuda() 
                return 
        
        ejemplos = leer_datos(sys.argv[1])
        pdb.set_trace()

if __name__ == "__main__":
	main()
