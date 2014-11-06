#!/usr/bin/python
""" Clasificador de Iris"""
import sys
import array, random
import argparse
from deap import creator, base, tools, algorithms
import pdb
RULE_SIZE = 24

def mensaje_ayuda():
        """Imprime mensaje de ayuda"""
        print ""
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
        """Convierte un flotante a un regla con sentido en el programa 
           Pendiente:
                regla 1 [0, 1, 0, 0] es de esta forma [0:4]
                regla 2 [0, 0, 0, 1, 0] es de esta forma [4:9]
                regla 3 [1, 0, 0, 0, 0, 0] es de esta forma [9:15]
                regla 4 [1, 0, 0, 0, 0, 0] es de esta forma [15:21]
        """
        ret = []

        for step in urange(rango_bajo,rango_alto,intervalo):
                if (valor >= step and valor < step + intervalo):
                        ret.append(1)
                else:
                        ret.append(0)
        return ret

def convertir_clasificacion(clasificacion):
        """Convierte clasificaciones.
           Las clasificaciones son de tamano 3. [21:24]
        """
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

                        ejemplos.append(bin1+bin2+bin3+bin4+convertir_clasificacion(tok[4]))
        return ejemplos


def initGabilI(container, func, n):
        """Consideramos que un individuo puede ser de 1 a 4 reglas.
        """
        return tools.initRepeat(container,func,n*random.randint(1,4))

global EJEMPLOS #Coloco esta variable como global.

def comparar_split(ejemplo,individuo,rango):
        """Compara un pedazo de regla con otro"""
        for i in rango:
                for j in rango:
                        if i == j
                                if ejemplo[i] == 1:
                                        if ejemplo[i] == individuo[i]:
                                                return True
                                        else:
                                                return False

def comparar(ejemplo,individuo):
        """Retorna si un ejemplo es clasificado a un individuo 
        """

        if !comparar_split(ejemplo,individuo,range(0,4)):
                return False

        if !comparar_split(ejemplo,individuo,range(4,9)):
                return False

        if !comparar_split(ejemplo,individuo,range(9,15)):
                return False

        if !comparar_split(ejemplo,individuo,range(15,21)):
                return False

        if !ejemplo[21:24] == individuo[21:24]:
                return False
                        


def fitness(individual):
        """Retorna el fitness de un individuo segun la siguiente formula:
                fitness(individual) = (porcentaje aciertos) ** 2
        """
        fitness = 0
        for ejemplo in EJEMPLOS:
                if comparar(ejemplo,individual):
                        fitness += 1
        return (fitness / len(EJEMPLOS))**2,
                        
def crossOver(ind1,ind2):
    news = tools.cxTwoPoint(ind1,ind2)
    chanc = random.randint(1,10)
    bigBrother = 0 if len(news[0]) > len(news[1]) else 1

    if chanc < 3 and len(news[bigBrother]) >= RULE_SIZE*2:
        newsT = (news[bigBrother][24:],news[not bigBrother])

    elif chanc >= 9:
        news2 = tools.cxTwoPoint(ind1,ind2)
        newsT = (news[bigBrother] + news2[random.randint(0,1)][:24],news[not bigBrother])
    else:
        newsT = news
    
    return newsT

def main():
        """Funcion principal de nuestro programa"""

        #Creo el parser de argumentos
        parser = argparse.ArgumentParser(description='Clasificador de Iris usando un sistema tipo GABIL.') 
        #Agrego argumentos
        parser.add_argument("-e","--entrenamiento",type=str,help="Conjunto de datos de entrenamiento")
        parser.add_argument("-f","--prueba",type=str,help="Conjunto de datos de prueba")
        parser.add_argument("-p","--padres",type=str,help="Metodo de seleccion de padres",choices=["ruleta","elitismo"])
        parser.add_argument("-s","--sobrevivientes",type=str,help="Metodo de seleccion de sobrevivientes",choices=["ruleta","torneo"])

        arg = parser.parse_args()
        
        if (arg.entrenamiento == None or arg.prueba == None):
                print "Faltan los archivos de entrenamiento o de prueba. Usa el argumento -h para obtener instrucciones."
                return

        EJEMPLOS = leer_datos(arg.entrenamiento) 
        print EJEMPLOS
        return 
        
        creator.create("FitnessMax", base.Fitness, weights=(1.0,))
        creator.create("Individual", list , fitness=creator.FitnessMax)
        
        toolbox = base.Toolbox()

        toolbox.register("attr_bool", random.randint, 0, 1)
        toolbox.register("individual", myInitRepeat, creator.Individual, toolbox.attr_bool,24)
        toolbox.register("population", tools.initRepeat, list, toolbox.individual)

        toolbox.register("mate", tools.cxTwoPoint)
        toolbox.register("mutate", tools.mutFlipBit, indpb=0.05)
        toolbox.register("select", tools.selTournament, tournsize=3)

        population = toolbox.population(n=300)

        NGEN=10
        for gen in range(NGEN):
	        print 'Generacion %s' % gen
	        offspring = algorithms.varAnd(population, toolbox, cxpb=0.5, mutpb=0.1)
	        fits = toolbox.map(toolbox.evaluate, offspring)
                for fit, ind in zip(fits, offspring):
                        ind.fitness.values = fit
                population = offspring

	print mediaFitness(population)

        population.sort( key = lambda ind: fitness(ind) , reverse = True )

        print population[0]

if __name__ == "__main__":
	main()
