from PIL import Image

outname = '/home/townboy/glena.ppm'

def fun(filename):
    im = Image.open(filename).convert('L')
    pix = im.load()
    x, y = im.size
    ans = [[0 for i in range(y)] for f in range(x)]
    for i in range(x):
        for f in range(y):
            ans[i][f] = pix[i, f]

    for i in range(2, x - 2):
        for f in range(2, y - 2):
            tt = []
            for g in range(-2, 3):
                for h in range(-2, 3):
                    tt.append(pix[i + g, f + h])
            tt.sort()
            ans[i][f] = tt[12]

    for i in range(x):
        for f in range(y):
            pix[i, f] = ans[i][f]
    im.save(outname)
    return outname

if __name__ == '__main__':
    fun('/home/townboy/lena.ppm')
    Image.open(outname).show()

