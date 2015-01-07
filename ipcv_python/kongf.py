from PIL import Image

outname = '/home/townboy/glena.ppm'

def fun(filename):
    im = Image.open(filename).convert('L')
    pix = im.load()
    x, y = im.size
    num = [[0 for f in range(y)] for f in range(x)]
    for i in range(x):
        for f in range(y):
           num[i][f] = pix[i, f]
    for i in range(x):
        for f in range(y):
            if 0 == i * f:
                pix[i, f] = 0
                continue
            pix[i, f] = abs(num[i-1][f] - num[i][f]) + abs(num[i][f-1] - num[i][f])
    im.save(outname)
    return outname

if __name__ == '__main__':
    fun('/home/townboy/lena.ppm')
    Image.open(outname).show()

