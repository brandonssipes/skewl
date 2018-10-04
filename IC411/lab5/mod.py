#!/usr/bin/env python

#Brandon Sipes lab 5


def main():
    fd = open("numbers.txt" , "r") #open as read the input file

    mod1 = open("mod1.txt", "w+") #open and create the output files 
    mod2 = open("mod2.txt", "w+")
    mod0 = open("mod0.txt", "w+")

    for i in fd: #go line by line
        mod = int(i)%3 #mod by 3
        if(mod == 0): 
            mod0.write(i) #add to whichever file it goes into
        elif (mod == 1):
            mod1.write(i)
        else:
            mod2.write(i)

    mod0.close()
    mod1.close()
    mod2.close()
    fd.close()

if __name__== "__main__": #call main
    main()
