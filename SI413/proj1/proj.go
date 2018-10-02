/*  The 99 Bottles of Beer in the Go Proramming Language
 *
 *  Marcos Vazquez
 *  mvazquez[at]tamps.cinvestav[dot]mx
 *  November 10, 2010
 *
 */

package main

import "fmt"
import "math/rand"//https://gobyexample.com/random-numbers
import "strconv"
import "time"


var bottlesOfBeer int = 1;
var randNum int;

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
  //fmt.Printf("%s\n", factors)
  return factors
}

func takeOneBeer(ch chan bool, upTo int) {
    bottlesOfBeer+= randNum;
    go singTheSong(ch, upTo)
}

func singTheSong(ch chan bool, upTo int) {
    var facBeer string = primeFac(bottlesOfBeer)
    //fmt.Printf("%s\n", facBeer)
    if bottlesOfBeer < upTo {
        fmt.Printf("%s bugs in your code, %s bugs.\n", facBeer, facBeer);
        fmt.Printf("Take one down and pass it around, %s bugs in your code.\n\n", facBeer);
        go takeOneBeer(ch, upTo)
    } else if bottlesOfBeer == 1 {
        fmt.Printf("%s bug in your code, %s bug.", facBeer, facBeer);
        //fmt.Println("Take one down and pass it around, no more bottles of beer on the wall.\n")
        go takeOneBeer(ch, upTo)
    } else {
        //fmt.Println("No more bottles of beer on the wall, no more bottles of beer.")
        fmt.Printf("Go to the store and buy some more tequila, %s bugs in your code.\n", primeFac(upTo))
        ch <- true
    }
}

func main() {
    rand.Seed(time.Now().UTC().UnixNano())//https://stackoverflow.com/questions/12321133/golang-random-number-generator-how-to-seed-properly
    randNum = rand.Intn(10);
    ch := make(chan bool)
    var upTo int
    fmt.Printf("How many lines? ")
    fmt.Scanf("%d", &upTo)
    go singTheSong(ch, upTo)
    <- ch
}
