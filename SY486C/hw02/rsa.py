#####################################
#### Brandon Sipes RSA TOOL##########
#### created February 23, 2019#######
#### last updated March 1, 2019######
#####################################

import sys
if sys.version_info[0] < 3:
    raise Exception("Must be using Python 3")
import secrets

class RSA:
    def modPow(this,x,y,n):
        if (y >= 0):
            return this.__modPow(x,y,n)
        elif (y == -1):
            g, a, p = this.__modInverse(x,n)
            if g == 1:
                return p % n
            else:
                return -1

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
            g, s, t = this.__modInverse(b, r)
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

    def Encrypt(this,m,e,n):
        return this.modPow(m,e,n)
    def Decrypt(this,c,d,n):
        return this.modPow(c,d,n)

    def KeyGen(this, y):
        p = secrets.randbits(y)
        while(this.MillerRabin(p) == "composite"):
            p = secrets.randbits(y)
        q = secrets.randbits(y)
        while(this.MillerRabin(q) == "composite"):
            q = secrets.randbits(y)
        n = p*q
        phi = (p-1)*(q-1) 
        e = 65537
        if (e >= phi): #e has to be less than phi which if phi is less than 65537
            e = 3      # then the security of e = 3 isn't the concern
        d = this.modPow(e,-1,phi)
        if(d == -1): #There is no inverse for d
            n,e,d = this.KeyGen(y)
        return n,e,d




        


test = RSA()
#print(test.modPow(int(sys.argv[1]),int(sys.argv[2]),int(sys.argv[3])))
#print(pow(int(sys.argv[1]),int(sys.argv[2]),int(sys.argv[3])))
#print(test.MillerRabin(int(sys.argv[1])))
#print(test.KeyGen(int(sys.argv[1])))
print(test.Decrypt(2790,413,3233))
