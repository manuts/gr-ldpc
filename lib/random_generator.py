import random

f = open("randoms", "w")
for i in range(100000):
    X = random.gauss(0, 0.6)
    f.write(str(X) + "\n")
