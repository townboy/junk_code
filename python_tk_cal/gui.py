# -*- coding:utf-8 _*_
import Tkinter
import platform

system = platform.system()
if 'Linux' == system:
    print 'success'
    path = 'Image/'
else:
    path = 'Image\\'

INDEX = 0
ImagePos = [None for i in range(7)]
LabelPos = [None for i in range(7)]

Entry = [None for i in range(200)]
EntryPos = [None for i in range(200)]
EntryRange = [None for i in range(8)]
root = Tkinter.Tk()

def display():
    LabelPos[INDEX].place(x = 50, y = 130)
    L, R = EntryRange[INDEX]
    for i in range(L, R):
        Entry[i].place(x = 911, y = EntryPos[i])
    if 6 == INDEX:
        L, R = EntryRange[INDEX + 1]
        for i in range(L, R):
            Entry[i].place(x = 911, y = EntryPos[i])

def undisplay():
    LabelPos[INDEX].place_forget()
    L, R = EntryRange[INDEX]
    for i in range(L, R):
        Entry[i].place_forget()
    if 6 == INDEX:
        L, R = EntryRange[INDEX + 1]
        for i in range(L, R):
            Entry[i].place_forget()
        

def NextPage():
    global INDEX
    if 6 == INDEX:
        return
    undisplay()
    INDEX += 1
    display()

def LastPage():
    global INDEX
    if 0 == INDEX:
        return
    undisplay()
    INDEX -= 1
    display()

def get(x):
    try:
        ans = float(Entry[x].get())
        return ans
    except Exception as e:
        return 0.1

def fu(x, val):
    Entry[x].delete(0, Tkinter.END)
    Entry[x].insert(0, str(val))

def Compute():
    for i in range(100):
        val = get(62) * (get(63) - get(64)) + get(65) * (get(67) - get(66)) + get(68) * (get(67) - get(69)) + get(70) * (get(72) - get(71)) + get(73) * (get(71) - get(64))
        fu(122, val)

        val = 0.84 + 37.68 * 0.000001 * (13 + get(15)) * (130 + get(17))
        fu(121, val)

        val = 0.71 + 5.02 * 0.0001 * get(42)
        fu(120, val)

        val = 100 * get(14) / (100 - get(12))
        fu(119, val)

        val = 0.01 * (get(120) * get(119) + get(121) *(100 - get(119)))
        fu(118, val)

        val = get(118) * (100 - get(12)) / 100 + 4.1868 * get(12) / 100
        fu(117, val)

        val = get(75) * 3600
        fu(116, val)

        val = 3.35 * (get(12) - get(13) * (100 - get(12)) / (100 - get(13)))
        fu(115, val)

        val = get(51) * (get(52) - get(53))
        fu(114, val)

        val = get(59) * (get(60) * get(61) - get(57) * get(54))
        fu(113, val)

        val = get(117) * (get(17) - get(54))
        fu(112, val)

        fu(111, get(16))

        val = get(122) * 100 / get(133)
        fu(110, val)

        val = get(9) / 100 * (57.19 * get(88) * get(20) - 152 * get(89))
        fu(109, val)

        val = get(91) / 100 * (get(37) * (get(34) - get(54)) * get(35) / (100 - get(36)) + get(48) * (get(58) - get(54)) * get(46) / (100 - get(47)) + get(41) * (get(38) - get(54)) * get(39) / (100 - get(40)) + get(45) * (get(42 - get(54)))  * get(43) / (100 - get(44)))
        fu(108, val)

        val = get(106) * get(74)
        fu(107, val)

        val = 5.82 * (get(50) / 1000) ** -0.38
        fu(106, val)

        val = 337 * get(91) * get(92) / 100
        fu(105, val)

        val = get(82) * (126.36 * get(26) + 358.18 * get(31) + 107.98 * get(28) + 590.79 * get(32))
        fu(104, val)

        val = 0.089 * (get(87) + 0.375 * get(9) ) + 0.265 * get(8) + 0.0167 * get(9) * get(89) / 100 - 0.0333 * get(10)
        fu(103, val)
        
        val = 1.866 * (get(7) + 0.375 * get(9)) / 100 + 0.79 * get(103) + 0.8 * get(11) / 100 + 0.7 * get(8) * (get(20) * get(88) - get(89)) / 10000
        fu(102, val)

        val = 1.24 * ((9 * get(8) + get(12)) / 100 + get(102) * get(18) / 10000 + 1.293 * get(85) * get(86) * get(55))
        fu(101, val)

        val = 3.125 * get(88) * get(9) / get(19) * 100
        fu(100, val)

        val = get(102) + 0.4 * get(103)
        fu(99 ,val)

        val = get(33) * get(85) / 1.4
        fu(98, val)

        val = 2 * get(9) / get(99) * 10000
        fu(97, val)

        val = (1 - get(19) / 100 - get(18) / 100) * get(100)
        fu(96, val)

        val = get(100) * (1 - get(20) / 100) * get(19) / 100
        fu(95, val)

        val = (1.75 * get(9) * (get(88) - get(89) / 100) / 100 - get(100) * (1 - get(20) / 100) * get(19) * 56 / 1000000) * 100
        fu(94, val)

        val = 0.0425 * get(89) * get(9)
        fu(93, val)

        val = get(37) * get(36) / (100 - get(36)) + get(48) * get(47) / (100 - get(47)) + get(41) * get(40) / (100 - get(40)) + get(45) * get(44) / (100 - get(44))
        fu(92, val)

        val = get(14) + get(93) + get(94) + get(95) + get(96)
        fu(91, val)

        fu(90, 80)

        fu(89, get(128))
        
        val = get(21) * get(19) / 100 * 32 / get(9) / get(130)
        fu(88, val)

        val = get(7) - get(91) * get(92) / 100
        fu(87, val)

        val = 0.089 * (get(87) + 0.375 * get(9)) + 0.265 * get(8) + 0.0167 * get(9) * get(89) / 100 - 0.0333 * get(10)
        fu(86, val)

        val = 21 / (21 - (get(22) - 2 * get(31) - 0.5 * get(26) - 0.5 * get(28)))
        fu(85, val)

        val = 1.866 * (get(7) + 0.375 * get(9)) / 100 + 0.79 * get(86) + 0.8 * get(11) / 100 + 0.7 * get(9) * (get(20) * get(88) - get(89)) / 100 / 100
        fu(84, val)

        val = get(25) * get(24) / 100 + get(23) * get(22) / 100 + get(30) * get(29) / 100 + get(27) * get(26) / 100
        fu(83, val)

        val = get(84) + (get(85) - 1) * get(86)
        fu(82, val)
        
        val = get(101) * get(56) * (get(58) - get(54))
        fu(81, val)

        val = get(82) * get(83) * (get(58) - get(54))
        fu(80, val)

        val = get(80) + get(81)
        fu(79, val)

        fu(126, 80)
        
        fu(127, get(128))

        val = (get(97) - get(98)) * 100 / get(97)
        fu(128, val)

        fu(129, 90)

        if get(17) >= 0:
            val = (get(110) - get(113) - get(114) - get (116)) / (get(111) + get(112)) 
        else:
            val = (get(110) - get(113) - get(114) - get (116)) / (get(111) + get(112) - get(115)) 
        fu(130, val)

        fu(131, 84.84083652)

        fu(132, get(129))

        val = 100 - get(143) - get(144) - get(145) - get(146) - get(147) - get(148)
        fu(133, val)

        fu(138, get(110))

        fu(139, get(122))

        val = get(139) / get(138) * 100
        fu(140, val)

        val = get(79) * get(130) / get(110) * 100
        fu(143, val)

        val = get(104) * get(130) / get(110) * 100
        fu(144, val)

        val = get(105) * get(130) / get(110) * 100
        fu(145, val)

        val = get(107) * get(49) / get(50)
        fu(146, val)

        val = get(108) * get(130) / get(110) * 100
        fu(147, val)

        val = get(109) * get(130) / get(110) * 100
        fu(148, val)

        fu(149, get(133))

def ClearAll():
    for i in range(8):
        L, R = EntryRange[i]
        for f in range(L, R):
            Entry[f].delete(0, Tkinter.END)

initVal = [0, 0, 0, 0, 0, 0, 0 ,
89.86,
3.29,
0.45,
5.26,
1.14,
2.04,
0,
20.08,
5.97,
26936.91,
23,
6,
85,
98,
5500,
4.6,
1.324112,
13,
1.78919,
0.005,
1.303698,
0,
82.395,
1.297206,
0,
0,
350,
900,
0.8374,
1.77,
40,
800,
0.8374,
5,
12,
200,
0.8374,
9.56,
8,
0.8118,
13,
40,
400000,
393000,
0,
0,
0,
20,
0.012,
1.5115,
0,
137,
0,
0,
0,
400000,
3470.1,
858.98,
350000,
1200,
1690,
0,
700.98,
0,
1706.5,
2532.62,
0.01,
1.1,
0]

def genButt():
    EntryRange[0] = [7, 34]
    for i in range(7, 34):
        Entry[i] = Tkinter.Entry(root, width = 8)
        EntryPos[i] = 57 + i * 16.8

    EntryRange[1] = [34, 49]
    for i in range(34, 49):
        Entry[i] = Tkinter.Entry(root, width = 8)
        EntryPos[i] = -450 + i * 17.1

    EntryRange[2] = [49, 76]
    for i in range(49, 76):
        Entry[i] = Tkinter.Entry(root, width = 8)
        EntryPos[i] = 63 + (i - 45) * 17.1

    for i in range(7, 76):
        if None == initVal[i]:
            continue
        fu(i, initVal[i])

    EntryRange[3] = [79, 104]
    for i in range(79, 104):
        Entry[i] = Tkinter.Entry(root, width = 8)
        EntryPos[i] = 5 + (i - 69) * 16.8

    EntryRange[4] = [104, 123]
    for i in range(104, 123):
        Entry[i] = Tkinter.Entry(root, width = 8)
        EntryPos[i] = -10 + (i - 96) * 17.1

    EntryRange[5] = [126, 134]
    for i in range(126, 134):
        Entry[i] = Tkinter.Entry(root, width = 8)
        EntryPos[i] = -47 + (i - 112) * 15.7

    EntryRange[6] = [138, 141]
    for i in range(138, 141):
        Entry[i] = Tkinter.Entry(root, width = 8)
        EntryPos[i] = -127 + (i - 119) * 16.8

    EntryRange[7] = [143, 150]
    for i in range(143, 150):
        Entry[i] = Tkinter.Entry(root, width = 8)
        EntryPos[i] = -156 + (i - 117) * 16.7

def init():
    global root
    root.title('Measurement Procedure Chart of A Boiler Efficiency')
    root.geometry('1030x750')

    TitleImage = Tkinter.PhotoImage(file = path + 'title.PPM')
    Tkinter.Label(root ,image = TitleImage).place(x = 50, y = 10)
    NoteImage = Tkinter.PhotoImage(file = path + 'notes.PPM')
    Tkinter.Label(root ,image = NoteImage).place(x = 50, y = 650)

    Tkinter.Button(root, text = 'Compute', command = Compute, width = 9).place(x = 930, y = 680)
    Tkinter.Button(root, text = 'Next Page', command = NextPage, width = 9).place(x = 930, y = 650)
    Tkinter.Button(root, text = 'Last page', command = LastPage, width = 9).place(x = 830, y = 650)
    Tkinter.Button(root, text = 'Clear All', command = ClearAll, width = 9).place(x = 830, y = 680)

    INDEX = 0
    
    global ImagePos, LabelPos
    for i in range(7):
        ImagePos[i] = Tkinter.PhotoImage(file = path + str(i) + '.PPM')
        LabelPos[i] = Tkinter.Label(root ,image = ImagePos[i])

    genButt()
    display()
    root.mainloop()

init()
