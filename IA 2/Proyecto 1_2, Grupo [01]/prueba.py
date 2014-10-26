
test2 = []
#with open('datos_P1_2_SD2014_n500.txt') as f1:
with open('test001.txt') as f1:
	for line in f1:
	    tok = line.split(' ')

	    if float(tok[2]) == 1.0:
	        res = 1.0
	    else:
	        res = 0.0

	    test2.append([ [float(tok[0]) , float(tok[1])] , [ res ] ])

buenos = 0
malos = 0
for test in test2:
	cuenta = (test[0][0]-10)**2+(test[0][1]-10)**2
	if cuenta <= 49:
		ejemplo = 0.0
	else:
		ejemplo = 1.0

	if ejemplo == test[1][0]:
		buenos+=1
	else:
		malos+=1

print 'Buenos %s | Malos %s' % (buenos,malos,)