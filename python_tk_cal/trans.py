import Image
for i in range(7):
    im = Image.open('Image/' + str(i) + '.png')
    im.save('Image/' + str(i) + '.PPM')

im = Image.open('Image/notes.png')
im.save('Image/notes.PPM')


