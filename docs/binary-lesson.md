# Binary Lesson

This document was designed to explain the basics of Decimal (our number system),
Hexadecimal (base16, the ASM number system), and binary (machine code, 0's and
1's). Again, this is going to be very basic. Check the internet if you want to
learn more.

## Converting from Dec to Hex:
1. Divide the number by 16. The remainder is the first number. If it is 0 to 9,
just keep that. If it is 10 to 15, use letters A to F.

2. If the number is 16 or larger, still, divide by 16.
3. Repeat step 1 and 2 until finished.

Here is an example of 32173 converted to Hex:
```
32173/16= 2010 13/16  Remainder=13 “D”
2010/16= 125 10/16    Remainder=10 “A”
125/16= 7 13/16       Remainder=13 “D”
7/16= 7/16            Remainder=7  “7”
```
So the number is 7DADh

## Converting from Hex to Dec:
I will start this with an example of 731h:
```
1*16^0 = 1
3*16^1 = 48
7*16^2 = 1792
```
Add them all up to get 1841. Did you see the pattern with the 16<sup>n</sup>?

## Binary.
Converting to and from binary is pretty similar. Just replace all the 16's with 2's
and you will have it.

## Octal.
Replace all the 16's with 8's.

## Other Bases
Replace the 16's with whatever number you want.

Here is some cool knowledge for spriting. Each four binary digits represents one
hexadecimal digit. For example:
`00110101` corresponds to `35` in hexadecimal. This makes it super easy to convert a sprite which is
binary to hexadecimal! You only need the first 16 digits, so here you go:
```
0000 = 0 0100 = 4 1000 = 8 1100 = C
0001 = 1 0101 = 5 1001 = 9 1101 = D
0010 = 2 0110 = 6 1010 = A 1110 = E
0011 = 3 0111 = 7 1011 = B 1111 = F
```
