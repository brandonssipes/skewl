I created a built-in chr similar to python where you can do chr@65 
and it will print out 'A'.  It converts a number to the ascii value 
representation of it.  I was going to have it be returned as all our
other built-ins did but Value did not support the use of characters.  I
considered changing Value so that it would be able to return characters
but I do not really have the time right now on the chance that it breaks
and i have to start debugging it.
