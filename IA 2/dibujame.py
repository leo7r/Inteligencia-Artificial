from PIL import Image

img = Image.new( 'RGB', (100,100), "black") # create a new black image
pixels = img.load() # create the pixel map


with open('circulo.txt') as file:
	lines = file.readlines()

	for i in range(img.size[0]):    # for every pixel:
	    for j in range(img.size[1]):

	    	l = int(lines[ i % 100 * j ])

	    	if l == 1:
	    		pp = 255
	    	else:
	    		pp = 0

	        pixels[i,j] = (pp,pp,pp) # set the colour accordingly

img.save("fru.bmp", "BMP")