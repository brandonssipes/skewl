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
//import "strings"//https://golang.org/pkg/strings/


var bottlesOfBeer int = 0;

func primeFac (bottlesOfBeer int){

}

func takeOneBeer(ch chan bool, upTo int) {
    bottlesOfBeer+= rand.Intn(10);
    go singTheSong(ch, upTo)
}

func singTheSong(ch chan bool, upTo int) {
    var facBeer = primeFac(bottlesOfBeer)
    if bottlesOfBeer < upTo {
        fmt.Printf("%d bugs in your code, %d bugs.\n", 
        bottlesOfBeer, bottlesOfBeer)
        fmt.Printf("Take one down and pass it around, %d bugs in your code.\n\n", bottlesOfBeer)
        go takeOneBeer(ch, upTo)
    } else if bottlesOfBeer == 1 {
        fmt.Println("1 bug in your code, 1 bug.")
        //fmt.Println("Take one down and pass it around, no more bottles of beer on the wall.\n")
        go takeOneBeer(ch, upTo)
    } else {
        //fmt.Println("No more bottles of beer on the wall, no more bottles of beer.")
        fmt.Printf("Go to the store and buy some more tequila, %d bugs in your code.\n", upTo)
        ch <- true
    }
}

func main() {
    ch := make(chan bool)
    var upTo int
    fmt.Printf("How many lines? ")
    fmt.Scanf("%d", &upTo)
    go singTheSong(ch, upTo)
    <- ch
}
