# Grammer Math

Grammer uses 16-bit math. If you are not familiar with what this means, please look at the [Number System](#number-system) section.

Much of Grammer is numbers and math. For example, when you do something like `"HELLO WORLD→A`, this isn't storing the string anywhere, it is actually storing the location of the string as a 16-bit number. If you don't know what pointers are, you should read the [Pointers](readme.md#pointers) section.

## Math

Grammer math is very different from the math that you are used to. The main
points are:
* Math is done right to left
* All functions in Grammer are math.

For the first point, let's look at an example of the math string 3+9/58-3\*14+2\*2:
```
3+9/58-3*14+2*2
3+9/58-3*14+4
3+9/58-3*18
3+9/58-54
3+9/4
3+2
5
```
Parentheses are not part of Grammer math, but to give you you can use a space or use a colon between chunks of math to compute
each chunk in order. In most situations, you should use a colon. So say you want to
do ((3+4)*(6+3))/6. You have 3 chunks that you can compute in order:
```
3+4:*6+3:/6
7:*6+3:/6
7*6+3:/6
7*9:/6
63:/6
63/6
10
```
Pretty cool, right? That is actually even more optimized than using parentheses! Now, if you are like me, you might not like the look of that missing remainder of 3 in that division. 63/6 is 10.5, not 10, but Grammer truncates the results. However, a system variable called θ' will contain the remainder after division and other such extra information after math.

Here are the math operations currently available.

| Example | Token | Grammer | Description                                      |
|:------- |:----- |:------- |:------------------------------------------------ |
| a+b     | +     | +       | Adds two numbers. If there is overflow, θ'=1, else it is 0.|
| a-b     | -     | -       | Subtracts two numbers. If there is overflow, θ'=65535, else it is zero |
| a*b     | *     | *       | Multiplies two numbers. Overflow is stored in θ' |
| a/b     | /     | /       | Divides two numbers. The remainder is stored in θ'. |
| a/ b    | `/ `  | `/ `    | Divides two __signed__ numbers. Ex. `65533/ 65535` returns `3` since this is equivalent to `-3/-1`. |
| a<sup>2</sup> | <sup>2</sup> | <sup>2</sup> | This squares a number. Overflow is stored in θ'. |
| -a      | (-)   | (-)     | Negates a number. |
| min(a,b | min(  | min(    | Returns the minimum of two numbers. |
| max(a,b | max(  | max(    | Returns the maximum of two numbers. |
| sin(a   | sin(  | sin(    | This returns the sine of a number as a value between -128 and 127. The period is 256, not 360. For example, sin(32) is like sin(45) in normal math. If you need help, take the actual sin(45) and multiply by 128. Rounded, this is 91. So, sin(32)=91. |
| cos(a   | cos(  | cos(    | This calculates cosine. See notes on sine. |
| e^(a    | e^(   | 2^(     | Computes a power of 2. |
| gcd(a,b | gcd(  | gcd(    | Returns the greatest common divisor of two numbers. |
| lcm(a,b | lcm(  | lcm(    | Returns the least common multiple of two numbers. |
| a▶Frac  | ▶Frac | ▶lFactor | θ' contains the smallest factor of the number. Output is a divided by that number. For example, 96▶Frac will output 48 with θ'=2. You can use this to test primality. |
| √(a     | √(    | √(a     | Returns the square root of the number, rounded down. θ' contains a remainder. |
| √('a    | √('   | √('     | Returns the square root rounded to the nearest integer. |
| abs(a   | abs(  | abs(    | Returns the absolute value of a number. If a>32767, it is treated as negative. |
| rand    | rand  | rand    | Returns a random integer between 0 and 65535. |
| randInt(a,b | randInt( | randInt( | Returns a random integer between `a` and `b-1`. |
| ~~a nCr b~~ | ~~nCr~~ | ~~nCr~~ | ~~Returns `a` choose `b`. In mathematics, this is typically seen as n!/((n-r)!r!). I had to invent an algorithm for this to avoid factorials because otherwise, you could not do anything like 9 nCr 7 (9!>65535).~~|
| !a      | !     | !       | If the following expression results in 0, this returns 1, else it returns 0. |
| a and b | and   | and     | Computes bit-wise AND of two values. Remember the [Binary Lesson](binary-lesson.md) ? |
| a or b  | or    | or      | Computes bit-wise OR of two values. |
| a xor b | xor   | xor     | Computes bit-wise XOR of two values. |
| not(a   | not(  | not(    | Inverts the bits of a number. |
| a=b     | =     | =       | If a and b are equal, this returns 1, else it returns 0. |
| a≠b     | ≠     | ≠       | If a and b are not equal, this returns 1, else it returns 0. |
| a>b     | >     | >       | If a is greater than b, this returns 1, else it returns 0. |
| a≥b     | ≥     | ≥       | If a is greater than or equal to b, this returns 1, else it returns 0. |
| a<b     | <     | <       | If a is less than b, this returns 1, else it returns 0. |
| a≤b     | ≤     | ≤       | If a is less than or equal to b, this returns 1, else it returns 0. |

## Floating Point
As of version 2.5.1.0, Grammer is beginning to have support for floating point numbers. In general, float commands are signified by an operations followed by a `.`.

| Example | Token | Grammer | Description                                      |
|:------- |:----- |:------- |:------------------------------------------------ |
| A→.B    | →.    | →.      | Stores the 4 bytes at ptr A to ptr B             |
| A+.B    | +.    | +.      | Adds the floats at A and B, returns a pointer.   |
| A-.B    | -.    | -.      | Subtracts the floats at A and B, returns a pointer. |
| A*.B    | *.    | *.      | Multiplies the floats at A and B, returns a pointer. |
| A/.B    | /.    | /.      | Divides the floats at A and B, returns a pointer. |
| √(.B    | √(.   | √(.     | Computes the square root of the float at A, returns a pointer. |


## Number System
Grammer's number system works like this: Numbers are integers 0 to 65535. This means no fractions, or decimals, though are a few commands that handle larger numbers.

Let's look at this closer. First, why 65535? That is easy to answer. Grammer
uses 16-bit math. In binary, the numbers are 0000000000000000b to
1111111111111111b. Convert that to decimal (our number system) and you get 0 to 65535. If you don't understand binary or hexadecimal, see the [Binary Lesson](binary-lesson.md)
section. Understanding binary and hex is not necessary, but it will help you
understand why certain commands act the way they do. Plus, it can help you figure
out some advanced tricks.

Now, let's look at some scenarios. If you overflow and add 1 to 65535, it
loops back to 0. Similarly, if you subtract 1 from 0, you loop back to 65535.
Then you can see that 65530+11=5. You also now know that -1=65535. So what happens
if you multiply 11\*65535? Believe it or not, you will get -11 which is 65536-
11=65525.(If you ever want to go into more advanced math in college, hold on to
this info for when you get into Abstract Algebra. You are working with the ring
**Z**<sub>2<sup>16</sup></sub>).

Division, unfortunately is not as nice as multiplication, addition, or
subtraction. 3/-1 will give you 0 because it is 3/65535.
