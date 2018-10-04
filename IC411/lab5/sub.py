#!/usr/bin/env python

#Brandon Sipes lab 5

def main():
    fd = open("letters.txt", "r") #open input file

    navy = open("navy.txt", "w+") #open output file and create if not exist

    for i in fd:
        n = i.find('N') #find first occurance of each letter
        a = i[n:].find('A') + n #starting at occurance of prev letter
        v = i[a:].find('V') + a #add back the offset
        y = i[v:].find('Y') + v
        if n >= 0 and a-n >= 0 and v-a >= 0 and y-v >= 0: #subtract offset to look for -1
            i = i.replace('N', 'n') #replace all occurances
            i = i.replace('A', 'a')
            i = i.replace('V', 'v')
            i = i.replace('Y', 'y')
            navy.write(i)

    navy.close() #close files
    fd.close()




if __name__=="__main__":
    main()
