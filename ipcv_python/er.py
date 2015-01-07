from PIL import Image

def fun(filename):
	im = Image.open(filename).convert('L')
	pix = im.load()
	x, y = im.size
	for i in range(x):
		for f in range(y):
			if pix[i, f] < 100:
				pix[i, f] = 0
			else:
				pix[i, f] = 255
	savename = '/home/townboy/glena.ppm'
	im.save(savename)
	return savename

if __name__ == '__main__':
	Image.open(fun('/home/townboy/lena.ppm')).show()

