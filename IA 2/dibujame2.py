from PIL import Image
import pdb

img = Image.new( 'RGB', (100,100), "green") # create a new black image
pixels = img.load() # create the pixel map

with open('datos_P1_2_SD2014_n1000.txt') as file:

	lines = file.readlines()

	for line in lines:
		#print 'hice un punto'

		tok = line.split(' ')
		if int(tok[2]) == 1:
			pp = 255
		else:
			pp = 0

		x = int(float(tok[0])*5)
		y = int(float(tok[1])*5)

		pixels[x,y] = (pp,pp,pp)

img.save("fru2.bmp", "BMP")