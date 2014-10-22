import random
import pdb

unos = 0
menosuno = 0

l1 = []
l2 = []


with open('test001.txt','w+') as file:
	for i in range(100000000):

		x = random.random() * 20
		y = random.random() * 20

		cuenta = (x-10)**2+(y-10)**2

		if cuenta <= 49:
			res = -1
			menosuno+=1
			l2.append([x,y,res])
		else:
			res = 1
			unos+=1
			l1.append([x,y,res])

		if len(l1) >= 1000 and len(l2) >= 1000:
			break

	for i in range(len(l1)):
		if i >= 1000:
			break
		try:
			file.write('%s %s %s\n' % (l2[i][0],l2[i][1],l2[i][2],) )
			file.write('%s %s %s\n' % (l1[i][0],l1[i][1],l1[i][2],) )
		except:
			print i
			pdb.set_trace()

print "%s | %s" %(unos,menosuno)			
