from PIL import Image

outname = '/home/townboy/glena.ppm'

def getColor(L):
    if L < 127:
        R = 0
    elif L > 191:
        R = 255
    else:
        R = (L - 127) * 4 - 1

    if L < 64:
        G = 255
    elif L > 191:
        G = 0
    else:
        G = 256 - (L -191) * 4

    if L < 64:
        B = 255
    elif L > 127:
        B = 0
    else:
        B = 256 - (L - 63) * 4

    return R, B, G

def fun(filename):
    im = Image.open(filename)
    imc = im.convert('L')
    pix = im.load()
    pixc = imc.load()
    x, y = im.size
    for i in range(x):
        for f in range(y):
            pix[i, f] = getColor(pixc[i, f])
    im.save(outname)
    return outname

if __name__ == '__main__':
    fun('/home/townboy/lena.ppm')
    Image.open(outname).show()

