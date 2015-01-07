from PIL import Image

outname = '/home/townboy/glena.ppm'

def fun(filename):
    im = Image.open(filename).convert('L')
    x, y = im.size
    cnt = x * y
    num = [0 for tt in range(256)]

    pix = im.load()

    tt = 0
    for i in range(x):
        for f in range(y):
            num[ pix[i, f] ] += 1
            tt += 1
    for i in range(256):
        num[i] /= 1.0 * cnt;
        if i > 0:
            num[i] += num[i-1]

    to = [0 for tt in range(256)]
    for i in range(256):
        to[i] = int(255 * num[i] + 0.5)

    for i in range(x):
        for f in range(y):
            pix[i, f] = to[pix[i, f]]
    im.save(outname)
    return outname

if __name__ == '__main__':
    fun('/home/townboy/lena.ppm')
    Image.open(outname).show()
