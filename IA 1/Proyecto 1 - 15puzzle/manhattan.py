puzzle = 4

man = [[0 for x in xrange(puzzle*puzzle)] for x in range(puzzle*puzzle)]

for fil in range(puzzle):
	for col in range(puzzle):
				
		for i in range(puzzle):
			for j in range(puzzle):
				r = abs(col-j) + abs(fil-i)
				
				if fil*puzzle+col != 0:
					man[fil*puzzle+col][i*puzzle+j] = r
				else:
					man[fil*puzzle+col][i*puzzle+j] = 0
				
for row in man:
	print row