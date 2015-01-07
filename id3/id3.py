import sys
import os

data = []

ci = 0
for line in open('data', 'r'):
    tt = map(int, line.split())
    data.append(tt)

print data

