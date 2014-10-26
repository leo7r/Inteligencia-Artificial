from PIL import Image

img = Image.new( 'RGB', (100,100), "black") # create a new black image
pixels = img.load() # create the pixel map


with open('instancia_correcta1000') as file:
	lines = file.readlines()
	c = 0

	for i in range(img.size[0]):    # for every pixel:
	    for j in range(img.size[1]):

	    	l = int(lines[ c ])

	    	if l == 1:
	    		pp = 255
	    	else:
	    		pp = 0

	    	c+=1

	        pixels[i,j] = (pp,pp,pp) # set the colour accordingly

img.save("fru.bmp", "BMP")