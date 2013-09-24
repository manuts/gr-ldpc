import scipy as sp
import numpy as np

f = sp.fromfile(open("encout"), dtype=sp.int8)

for i in range(10000):
    print int(f[i]),
