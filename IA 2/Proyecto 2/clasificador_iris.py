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
        print "p: "

def leer_datos(file):
        """Esta funcion lee los datos pero no se como
           @param file Nombre de archivo
        """
           
        ejemplos = []
        with open(file) as f:
                for line in f:
                        tok = line.split(',')
                        n1 = int(float(tok[0])*10.0)
                        n2 = int(float(tok[1])*10.0)
                        n3 = int(float(tok[2])*10.0)
                        n4 = int(float(tok[3])*10.0)

                        bin1 = '{0:07b}'.format(n1)
                        bin2 = '{0:07b}'.format(n2)
                        bin3 = '{0:07b}'.format(n3)
                        bin4 = '{0:07b}'.format(n4)

                        ejemplos.append([tokBin(bin1),tokBin(bin2),tokBin(bin3),tokBin(bin4),tok[4]])
        return ejemplos
                        

def main():
        """Funcion principal de nuestro programa"""
        # Imprime mensaje de ayuda si no hay argumentos.
        if (len(sys.argv) <= 1):
        mensaje_ayuda() 
	return 

