#!/usr/bin/python
""" Clasificador de Iris"""
import sys
import array, random
import argparse
from deap import creator, base, tools, algorithms
import pdb
RULE_SIZE = 24
EJEMPLOS = []

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

def comparar_split(ejemplo,individuo,rango):
    """Compara un pedazo de regla con otro"""
    for i in rango:
        if ejemplo[i % RULE_SIZE ] == 1:
            if ejemplo[i % RULE_SIZE ] == individuo[i]:
                return True
            else:
                return False

def comparar(ejemplo,individuo):
        """Retorna si un ejemplo es clasificado a un individuo 
        """

        for regla in range( len(individuo)/ RULE_SIZE ):

            #print "%s\n%s" % ( ejemplo , individuo[regla:regla+RULE_SIZE], )

            #pdb.set_trace()

            if not comparar_split(ejemplo,individuo,range(regla*RULE_SIZE,regla*RULE_SIZE+4)):
                continue
            #print 'Pase 1er rasgo'

            if not comparar_split(ejemplo,individuo,range(regla*RULE_SIZE+4,regla*RULE_SIZE+9)):
                continue
            #print 'Pase 2 rasgo'

            if not comparar_split(ejemplo,individuo,range(regla*RULE_SIZE+9,regla*RULE_SIZE+15)):
                continue
            #print 'Pase 3 rasgo'

            if not comparar_split(ejemplo,individuo,range(regla*RULE_SIZE+15,regla*RULE_SIZE+21)):
                continue
            #print 'Pase 4 rasgo'

            if not ejemplo[21:24] == individuo[regla*RULE_SIZE+21:regla*RULE_SIZE+24]:
                continue
            #print 'Pase clasif'
            
            return True

        return False
                        
def fitness(individual):
    """Retorna el fitness de un individuo segun la siguiente formula:
            fitness(individual) = (porcentaje aciertos) ** 2
    """
    global EJEMPLOS

    fitness = 0
    for ejemplo in EJEMPLOS:
        
        #pdb.set_trace()
        #raw_input('Habla..')

        if comparar(ejemplo,individual):
            fitness += 1

    #if fitness != 0:
    #    pdb.set_trace()

    return (fitness / float(len(EJEMPLOS)))**2,

def mediaFitness( population ):
    fitness_count = 0
    for ind in population:
        fitness_count+= fitness(ind)[0]

    return fitness_count / float(len(population))

def crossOver2(ind1,ind2):

    c1 = random.randint(0,RULE_SIZE)
    c2 = random.randint(c1,RULE_SIZE)

    r11 = random.randint(0,(len(ind1)/RULE_SIZE)-1)
    r12 = random.randint(r11,(len(ind1)/RULE_SIZE)-1)

    r21 = random.randint(0,(len(ind2)/RULE_SIZE)-1)
    r22 = random.randint(r21,(len(ind2)/RULE_SIZE)-1)

    #pdb.set_trace()
    new1 = ind1[0:r11*RULE_SIZE+c1] + ind2[ r21*RULE_SIZE+c1 : r22*RULE_SIZE+c2 ] + ind1[r12*RULE_SIZE+c2:]
    new2 = ind2[0:r21*RULE_SIZE+c1] + ind1[ r11*RULE_SIZE+c1 : r12*RULE_SIZE+c2 ] + ind2[r22*RULE_SIZE+c2:]

    return (creator.Individual(new1),creator.Individual(new2))

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
    

    return ( creator.Individual(newsT[0]) , creator.Individual(newsT[1]) )
    #return newsT

def main():
    """Funcion principal de nuestro programa"""
    global EJEMPLOS

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
    
    creator.create("FitnessMax", base.Fitness, weights=(1.0,))
    creator.create("Individual", list , fitness=creator.FitnessMax)
    
    toolbox = base.Toolbox()

    toolbox.register("attr_bool", random.randint, 0, 1)
    toolbox.register("individual", initGabilI, creator.Individual, toolbox.attr_bool,24)
    toolbox.register("population", tools.initRepeat, list, toolbox.individual)
    
    toolbox.register("evaluate",fitness)
    toolbox.register("mate", crossOver2 )
    toolbox.register("mutate", tools.mutFlipBit, indpb=0.05)
    toolbox.register("select", tools.selBest, k=5)

    population = toolbox.population(n=100)

    NGEN=500
    for gen in range(NGEN):
        #print 'Generacion %s' % gen
        #print mediaFitness(population)**(1/2.0)

        offspring = algorithms.varAnd(population, toolbox, cxpb=0.8, mutpb=0.1)

        # Elitismo
        population.sort( key = lambda ind: fitness(ind) , reverse = True )
        print "Fitness =  %s | Poblacion %s" % (fitness(population[0])[0]**(1/2.0),len(population))

        if fitness(population[0])[0] == 1.0:
            print "Num gen %s" % gen
            break

        for i in range(5):
            rnd = random.randint(0,len(offspring)-1)
            offspring[ rnd ] = population[i]

        fits = toolbox.map(toolbox.evaluate, offspring)
        for fit, ind in zip(fits, offspring):
            ind.fitness.values = fit

        population = offspring

    population.sort( key = lambda ind: fitness(ind) , reverse = True )
    print population[0]

if __name__ == "__main__":
    main()
