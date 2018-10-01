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



var bottlesOfBeer int = 0;

//func primeFac (bottlesOfBeer int){
//}

func takeOneBeer(ch chan bool) {
    bottlesOfBeer+= rand.Intn(10);
    go singTheSong(ch)
}

func singTheSong(ch chan bool) {
    if bottlesOfBeer < 100 {
        fmt.Printf("%d bugs in your code, %d bugs.\n", 
        bottlesOfBeer, bottlesOfBeer)
        fmt.Printf("Take one down and pass it around, %d bugs in your code.\n\n", bottlesOfBeer)
        go takeOneBeer(ch)
    } else if bottlesOfBeer == 1 {
        fmt.Println("1 bug in your code, 1 bug.")
        //fmt.Println("Take one down and pass it around, no more bottles of beer on the wall.\n")
        go takeOneBeer(ch)
    } else {
        //fmt.Println("No more bottles of beer on the wall, no more bottles of beer.")
        fmt.Println("Go to the store and buy some more beer, 100 bugs in your code.")
        ch <- true
    }
}

func main() {
    ch := make(chan bool)
    var upTo int
    //var err error
    fmt.Printf("How many lines? ")
    fmt.Scanf("%d", &upTo)
    go singTheSong(ch)
    <- ch
}
