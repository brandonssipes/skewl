import random

def flip():
    if random.randint(0,1) == 0:
        return 'H'
    else:
        return 'T'

def y():
    if flip() == 'T':
        return 1 + y()
    else:
        return 1 + x()

def x():
    if flip() == 'T':
        return 1
    else:
        return 1 + x()

def do(num=100000):
    print(sum(y() for _ in range(num))/num)

do(1000000)
