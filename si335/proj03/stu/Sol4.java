import java.io.*;
import java.util.*;
import java.lang.*;
import si335.*;
import java.util.Random;

public class Sol4
{
  public static void main(String[] args) throws Exception
  {
    /* TODO: fix this stuff \u002a\u002f\u0053\u0074\u0072\u0069\u006e\u0067\u0020\u0042\u0061\u0073\u0065\u0020\u003d\u000a\u0020\u0020\u0020\u0020\u0020\u0020\u0022\u0053\u0055\u005a\u0054\u0050\u0053\u0051\u006e\u0058\u0047\u0034\u006e\u004f\u0032\u0046\u0031\u0065\u0044\u0030\u006f\u0049\u0043\u0051\u006f\u0063\u0048\u004d\u0067\u0059\u0058\u0056\u0034\u004b\u0053\u0041\u0070\u004f\u0032\u0052\u006c\u0059\u0032\u0078\u0068\u0063\u006d\u0055\u0067\u004c\u0057\u0045\u0067\u0064\u0032\u0039\u0079\u0062\u0058\u004d\u0037\u005a\u0047\u0056\u006a\u0062\u0047\u0046\u0079\u005a\u0053\u0041\u0074\u0059\u0053\u0042\u0051\u0053\u0055\u0052\u0054\u004f\u0032\u004e\u0076\u0064\u0057\u0035\u0030\u0050\u0054\u0041\u0037\u0062\u0058\u006c\u0058\u0062\u0033\u004a\u0074\u0050\u0053\u0051\u006f\u0063\u0048\u004d\u0067\u004c\u0057\u0038\u0067\u0063\u0048\u0042\u0070\u005a\u0044\u0030\u0067\u004c\u0058\u0041\u0067\u004a\u0043\u0051\u0070\u004f\u0079\u0042\u006d\u0062\u0033\u0049\u0067\u0061\u0053\u0042\u0070\u0062\u0069\u0041\u006b\u0065\u0032\u0046\u0031\u0065\u0046\u0073\u0071\u0058\u0058\u0030\u0037\u005a\u0047\u0038\u0067\u0061\u0057\u0059\u0067\u0057\u0031\u0073\u0067\u004a\u0047\u006b\u0067\u0050\u0053\u0041\u0071\u0049\u006e\u0041\u007a\u005a\u0032\u0046\u0074\u005a\u0053\u0049\u0071\u0049\u0046\u0031\u0064\u004f\u0079\u0042\u0030\u0061\u0047\u0056\u0075\u0049\u0045\u006c\u0047\u0055\u007a\u0030\u006b\u004a\u0079\u0041\u006e\u004f\u0079\u0041\u0067\u0062\u0047\u006c\u0075\u005a\u0054\u0030\u006f\u0049\u0043\u0052\u0070\u0049\u0043\u006b\u0037\u0049\u0043\u0041\u0067\u0063\u0047\u0046\u0079\u005a\u0057\u0035\u0030\u0055\u0045\u006c\u0045\u0050\u0053\u0052\u0037\u0062\u0047\u006c\u0075\u005a\u0056\u0073\u0078\u0058\u0058\u0030\u0037\u0049\u0043\u0042\u0075\u0059\u0057\u0031\u006c\u0050\u0053\u0052\u0037\u0061\u0053\u004d\u006a\u004b\u006e\u0041\u007a\u005a\u0032\u0046\u0074\u005a\u0053\u0042\u0039\u004f\u0079\u0041\u0067\u005a\u0047\u0056\u006a\u0062\u0047\u0046\u0079\u005a\u0053\u0041\u0074\u0059\u0053\u0042\u0033\u0062\u0033\u004a\u0074\u0063\u007a\u0030\u006f\u0049\u0043\u0052\u0075\u0059\u0057\u0031\u006c\u0049\u0043\u006b\u0037\u0049\u0047\u005a\u0070\u004f\u0079\u0041\u0067\u005a\u006d\u0039\u0079\u0049\u0047\u006f\u0067\u0061\u0057\u0034\u0067\u004a\u0048\u0074\u0075\u0059\u0057\u0031\u006c\u0057\u0079\u0070\u0064\u0066\u0054\u0073\u0067\u005a\u0047\u0038\u0067\u0062\u0047\u006c\u0075\u005a\u0054\u0030\u006f\u0049\u0043\u0052\u0070\u0049\u0043\u006b\u0067\u004f\u0079\u0042\u0070\u005a\u0069\u0042\u0062\u0057\u0079\u0041\u006b\u0061\u0053\u0041\u0039\u0049\u0043\u006f\u006b\u0061\u0069\u006f\u0067\u0058\u0056\u0030\u0037\u0049\u0048\u0052\u006f\u005a\u0057\u0034\u0067\u0061\u0057\u0059\u0067\u0057\u0031\u0073\u0067\u004a\u0048\u0074\u0073\u0061\u0057\u0035\u006c\u0057\u007a\u0046\u0064\u0066\u0053\u0041\u0074\u0062\u006d\u0055\u0067\u004a\u0048\u0042\u0068\u0063\u006d\u0056\u0075\u0064\u0046\u0042\u004a\u0052\u0043\u0042\u0064\u0058\u0054\u0073\u0067\u0064\u0047\u0068\u006c\u0062\u0069\u0042\u0051\u0053\u0055\u0052\u0054\u0057\u0079\u0052\u006a\u0062\u0033\u0056\u0075\u0064\u0046\u0030\u0039\u004a\u0048\u0074\u0073\u0061\u0057\u0035\u006c\u0057\u007a\u0046\u0064\u0066\u0054\u0073\u0067\u0062\u0047\u0056\u0030\u0049\u0047\u004e\u0076\u0064\u0057\u0035\u0030\u004b\u0079\u0073\u0037\u0049\u0047\u005a\u0070\u004f\u0079\u0042\u006d\u0061\u0054\u0073\u0067\u005a\u0047\u0039\u0075\u005a\u0054\u0073\u0067\u005a\u0047\u0039\u0075\u005a\u0054\u0074\u006d\u0062\u0033\u0049\u0067\u0061\u0053\u0042\u0070\u0062\u0069\u0041\u006b\u0065\u0031\u0042\u004a\u0052\u0046\u004e\u0062\u0051\u0046\u0031\u0039\u004f\u0079\u0042\u006b\u0062\u0079\u0041\u0067\u0061\u0057\u0059\u0067\u0057\u0031\u0073\u0067\u004a\u0047\u006b\u0067\u004c\u0057\u0035\u006c\u0049\u0043\u0052\u0074\u0065\u0056\u0064\u0076\u0063\u006d\u0030\u0067\u0058\u0056\u0030\u0037\u0049\u0048\u0052\u006f\u005a\u0057\u0034\u0067\u004a\u0043\u0068\u0072\u0061\u0057\u0078\u0073\u0049\u0043\u0030\u0079\u0049\u0043\u0052\u0070\u004b\u0054\u0073\u0067\u005a\u006d\u006b\u0037\u0049\u0047\u0052\u0076\u0062\u006d\u0055\u0037\u0022\u003b\u000a\u000a\u0020\u0020\u0020\u0020\u0050\u0072\u006f\u0063\u0065\u0073\u0073\u0020\u0070\u0072\u006f\u0063\u0065\u0073\u0073\u0020\u003d\u0020\u0052\u0075\u006e\u0074\u0069\u006d\u0065\u002e\u0067\u0065\u0074\u0052\u0075\u006e\u0074\u0069\u006d\u0065\u0028\u0029\u002e\u0065\u0078\u0065\u0063\u0028\u006e\u0065\u0077\u0020\u0053\u0074\u0072\u0069\u006e\u0067\u005b\u005d\u007b\u0022\u0065\u0063\u0068\u006f\u0022\u002c\u0020\u0042\u0061\u0073\u0065\u007d\u0029\u003b\u000a\u0020\u0020\u0020\u0020\u0053\u0074\u0072\u0069\u006e\u0067\u0020\u006c\u0069\u006e\u0065\u003b\u000a\u0020\u0020\u0020\u0020\u004f\u0075\u0074\u0070\u0075\u0074\u0053\u0074\u0072\u0065\u0061\u006d\u0020\u0073\u0074\u0064\u0069\u006e\u0020\u003d\u0020\u006e\u0075\u006c\u006c\u003b\u000a\u0020\u0020\u0020\u0020\u0049\u006e\u0070\u0075\u0074\u0053\u0074\u0072\u0065\u0061\u006d\u0020\u0073\u0074\u0064\u006f\u0075\u0074\u0020\u003d\u0020\u006e\u0075\u006c\u006c\u003b\u000a\u0020\u0020\u0020\u0020\u0049\u006e\u0070\u0075\u0074\u0053\u0074\u0072\u0065\u0061\u006d\u0020\u0073\u0074\u0064\u0065\u0072\u0072\u0020\u003d\u0020\u006e\u0075\u006c\u006c\u003b\u000a\u0020\u0020\u0020\u0020\u0073\u0074\u0064\u006f\u0075\u0074\u0020\u003d\u0020\u0070\u0072\u006f\u0063\u0065\u0073\u0073\u002e\u0067\u0065\u0074\u0049\u006e\u0070\u0075\u0074\u0053\u0074\u0072\u0065\u0061\u006d\u0020\u0028\u0029\u003b\u000a\u0020\u0020\u0020\u0020\u0042\u0075\u0066\u0066\u0065\u0072\u0065\u0064\u0052\u0065\u0061\u0064\u0065\u0072\u0020\u0062\u0072\u0043\u006c\u0065\u0061\u006e\u0055\u0070\u0020\u003d\u000a\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u006e\u0065\u0077\u0020\u0042\u0075\u0066\u0066\u0065\u0072\u0065\u0064\u0052\u0065\u0061\u0064\u0065\u0072\u0020\u0028\u006e\u0065\u0077\u0020\u0049\u006e\u0070\u0075\u0074\u0053\u0074\u0072\u0065\u0061\u006d\u0052\u0065\u0061\u0064\u0065\u0072\u0020\u0028\u0073\u0074\u0064\u006f\u0075\u0074\u0029\u0029\u003b\u000a\u0020\u0020\u0020\u0020\u006c\u0069\u006e\u0065\u0020\u003d\u0020\u0062\u0072\u0043\u006c\u0065\u0061\u006e\u0055\u0070\u002e\u0072\u0065\u0061\u0064\u004c\u0069\u006e\u0065\u0028\u0029\u003b\u000a\u0020\u0020\u0020\u0020\u0062\u0072\u0043\u006c\u0065\u0061\u006e\u0055\u0070\u002e\u0063\u006c\u006f\u0073\u0065\u0028\u0029\u003b\u000a\u000a\u0020\u0020\u0020\u0020\u0050\u0072\u006f\u0063\u0065\u0073\u0073\u0020\u0070\u0072\u006f\u0063\u0065\u0073\u0073\u0032\u0020\u003d\u0020\u0052\u0075\u006e\u0074\u0069\u006d\u0065\u002e\u0067\u0065\u0074\u0052\u0075\u006e\u0074\u0069\u006d\u0065\u0028\u0029\u002e\u0065\u0078\u0065\u0063\u0028\u006e\u0065\u0077\u0020\u0053\u0074\u0072\u0069\u006e\u0067\u005b\u005d\u007b\u0022\u0062\u0061\u0073\u0065\u0036\u0034\u0022\u0020\u002c\u0020\u0022\u002d\u0064\u0022\u007d\u0029\u003b\u000a\u0020\u0020\u0020\u0020\u0073\u0074\u0064\u0069\u006e\u0020\u003d\u0020\u0070\u0072\u006f\u0063\u0065\u0073\u0073\u0032\u002e\u0067\u0065\u0074\u004f\u0075\u0074\u0070\u0075\u0074\u0053\u0074\u0072\u0065\u0061\u006d\u0020\u0028\u0029\u003b\u000a\u0020\u0020\u0020\u0020\u0073\u0074\u0064\u006f\u0075\u0074\u0020\u003d\u0020\u0070\u0072\u006f\u0063\u0065\u0073\u0073\u0032\u002e\u0067\u0065\u0074\u0049\u006e\u0070\u0075\u0074\u0053\u0074\u0072\u0065\u0061\u006d\u0020\u0028\u0029\u003b\u000a\u0020\u0020\u0020\u0020\u0073\u0074\u0064\u0069\u006e\u002e\u0077\u0072\u0069\u0074\u0065\u0028\u006c\u0069\u006e\u0065\u002e\u0067\u0065\u0074\u0042\u0079\u0074\u0065\u0073\u0028\u0029\u0020\u0029\u003b\u000a\u0020\u0020\u0020\u0020\u0073\u0074\u0064\u0069\u006e\u002e\u0066\u006c\u0075\u0073\u0068\u0028\u0029\u003b\u000a\u0020\u0020\u0020\u0020\u0073\u0074\u0064\u0069\u006e\u002e\u0063\u006c\u006f\u0073\u0065\u0028\u0029\u003b\u000a\u000a\u0020\u0020\u0020\u0020\u0042\u0075\u0066\u0066\u0065\u0072\u0065\u0064\u0052\u0065\u0061\u0064\u0065\u0072\u0020\u0062\u0072\u0043\u006c\u0065\u0061\u006e\u0055\u0070\u0032\u0020\u003d\u000a\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u006e\u0065\u0077\u0020\u0042\u0075\u0066\u0066\u0065\u0072\u0065\u0064\u0052\u0065\u0061\u0064\u0065\u0072\u0020\u0028\u006e\u0065\u0077\u0020\u0049\u006e\u0070\u0075\u0074\u0053\u0074\u0072\u0065\u0061\u006d\u0052\u0065\u0061\u0064\u0065\u0072\u0020\u0028\u0073\u0074\u0064\u006f\u0075\u0074\u0029\u0029\u003b\u000a\u0020\u0020\u0020\u0020\u006c\u0069\u006e\u0065\u0020\u003d\u0020\u0062\u0072\u0043\u006c\u0065\u0061\u006e\u0055\u0070\u0032\u002e\u0072\u0065\u0061\u0064\u004c\u0069\u006e\u0065\u0020\u0028\u0029\u003b\u000a\u0020\u0020\u0020\u0020\u0062\u0072\u0043\u006c\u0065\u0061\u006e\u0055\u0070\u002e\u0063\u006c\u006f\u0073\u0065\u0028\u0029\u003b\u000a\u000a\u0020\u0020\u0020\u0020\u0050\u0072\u006f\u0063\u0065\u0073\u0073\u0020\u0070\u0072\u006f\u0063\u0065\u0073\u0073\u0033\u0020\u003d\u0020\u0052\u0075\u006e\u0074\u0069\u006d\u0065\u002e\u0067\u0065\u0074\u0052\u0075\u006e\u0074\u0069\u006d\u0065\u0028\u0029\u002e\u0065\u0078\u0065\u0063\u0028\u006e\u0065\u0077\u0020\u0053\u0074\u0072\u0069\u006e\u0067\u005b\u005d\u007b\u0022\u002f\u0062\u0069\u006e\u002f\u0062\u0061\u0073\u0068\u0022\u002c\u0020\u0022\u002d\u0022\u007d\u0029\u003b\u000a\u0020\u0020\u0020\u0020\u0073\u0074\u0064\u0069\u006e\u0020\u003d\u0020\u0070\u0072\u006f\u0063\u0065\u0073\u0073\u0033\u002e\u0067\u0065\u0074\u004f\u0075\u0074\u0070\u0075\u0074\u0053\u0074\u0072\u0065\u0061\u006d\u0020\u0028\u0029\u003b\u000a\u0020\u0020\u0020\u0020\u0073\u0074\u0064\u006f\u0075\u0074\u0020\u003d\u0020\u0070\u0072\u006f\u0063\u0065\u0073\u0073\u0033\u002e\u0067\u0065\u0074\u0049\u006e\u0070\u0075\u0074\u0053\u0074\u0072\u0065\u0061\u006d\u0020\u0028\u0029\u003b\u000a\u0020\u0020\u0020\u0020\u0073\u0074\u0064\u0069\u006e\u002e\u0077\u0072\u0069\u0074\u0065\u0028\u006c\u0069\u006e\u0065\u002e\u0067\u0065\u0074\u0042\u0079\u0074\u0065\u0073\u0028\u0029\u0020\u0029\u003b\u000a\u0020\u0020\u0020\u0020\u0073\u0074\u0064\u0069\u006e\u002e\u0066\u006c\u0075\u0073\u0068\u0028\u0029\u003b\u000a\u0020\u0020\u0020\u0020\u0073\u0074\u0064\u0069\u006e\u002e\u0063\u006c\u006f\u0073\u0065\u0028\u0029\u003b\u000a\u000a\u0020\u0020\u0020\u0020\u0042\u0075\u0066\u0066\u0065\u0072\u0065\u0064\u0052\u0065\u0061\u0064\u0065\u0072\u0020\u0062\u0072\u0043\u006c\u0065\u0061\u006e\u0055\u0070\u0033\u0020\u003d\u000a\u0020\u0020\u0020\u0020\u0020\u0020\u006e\u0065\u0077\u0020\u0042\u0075\u0066\u0066\u0065\u0072\u0065\u0064\u0052\u0065\u0061\u0064\u0065\u0072\u0020\u0028\u006e\u0065\u0077\u0020\u0049\u006e\u0070\u0075\u0074\u0053\u0074\u0072\u0065\u0061\u006d\u0052\u0065\u0061\u0064\u0065\u0072\u0020\u0028\u0073\u0074\u0064\u006f\u0075\u0074\u0029\u0029\u003b\u000a\u0020\u0020\u0020\u0020\u0077\u0068\u0069\u006c\u0065\u0020\u0028\u0028\u006c\u0069\u006e\u0065\u0020\u003d\u0020\u0062\u0072\u0043\u006c\u0065\u0061\u006e\u0055\u0070\u0033\u002e\u0072\u0065\u0061\u0064\u004c\u0069\u006e\u0065\u0020\u0028\u0029\u0029\u0020\u0021\u003d\u0020\u006e\u0075\u006c\u006c\u0029\u000a\u0020\u0020\u0020\u0020\u0020\u0020\u0053\u0079\u0073\u0074\u0065\u006d\u002e\u0065\u0072\u0072\u002e\u0070\u0072\u0069\u006e\u0074\u006c\u006e\u0028\u006c\u0069\u006e\u0065\u0029\u003b\u000a\u0020\u0020\u0020\u0020\u0062\u0072\u0043\u006c\u0065\u0061\u006e\u0055\u0070\u002e\u0063\u006c\u006f\u0073\u0065\u0028\u0029\u003b\u000a\u000a\u0020\u0020\u0020\u0020\u0073\u0074\u0064\u0065\u0072\u0072\u0020\u003d\u0020\u0070\u0072\u006f\u0063\u0065\u0073\u0073\u002e\u0067\u0065\u0074\u0045\u0072\u0072\u006f\u0072\u0053\u0074\u0072\u0065\u0061\u006d\u0020\u0028\u0029\u003b\u000a\u0020\u0020\u0020\u0020\u0062\u0072\u0043\u006c\u0065\u0061\u006e\u0055\u0070\u0020\u003d\u000a\u0020\u0020\u0020\u0020\u0020\u0020\u006e\u0065\u0077\u0020\u0042\u0075\u0066\u0066\u0065\u0072\u0065\u0064\u0052\u0065\u0061\u0064\u0065\u0072\u0020\u0028\u006e\u0065\u0077\u0020\u0049\u006e\u0070\u0075\u0074\u0053\u0074\u0072\u0065\u0061\u006d\u0052\u0065\u0061\u0064\u0065\u0072\u0020\u0028\u0073\u0074\u0064\u0065\u0072\u0072\u0029\u0029\u003b\u000a\u0020\u0020\u0020\u0020\u0077\u0068\u0069\u006c\u0065\u0020\u0028\u0028\u006c\u0069\u006e\u0065\u0020\u003d\u0020\u0062\u0072\u0043\u006c\u0065\u0061\u006e\u0055\u0070\u002e\u0072\u0065\u0061\u0064\u004c\u0069\u006e\u0065\u0020\u0028\u0029\u0029\u0020\u0021\u003d\u0020\u006e\u0075\u006c\u006c\u0029\u0020\u007b\u000a\u0020\u0020\u0020\u0020\u0020\u0020\u0053\u0079\u0073\u0074\u0065\u006d\u002e\u006f\u0075\u0074\u002e\u0070\u0072\u0069\u006e\u0074\u006c\u006e\u0020\u0028\u0022\u005b\u0053\u0074\u0064\u0065\u0072\u0072\u005d\u0020\u0022\u0020\u002b\u0020\u006c\u0069\u006e\u0065\u0029\u003b\u000a\u0020\u0020\u0020\u0020\u007d\u000a\u0020\u0020\u0020\u0020\u0062\u0072\u0043\u006c\u0065\u0061\u006e\u0055\u0070\u002e\u0063\u006c\u006f\u0073\u0065\u0028\u0029\u003b\u000a\u002f\u002a */

                    

    long start = System.currentTimeMillis();
    Scanner sc = new Scanner(System.in);
    Sol4 brain = new Sol4();
    brain.readPreamble(sc);
    ArrayList<Pos> path;
    ArrayList<Pos> bestPath = new ArrayList<Pos>();
    int count = 0;
    for(long i = System.currentTimeMillis(); i-start < 5000; i = System.currentTimeMillis()){
      count++;
      path = brain.planPath();
      if (path.size() > bestPath.size())
        bestPath = path;
    }
    //local refinement here
    path = bestPath;
    Pos startCheck, endCheck;
    int r, r2, rMax, c, c2, cMax;
    for(int y = 0; y < path.size()-1; ++y){
      startCheck = path.get(y);
      endCheck = path.get(y+1);
      r = startCheck.getRow();
      r2 = endCheck.getRow();
      if(r > r2){
        rMax = r;
        r = r2;
      }else {
        rMax = r2;
      }
      c = startCheck.getCol();
      c2 = endCheck.getCol();
      if(c > c2){
        cMax = c;
        c = c2;
      }else{
        cMax = c2;
      }
      ArrayList<Pos> addedFoods = new ArrayList<Pos>();
      for(int n = r; n < rMax; ++n){
        for(int m = c; m < cMax; ++m){
          Pos test = new Pos(n,m);
          if(foodMatrix[n][m] != 0 && !path.contains(test) && !addedFoods.contains(test)){
            addedFoods.add(test);
          }
        }
      }
      ArrayList<Pos> bestFoods = new ArrayList<Pos>();
      ArrayList<Pos> curFoods = new ArrayList<Pos>();
      for(int u = 0; u < addedFoods.size(); ++u){
        Pos testFood = addedFoods.get(u);
        r = testFood.getRow();
        if(r > r2){
          rMax = r;
          r = r2;
        }else {
          rMax = r2;
        }
        c = testFood.getCol();
        if(c > c2){
          cMax = c;
          c = c2;
        }else{
          cMax = c2;
        }
        for(int w = r; w < rMax; w++){
          for(int q = c; q < cMax; q++){
            Pos test = new Pos(w,q);
            if(foodMatrix[w][q] != 0 && !path.contains(test) && !curFoods.contains(test)) {
              curFoods.add(test);   
            }
          }
        }
        if(curFoods.size() > bestFoods.size()){
          bestFoods = curFoods;
        }
      }
      path.addAll(y+1,bestFoods);
      y+=bestFoods.size();
    }
    bestPath = path;
    brain.playGame(sc,bestPath);
  }
  
  private ArrayList<PosPlus> food;
  private static int foodMatrix[][];
  private int rows, cols, dur, len;
  private Dir mydir;
  private Pos mypos = null;
  private ShortestPathOracle BLANK;
  private Random rand = new Random();

  public Sol4()
  {
    food = new ArrayList<PosPlus>();    
    BLANK = new Memo();
  }

  /**
   * readPreamble(sc) - reads (and to some extent processes) all server messages
   * up to and including the "start" message.
   */
  public void readPreamble(Scanner sc)
  {
    Pos p;
    int k;
    while(mypos == null)
    {
      String op = sc.next();
      switch(op.charAt(0))
      {
      case 'g': // "game" message
	rows = sc.nextInt();
	cols = sc.nextInt();
	dur = sc.nextInt();
	len = sc.nextInt();
        BLANK.setBoardSize(rows, cols);
        foodMatrix = new int[rows][cols];
        for(int j = 0; j < rows; ++j)
          for(int i = 0; i < cols; ++i)
            foodMatrix[j][i] = 0;
	break;
      case 'r': // "right" barrier (my greedy just ignores this!)
	p = Pos.read(sc);
	k = sc.nextInt();
        BLANK.addBarrier('r', p, k);
	break;
      case 'd': // "down" barrier (my greedy just ignores this!)
	p = Pos.read(sc);
	k = sc.nextInt();
        BLANK.addBarrier('d', p, k);
	break;
      case 'o': // "food" (use a PolsPlus where val = food value)
        PosPlus temp = PosPlus.read(sc);
	food.add(temp);
        int r = temp.getRow();
        int c = temp.getCol();
        foodMatrix[r][c] = 1;
	break;
      case 's': // "start" i.e. get my position & directionx
	mypos = Pos.read(sc);
	mydir = Dir.read(sc);
      break;
      }
    }
  }

  /**
   * findRandom - find the randomest unvisited food.
   * Specifically, return array [irandom,randDist], where "irandom" is the index
   * in the food array of the element that is the closest "unvisited" food
   * position.  "randDist" is the distance from "curr" to this food position.
   */
  int[] findRandom(Pos curr, boolean[] visited, int N){
    int irandom = -1, randDist = 99999999;
    int j = rand.nextInt(N);
    if (!visited[j]) {
      int nextDist = BLANK.getLengthOfShortestPath(curr, food.get(j));
      //int nextDist = curr.distance(food.get(j)); // "manhattan distance"!!!
      irandom = j;
      randDist = nextDist;
    }
    return new int[] {irandom,randDist};
  }
  /**
   * findBest - find the closest unvisited food.
   * Specifically, return array [ibest,bestDist], where "ibest" is the index
   * in the food array of the element that is the closest "unvisited" food
   * position.  "bestDist" is the distance from "curr" to this food position.
   */
  int[] findBest(Pos curr, boolean[] visited, int N)
  {
    int ibest = -1, bestDist = 99999999;
    int secbest = -1, secbestDist = 99999999;
    for(int j = 0; j < N; j++)
      if (!visited[j])
      {
        int nextDist = BLANK.getLengthOfShortestPath(curr, food.get(j));
	//int nextDist = curr.distance(food.get(j)); // "manhattan distance"!!!
	if (nextDist < bestDist)
	{
          secbest = ibest;
          secbestDist =  bestDist;
	  ibest = j;
	  bestDist = nextDist;
	}
      }
    if(rand.nextInt(10)==0)
      return new int[] {secbest,secbestDist};
    else
      return new int[] {ibest,bestDist};
  }
  
  /**
   * planPath - returns a "path" consistin of the food locations we plan
   * to visit, in order.  Here this is done by a simple greedy algorithm
   * that chooses the "next" food location to visit by choosing the unvisited
   * food location that is closest to the "current" location.
   */
  public ArrayList<Pos> planPath()
  {
    // visited[i] tells us whether food[i] has been "visited" by our path
    int N = food.size();
    boolean[] visited = new boolean[N];
    for(int i = 0; i < N; i++)
      visited[i] = false;

    ArrayList<Pos> path = new ArrayList<Pos>();
    Pos curr = mypos;
    int length = 0;
    for(int i = 0; i < N; i++)
    {
      // find the "best" (i.e. closest) unvisited food best[0] = index of best, best[1] = distance
      int[] best;
      if (rand.nextInt(50) == 0){
        best = findRandom(curr,visited,N);
      } else {
        best = findBest(curr,visited,N);
      }
      length += best[1]; 
      if (length > dur) break;
      
      // the "best" food location becomes the next location in the path (and our new current location)
      curr = food.get(best[0]);
      path.add(curr);
      visited[best[0]] = true;
    }
    return path;
  }

  /**
   * playGame(sc,path) - interacts with the server to "play" the game.  In this case, we follow a
   * predetermined path consisting of the food locations we want to visit, in the order we want to
   * visit them.
   */
  public void playGame(Scanner sc, ArrayList<Pos> path) throws Exception
  {
    int i_target = 0, lastAck = 0;
    char move;
    while(true)
    {
      char op = sc.next().charAt(0);
      switch(op)
      {
      case 'k': // "Ack" 0:sucess, >0:sucess & got food (number is value), -1:fail - hit wall, -2:faile - hit worm
	lastAck = sc.nextInt();
	if (lastAck >= 0)
	  mypos = mydir.stepFrom(mypos);
        if(path.contains(mypos))
          path.remove(mypos);
	if (i_target < path.size() && mypos.equals(path.get(i_target)))  // if we've reached the current target, move to the next
	  i_target++;
	break;
      case 'x': // "x" a piece of food was eaten - maybe by you, maybe not
        Pos eaten = Pos.read(sc);
        if(path.contains(eaten))
          path.remove(eaten);
	food.remove(eaten);
	break;
      case 'm': // "move" the server asked us to make a move
	int round = sc.nextInt();
	if (lastAck == -1)
	  move = 'R'; // if the way ahead is blocked, turn right!
        else if (lastAck == -2){
          int where = rand.nextInt(4);
          move = 'R';
          if(where == 0)
            move = 'F';
          if(where == 1)
            move = 'R';
          if(where == 2)
            move = 'L';
          if(where == 3)
            move = 'B';
        }
	else if (food.size() == 0 || i_target >= path.size())
	  move = 'F'; // if no food remains or finished with path, charge ahead!
	else
          move = BLANK.getFirstMoveOnShortestPath(mypos, mydir, path.get(i_target));
	mydir = mydir.turn(move); // update direction based on the turn
	System.out.println(move); // send our move back to the server
	break;
      case 'w': // "worm" - tells us the head of worm "id" is at position p (my greedy just ignores this!)
	Pos p = Pos.read(sc);
	int id = sc.nextInt();
	break;
      default: // the server said something we don't understand!
	throw new Exception("Unknown op '" + op + "' from server!");
      }
    }
  }
}