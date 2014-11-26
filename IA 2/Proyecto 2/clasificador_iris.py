#!/usr/bin/python
""" Clasificador de Iris"""
import sys
import array, random
import argparse
from deap import creator, base, tools, algorithms
import pdb
RULE_SIZE = 24
EJEMPLOS = []
RULE_LIMIT = 3 # None en caso de no querer esto


def urange( bajo , alto , step ):
        v = bajo
        l = []
        while v < alto:
                l.append(v)
                v+=step
        return l

def individuo_regla(individuo):
        for i in range(0,len(individuo)):
                if i >= 0 and i < 4:
                        print "sepal length: "
                        if individuo[i] == 1 and i == 0:
                                print "4-5"
                        elif individuo[i] == 1 and i == 1:
                                print "5-6"
                        elif individuo[i] == 1 and i == 2:
                                print "6-7"
                        elif individuo[i] == 1 and i == 3:
                                print "7-8"
                elif i >= 4 and i < 9:
                        print "sepal width: "
                        if individuo[i] == 1 and i == 4:
                                print "2.0-2.5"
                        elif individuo[i] == 1 and i == 5:
                                print "2.5-3.0"
                        elif individuo[i] == 1 and i == 6:
                                print "3.0-3.5"
                        elif individuo[i] == 1 and i == 7:
                                print "3.5-4.0"
                        elif individuo[i] == 1 and i == 8:
                                print "4.0-4.5"
                elif i >= 9 and i < 15:
                        print "petal length: "
                        if individuo[i] == 1 and i == 9:
                                print "1-2"
                        elif individuo[i] == 1 and i == 10:
                                print "2-3"
                        elif individuo[i] == 1 and i == 11:
                                print "3-4"
                        elif individuo[i] == 1 and i == 12:
                                print "4-5"
                        elif individuo[i] == 1 and i == 13:
                                print "5-6"
                        elif individuo[i] == 1 and i == 14:
                                print "6-7"
                elif i >= 15 and i < 21:
                        print "petal width: "
                        if individuo[i] == 1 and i == 15:
                                print "0.0-0.5"
                        elif individuo[i] == 1 and i == 16:
                                print "0.5-1.0"
                        elif individuo[i] == 1 and i == 17:
                                print "1.0-1.5"
                        elif individuo[i] == 1 and i == 18:
                                print "1.5-2.0"
                        elif individuo[i] == 1 and i == 19:
                                print "2.0-2.5"
                        elif individuo[i] == 1 and i == 20:
                                print "2.5-3.0"
        if individuo[21] == 1:
                print "iris setosa"
        if individuo[22] == 1:
                print "iris virginica"
        if individuo[23] == 1:
                print "iris versicolor"
                
                



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

    if RULE_LIMIT and len(individual)/RULE_SIZE > RULE_LIMIT:
        return 0,

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

def seleccion_padres( offspring , population , tipo ):

    for i in range(5):
        rnd = random.randint(0,len(offspring)-1)
        rnd2 = random.randint(0,len(population)-1)

        offspring[ rnd ] = population[ i if tipo == 'elitismo' else rnd2 ]

def main():
    """Funcion principal de nuestro programa"""
    global EJEMPLOS

    #Creo el parser de argumentos
    parser = argparse.ArgumentParser(description='Clasificador de Iris usando un sistema tipo GABIL.') 
    #Agrego argumentos
    parser.add_argument("-e","--entrenamiento",type=str,help="Conjunto de datos de entrenamiento")
    parser.add_argument("-f","--prueba",type=str,help="Conjunto de datos de prueba")
    parser.add_argument("-p","--padres",type=str,help="Metodo de seleccion de padres",choices=["ruleta","mejor"], default = 'ruleta')
    parser.add_argument("-s","--sobrevivientes",type=str,help="Metodo de seleccion de sobrevivientes",choices=["elitismo","ruleta"] , default = 'elitismo')

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

    if arg.padres == 'ruleta':
        toolbox.register("select", tools.selRoulette, k=5)
    else:
        toolbox.register("select", tools.selBest, k=5)

    population = toolbox.population(n=100)
    print 'Empezando A.G con seleccion de padres %s, sobrevivientes %s' % (arg.padres,arg.sobrevivientes)

    NGEN=500
    for gen in range(NGEN):
        #print 'Generacion %s' % gen
        #print mediaFitness(population)**(1/2.0)

        offspring = algorithms.varAnd(population, toolbox, cxpb=0.8, mutpb=0.05)

        # Elitismo
        population.sort( key = lambda ind: fitness(ind) , reverse = True )
        print "Fitness =  %s | Generacion = %s" % (fitness(population[0])[0]**(1/2.0),gen)

        if fitness(population[0])[0] == 1.0:
            print "Num gen %s" % gen
            break

        seleccion_padres(offspring,population,arg.sobrevivientes)

        fits = toolbox.map(toolbox.evaluate, offspring)
        for fit, ind in zip(fits, offspring):
            ind.fitness.values = fit

        population = offspring

    population.sort( key = lambda ind: fitness(ind) , reverse = True )
    print population[0]
    print len(population[0])/RULE_SIZE

    pruebas = leer_datos(arg.prueba)
    buenas = 0
    malas = 0
    for prueba in pruebas:
        if comparar(prueba,population[0]):
            buenas+=1
        else:
            malas+=1
    print 'Buenas %s | Malas %s | Porcentaje exito = %s' % ( buenas,malas,(buenas/float(buenas+malas))*100 )

def main_prueba():

    """Funcion principal de nuestro programa"""
    global EJEMPLOS

    #Creo el parser de argumentos
    parser = argparse.ArgumentParser(description='Clasificador de Iris usando un sistema tipo GABIL.') 
    #Agrego argumentos
    parser.add_argument("-e","--entrenamiento",type=str,help="Conjunto de datos de entrenamiento")
    parser.add_argument("-f","--prueba",type=str,help="Conjunto de datos de prueba")
    parser.add_argument("-p","--padres",type=str,help="Metodo de seleccion de padres",choices=["ruleta","mejor"], default = 'ruleta')
    parser.add_argument("-s","--sobrevivientes",type=str,help="Metodo de seleccion de sobrevivientes",choices=["elitismo","ruleta"] , default = 'elitismo')

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

    if arg.padres == 'ruleta':
        toolbox.register("select", tools.selRoulette, k=5)
    else:
        toolbox.register("select", tools.selBest, k=5)

    '''
    AQUI SE HACEN LAS PRUEBAS PARA CADA VARIACION
    '''

    tasas_mutacion = [ 0.02 , 0.05 , 0.1 ]
    tasas_crossover = [ 0.1 , 0.4 , 0.8 ]
    penalizaciones = [ None , 10 , 20 ]
    num_repeticiones = 100
    resultados = []

    for mut in tasas_mutacion:
        for cross in tasas_crossover:
            for pen in penalizaciones:

                population = toolbox.population(n=100)
                offspring = []
                prom_res = 0
                RULE_LIMIT = pen

                for rep in range(num_repeticiones):

                    NGEN=500
                    for gen in range(NGEN):
                        #print 'Generacion %s' % gen
                        #print mediaFitness(population)**(1/2.0)

                        offspring = algorithms.varAnd(population, toolbox, cxpb=cross, mutpb=mut)

                        # Elitismo
                        population.sort( key = lambda ind: fitness(ind) , reverse = True )
                        #print "Fitness =  %s | Generacion = %s" % (fitness(population[0])[0]**(1/2.0),gen)

                        if fitness(population[0])[0] == 1.0:
                            #print "Num gen %s" % gen
                            break

                        seleccion_padres(offspring,population,arg.sobrevivientes)

                        fits = toolbox.map(toolbox.evaluate, offspring)
                        for fit, ind in zip(fits, offspring):
                            ind.fitness.values = fit

                        population = offspring

                    population.sort( key = lambda ind: fitness(ind) , reverse = True )
                    #print population[0]
                    #print len(population[0])/RULE_SIZE

                    pruebas = leer_datos(arg.prueba)
                    buenas = 0
                    malas = 0
                    for prueba in pruebas:
                        if comparar(prueba,population[0]):
                            buenas+=1
                        else:
                            malas+=1

                    prom_res+= (buenas/float(buenas+malas))*100

                rrr = {
                    'Tipo' : 'Mut: %s | CX: %s | Pen: %s' % (mut,cross,pen),
                    'Resultado' : prom_res/num_repeticiones
                    }
                resultados.append(rrr)
                print rrr
                    #print 'Buenas %s | Malas %s | Porcentaje exito = %s' % ( buenas,malas,(buenas/float(buenas+malas))*100 )
    #print resultados
    with open('resultados_pruebas','w+') as f:
        f.write('Se hicieron 100 corridas para cada una de las configuraciones, estos son los resultados:\n')
        for resultado in resultados:
            f.write( str(resultado) + '\n' )

if __name__ == "__main__":
    main()
    #main_prueba()
