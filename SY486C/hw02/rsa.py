#####################################
#### Brandon Sipes RSA TOOL##########
#### created February 23, 2019#######
#### last updated February 23, 2019##
#####################################

import sys

class RSA:
    def modPow(this,x,y,n):
        if (y >= 0):
            return this.__modPow(x,y,n)
        elif (y == -1):
            try:
                g, a, _ = this.__invMod(x,n)
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
            y = y/2 #shift y down by 1 bit
        return prod
    
    def __invMod(this,a,b):
        #basically just do the extended euclid
        #format is (g,s,t) a*s + b*t = g = gcd(a,b)
        if b == 0:
            return (a,0,1)
        else:
            q = a // b
            r = a % b
            g, s, t = __invMod(b, r)
            return (g, t - s*q, s)
        
        



test = RSA()
print(test.modPow(int(sys.argv[1]),int(sys.argv[2]),int(sys.argv[3])))
print(pow(int(sys.argv[1]),int(sys.argv[2]),int(sys.argv[3])))
