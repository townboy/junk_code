import random
from PIL import Image

outname = '/home/townboy/glena.ppm'

def fun(filename):
    im = Image.open(filename).convert('L')
    pix = im.load()
    x, y = im.size
    def get():
        return random.randint(0, x - 1), random.randint(0, y - 1)

    for i in range(7000):
        pix[get()] = random.randint(0, 255)
    im.save(outname)
    return outname

if __name__ == '__main__':
    fun('/home/townboy/lena.ppm')
    Image.open(outname).show()
