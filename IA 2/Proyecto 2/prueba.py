import array, random
from deap import creator, base, tools, algorithms
import pdb

def tokBin( string ):
	arr = []
	l = list(string)
	return map(int,l)

def andArray( arr1 , arr2 ):
	if len(arr1) != len(arr2):
		raise ValueError()

	return map( myAnd , zip(arr1,arr2) )

def myAnd( a ):
	return a[0] or a[1]

def fitness(individual):

	count = 0
	for ejemplo in ejemplos:
		
		and1 = andArray( ejemplo[0] , individual[:7] )
		and2 = andArray( ejemplo[1] , individual[7:14] )
		and3 = andArray( ejemplo[2] , individual[14:21] )
		and4 = andArray( ejemplo[3] , individual[21:] )

		num1 = int(''.join(str(x) for x in and1),2)
		num2 = int(''.join(str(x) for x in and2),2)
		num3 = int(''.join(str(x) for x in and3),2)
		num4 = int(''.join(str(x) for x in and4),2)

		num = (num1+num2+num3+num4) / 4

		#pdb.set_trace()

		if num <= 42 and ejemplo[4] == 'Iris-setosa\n':
			count+=1
		elif num > 42 and num <= 83 and ejemplo[4] == 'Iris-versicolor\n':
			count+=1
		elif num > 83 and ejemplo[4] == 'Iris-virginica\n':
			count+=1

	return count,

def mediaFitness( population ):
	fitness_count = 0
	for ind in population:
		fitness_count+= fitness(ind)[0]

	return fitness_count / float(len(population))

## Leyendo datos
ejemplos = []
with open('bezdekIris.data','r') as file:
	for line in file:

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

creator.create("FitnessMax", base.Fitness, weights=(1.0,))
creator.create("Individual", list , fitness=creator.FitnessMax)

toolbox = base.Toolbox()

toolbox.register("attr_bool", random.randint, 0, 1)
toolbox.register("individual", tools.initRepeat, creator.Individual, toolbox.attr_bool, 28)
toolbox.register("population", tools.initRepeat, list, toolbox.individual)

toolbox.register("evaluate", fitness)
toolbox.register("mate", tools.cxTwoPoint)
toolbox.register("mutate", tools.mutFlipBit, indpb=0.05)
toolbox.register("select", tools.selTournament, tournsize=3)

population = toolbox.population(n=300)

NGEN=101
for gen in range(NGEN):
	print 'Generacion %s' % gen
	offspring = algorithms.varAnd(population, toolbox, cxpb=0.5, mutpb=0.1)
	fits = toolbox.map(toolbox.evaluate, offspring)
	for fit, ind in zip(fits, offspring):
		#pdb.set_trace()
		ind.fitness.values = fit
	population = offspring

	print mediaFitness(population)

population.sort( key = lambda ind: fitness(ind) , reverse = True )

print population[0]
print population[1]
print population[2]