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

func primeFac (bottlesOfBeer int) string {
  var factors string = "("
  var i int
  var temp int = bottlesOfBeer
  i = 2
  for temp > 1 {
    if temp % i == 0 {
      factors += strconv.Itoa(i)
      temp = temp/i
      if temp > 1 {
        factors += "*"
      }
    }else{
      i++
    }
  }
  factors += ")"
  return factors
}

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
    rand.Seed(time.Now().UTC().UnixNano())//https://stackoverflow.com/questions/12321133/golang-random-number-generator-how-to-seed-properly
    randNum = rand.Intn(10);
    fmt.Printf("How many lines? ")
    fmt.Scanf("%d", &upTo)

    var wg sync.WaitGroup //https://www.ardanlabs.com/blog/2014/01/concurrency-goroutines-and-gomaxprocs.html
    wg.Add(2)

    go func(){
      defer wg.Done()

      f, err := os.OpenFile("out.txt", os.O_CREATE | os.O_WRONLY | os.O_TRUNC, 0666 ) //https://stackoverflow.com/questions/29981050/concurrent-writing-to-a-file
      if err != nil {
        panic(err)
      }
      singTheSong(f);
    }()

    go func(){
      defer wg.Done()

      singTheSong(os.Stdout);
    }()

    wg.Wait()
}
