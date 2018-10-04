/*  The 99 Bottles of Beer in the Go Proramming Language
 *
 *  Marcos Vazquez
 *  mvazquez[at]tamps.cinvestav[dot]mx
 *  November 10, 2010
 *
 */

//SI413 Project 1 Bodeman, Sipes
//Resources: tour.golang.org/basics

package main

import "fmt"
import "math/rand"//https://gobyexample.com/random-numbers
import "strconv"
import "time"
import "os"
import "sync"


var randNum int;
var upTo int

/*
 * Takes an integer and produces its prime factorization.
 */
func primeFac (bottlesOfBeer int) string {
  var factors string = "("
  var i int
  var temp int = bottlesOfBeer
  i = 2
  for temp > 1 {
	//Finds the first i that the current number (starting at the total bottles of beer) 
	//is evenly divisible by and adds it to the string to be printed. 
    if temp % i == 0 {
      factors += strconv.Itoa(i)
	  //That factor has to be removed from the total so that the next factor can be found.
      temp = temp/i
      if temp > 1 {
		//Accounts for the final factor so an extra star is not printed at the end of the string.
        factors += "*"
      }
    }else{
      i++
    }
  }
  factors += ")"
  return factors
}

/*
 * Prints out the "99 bottles of beer" song using the indicated file descriptor.
 */
func singTheSong(fd *os.File) {
    var bottlesOfBeer int = 1;
    for bottlesOfBeer < upTo {
      var facBeer string = primeFac(bottlesOfBeer)
      if bottlesOfBeer == 1 {
        fmt.Fprintf(fd, "%s bug in your code, %s bug.\n\n", facBeer, facBeer);
        bottlesOfBeer += randNum;
      }else {
        fmt.Fprintf(fd, "%s bugs in your code, %s bugs.\n", facBeer, facBeer);
        fmt.Fprintf(fd, "Take one down and pass it around, %s bugs in your code.\n\n", facBeer);
        bottlesOfBeer += randNum;
      }
    }
    fmt.Fprintf(fd, "Go to the store and buy some more tequila, %s bugs in your code.\n", primeFac(upTo))
}

func main() {
	//Adds the current time as a seed for the random function
    rand.Seed(time.Now().UTC().UnixNano())//https://stackoverflow.com/questions/12321133/golang-random-number-generator-how-to-seed-properly
    randNum = rand.Intn(10);
    fmt.Printf("How many lines? ")
    fmt.Scanf("%d", &upTo)

	//Provides synchronization functions for go routines (threads).
    var wg sync.WaitGroup //https://www.ardanlabs.com/blog/2014/01/concurrency-goroutines-and-gomaxprocs.html
    //Indicates that there will be 2 threads that must be waited on. Sets the WaitGroup counter to 2.
	wg.Add(2)

	//Executes the encapsulated code as a seperate thread. 
    go func(){
	  //When the thread completes, decrements the WaitGroup counter by 1.
      defer wg.Done()

	  //Creates a file called out.txt for writing.	
      f, err := os.OpenFile("out.txt", os.O_CREATE | os.O_WRONLY | os.O_TRUNC, 0666 ) //https://stackoverflow.com/questions/29981050/concurrent-writing-to-a-file
      //Error checking for file creation.
	  if err != nil {
        panic(err)
      }
	  
	  //Prints the "99 Bottles of Beer" song to the file.
      singTheSong(f);
    }()

	//Executes the encapsulated code as a seperate thread. 
    go func(){
	  //When the thread completes, decrements the WaitGroup counter by 1.
      defer wg.Done()

	  //Prints the "99 Bottles of Beer" song to Standard Out.
      singTheSong(os.Stdout);
    }()

	//Waits until the WaitGroup counter is 0.
    wg.Wait()
}
