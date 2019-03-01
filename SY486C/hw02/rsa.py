#####################################
#### Brandon Sipes RSA TOOL##########
#### created February 23, 2019#######
#### last updated February 23, 2019##
#####################################

import secrets
import sys

class RSA:
    def modPow(this,x,y,n):
        if (y >= 0):
            return this.__modPow(x,y,n)
        elif (y == -1):
            try:
                g, a, _ = this.__modInverse(x,n)
                if g == 1:
                    return a % n
                else:
                    raise ValueError("Does not have an inverse")
            except ValueError as e:
                print(e.args)

    def __modPow(this, x,y,n):
        curr = x%n #start off with x^1
        prod = 1 #the final product
        while(y > 0):
            if((y%2) == 1): #if the first bit is a 1
                prod = (prod * curr)%n #use that power of 2
            curr = (curr * curr)%n #increase to the next power of 2
            y = y//2 #shift y down by 1 bit
        return prod
    
    def __modInverse(this,a,b):
        #basically just do the extended euclid
        #format is (g,s,t) a*s + b*t = g = gcd(a,b)
        if b == 0:
            return (a,0,1)
        else:
            q = a // b
            r = a % b
            g, s, t = __invMod(b, r)
            return (g, t - s*q, s)
        

    def MillerRabin(this,n):
        # Determines if n is either composite or probably prime
        # the error probability is .25 so we will run it about run times
        # to get an error per centage of 2**-100
        runs = 50
        #input sanitization:
        if(n%2 == 0):
            return "composite" #for dumb people
        if(n <= 1):
            return "error"
        #n - 1 = m*(2^k) (while m is odd)
        k = 0
        m = n-1 
        while (m%2 == 0): #generate an m such that n -1 = m*(2^k) and m is odd
            k+=1
            m = m//2
        #choose ran int a so that 1 <= a <= n -1
        probability = 0
        for _ in range(runs): #run test many times
            a = secrets.randbelow(n-1)+1 #get a number from 1 to n-1
            #let b = a^m mod n
            b = this.modPow(a,m,n)
            if (b == 1):
                #probably prime so continue checking
                probability += 1
                continue
            for _ in range(k):
                if (b == n - 1):
                    probability += 1
                    break
                else:
                    b = this.modPow(b,2,n)
        if (probability == runs):
            return "prime"
        return "composite"


        



test = RSA()
#print(test.modPow(int(sys.argv[1]),int(sys.argv[2]),int(sys.argv[3])))
#print(pow(int(sys.argv[1]),int(sys.argv[2]),int(sys.argv[3])))
print(test.MillerRabin(int(sys.argv[1])))
