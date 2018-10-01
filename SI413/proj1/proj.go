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


//fmt.Scanf("%s", &ln)

var bottlesOfBeer int = 0;

func takeOneBeer(ch chan bool) {
    bottlesOfBeer+= rand.Intn(10);
    go singTheSong(ch)
}

func singTheSong(ch chan bool) {
    if bottlesOfBeer < 100 {
        fmt.Printf("%d bottles of beer on the wall, %d bottles of beer.\n", 
        bottlesOfBeer, bottlesOfBeer)
        fmt.Println("Take one down and pass it around, %d bottles of beer on the wall.\n", bottlesOfBeer)
        go takeOneBeer(ch)
    } else if bottlesOfBeer == 1 {
        fmt.Println("1 bottle of beer on the wall, 1 bottle of beer.")
        fmt.Println("Take one down and pass it around, no more bottles of beer on the wall.\n")
        go takeOneBeer(ch)
    } else {
        //fmt.Println("No more bottles of beer on the wall, no more bottles of beer.")
        fmt.Println("Go to the store and buy some more, 100 bottles of beer on the wall.")
        ch <- true
    }
}

func main() {
    ch := make(chan bool)
    go singTheSong(ch)
    <- ch
}
