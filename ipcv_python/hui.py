from PIL import Image

def fun(filename):
	im = Image.open(filename)
	im = im.convert('L')
	outname = '/home/townboy/glena.ppm'
	im.save(outname)
	return outname
    
if __name__ == '__main__':
	fun('/home/townboy/lena.ppm')
