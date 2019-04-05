#! /usr/bin/env python3
###################################
#### Brandon Sipes Paillier #######
#### created April 2, 2019 ########
#### last updated April 4, 2019 ###
###################################

from Crypto.Util.number import inverse
import secrets
import math
import time


class Paillier:
    def KeyGen(self, s):
        q = secrets.randbits(s)
        while(not(self._isPrime(q))):
            q = secrets.randbits(s)
        p = secrets.randbits(s)
        while(not (self._isPrime(p))):
            p = secrets.randbits(s)
        self.n = p*q
        while(math.gcd(self.n, (p-1)*(q-1)) != 1):
            q = secrets.randbits(s)
            p = secrets.randbits(s)
            self.n = p*q
        y = (p-1)*(q-1)
        g = self.n+1
        u = inverse(y,self.n)
        return (self.n,g,y,u)

    def _L(self,x):
        return (x-1)//self.n

    def Encrypt(self, n, g, m):
        n2 = n**2
        r = secrets.randbelow(n)
        while(math.gcd(r,n) != 1):
            r = secrets.randbelow(n)
        c = pow(g,m,n2)*pow(r,n,n2) #by doing pows both times
        c = c%n2                    #this should all be faster
        return c


    def Decrypt(self, y, u, c):
        sipes = pow(c,y,(self.n**2))
        brandon = self._L(sipes)
        m = (brandon*u)%self.n
        return m


    #To generate a prime number I found these three functions from https://inventwithpython.com/rabinMiller.py
    #Hopefully their implementation is is better than what I did for rsa.py from hw02 
    #though I will be making edits to this to use secrets rather than random
    def _rabinMiller(self,num):
        # Returns True if num is a prime number.
    
        s = num - 1
        t = 0
        while s % 2 == 0:
            # keep halving s while it is even (and use t
            # to count how many times we halve s)
            s = s // 2
            t += 1
    
        for trials in range(5): # try to falsify num's primality 5 times
            a = secrets.randbelow(num - 1 - 2)+2
            v = pow(a, s, num)
            if v != 1: # this test does not apply if v is 1.
                i = 0
                while v != (num - 1):
                    if i == t - 1:
                        return False
                    else:
                        i = i + 1
                        v = (v ** 2) % num
        return True
    
    
    def _isPrime(self,num):
        # Return True if num is a prime number. This function does a quicker
        # prime number check before calling rabinMiller().
    
        if (num < 2):
            return False # 0, 1, and negative numbers are not prime
    
        # About 1/3 of the time we can quickly determine if num is not prime
        # by dividing by the first few dozen prime numbers. This is quicker
        # than rabinMiller(), but unlike rabinMiller() is not guaranteed to
        # prove that a number is prime.
        lowPrimes = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997]
    
        if num in lowPrimes:
            return True
    
        # See if any of the low prime numbers can divide num
        for prime in lowPrimes:
            if (num % prime == 0):
                return False
    
        # If all else fails, call rabinMiller() to determine if num is a prime.
        return self._rabinMiller(num)
    
   


def main():
    p = Paillier()
    n,g,y,u = p.KeyGen(1024)
    plain = 20
    plain2 = 90
    cipher = p.Encrypt(n,g,plain)
    cipher2= p.Encrypt(n,g,plain2)
    test = (cipher*cipher2)%(n**2)
    test1 = p.Decrypt(y,u,test)
    test2 = plain + plain2
    if(test1 == test2):
        print("It works!!!")
    else:
        print("umm... something doesn't seem right...")
    print("performing benchmarks:")
    benchmark()

def benchmark():
    p = Paillier()
    for i in [512, 1024, 2048]:
        n,g,y,u = p.KeyGen(i)
        m = secrets.randbelow(n)
        start = time.time()
        oneThousand(p.Encrypt,n,g,m)
        end = time.time()
        s = "Encryption time for {} bits is: {}s".format(i,(end-start)/1000)
        print(s)
        start = time.time()
        oneThousand(p.Decrypt,y,u,m) #random bits should look the same Encrypted or not
        end = time.time()
        s = "Decryption time for {} bits is: {}s".format(i,(end-start)/1000)
        print(s)
        r = secrets.randbelow(n)
        q = secrets.randbelow(n)
        start = time.time()
        for _ in range(1000):
            r*q
        end = time.time()
        s = "Multiplication time for {} bits is: {}s".format(i,(end-start)/1000)
        print(s)







def oneThousand(lam,a,b,c):
    for i in range(1000):
        lam(a,b,c)

if __name__ == '__main__':
    main()






