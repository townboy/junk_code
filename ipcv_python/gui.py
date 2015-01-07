# -*- coding:utf-8 -*-
import Tkinter
from PIL import Image
import FileDialog
import er, hui, zhif, wei, zhhf, kongf
#import fuf
import jiaof

filename = 'normal.ppm'
savename = 'lena.jpg'

root = Tkinter.Tk()
root.geometry("850x700")
root.title("Lena")

def loadfile():
    fd = FileDialog.LoadFileDialog(root)
    global filename
    filename = fd.go()
    print filename
    Image.open(filename).save(filename + '.ppm')
    change(filename = filename + '.ppm', x = 50, y = 50)

def change(filename, x = 520, y = 50):
    img = Tkinter.PhotoImage(file = filename)
    tt = Tkinter.Label(root, image = img)
    tt.place(x = x, y = y)
    tt.mainloop()

def erzhi():
    change(filename = er.fun(filename))

def huidu():
    change(filename = hui.fun(filename))

def zhi():
    change(filename = zhif.fun(filename))

def rotate():
    Image.open(filename).rotate(330).save(savename)
    change(savename)

def weif():
    change(filename = wei.fun(filename))

def zhh():
    change(filename = zhhf.fun(savename))

def kong():
    change(filename = kongf.fun(filename))

def fu():
    #change(filename = fuf.fun(filename))
    change(filename = kongf.fun(filename))

def jiao():
    change(filename = jiaof.fun(filename))

def save():
    tt = entry.get()
    Image.open(savename).save(tt)

Tkinter.Button(root, text = '二值化', width = 10, height = 1, command = erzhi).place(x = 400, y = 140)
Tkinter.Button(root, text = '灰度化', width = 10, height = 1, command = huidu).place(x = 400, y = 180)
Tkinter.Button(root, text = '直方图均衡化', width = 10, height = 1, command = zhi).place(x = 400, y = 220)
Tkinter.Button(root, text = '伪彩色增强', width = 10, height = 1, command = weif).place(x = 400, y = 260)
Tkinter.Button(root, text = '旋转', width = 10, height = 1, command = rotate).place(x = 400, y = 300)
Tkinter.Button(root, text = 'choose', command = loadfile, width = 10, height = 1).place(x = 400, y = 100)
Tkinter.Button(root, text = '中值滤波器', width = 10, height = 1, command = zhh).place(x = 400, y = 340)
Tkinter.Button(root, text = '空域图像锐化', width = 10, height = 1, command = kong).place(x = 400, y = 380)
Tkinter.Button(root, text = '傅里叶变化', width = 10, height = 1, command = fu).place(x = 400, y = 420)
Tkinter.Button(root, text = '椒盐噪声', width = 10, height = 1, command = jiao).place(x = 400, y = 460)
Tkinter.Button(root, text = '保存图像', width = 10, height = 1, command = save).place(x = 400, y = 500)
img = Tkinter.PhotoImage(file = filename)
entry = Tkinter.Entry(root, width = 12)
entry.place(x = 400, y = 540)
Tkinter.Label(root, image = img).place(x = 50, y = 50)

root.mainloop()
