# Modules

Modules help to extend the Grammer language. Unfortunately, there is a lot of overhead involved, so locating and loading routines is rather slow. As such, I recommend modules where speed isn't critical. Where it is, you can still use assembly programs and hex codes.

Here is the format of a module:
```
;;All routines must be 768 bytes or less
;;They get copied to saveSScreen
#include "grammer.inc"
#include "grammer2.5.inc"
  .db "Gram"      ;Magic number
  .dw 0           ;Minimum module version. Currently, this should be zero. It might never change.
  .dw TableSize   ;Number of elements on the table
  .dw func0
  .dw func1
  ...
.org 0            ;Set the code counter to 0 here

func0: .db "MYFUNC0",$10  \ .dw size_of_func0_code
  ;func0
  ;code

func1: .db "MYFUNC1",$10  \ .dw size_of_func1_code
  ;func0
  ;code

```
To speed things up a little, Grammer uses binary search to locate functions. As a consequence, the table needs to be sorted by their strings. For example, if func0 is called "XXX" and func1 is called "AAA", then the table should have `.dw func1` before `.dw func0`.

Another issue to take into account is that the code is copied to saveSScreen. First, this means your code must be 768 bytes or fewer, but also jumps and calls need to be relocated if they occur in your code. *This does * **not** *apply to `jr ` instructions as these jump a relative distance.*

So for example, let's look at this super complicated piece of code and make it even more complicated:
```
func0: .db "XXX",$10 .dw funco_end-func0_start
func0_start:
  call label
  ret
label:
  ret
func0_end:
```
That call will almost certainly crash. Instead, you need:
```
func0: .db "XXX",$10 .dw funco_end-func0_start
func0_start:
  call saveSScreen+label-func0_start
  ret
label:
  ret
func0_end:
```
Again, this only applies to `jp` and `call` instructions, and only those for routines within the code. You can still make calls to Grammer routines just fine.

One final note before we get to Grammer routines: the function names must be terminated by a `0` byte, a space token, `$29`, or an open parentheses, `$10`.

# Grammer Routines

You need `grammer.inc` and `grammer2.5.inc`.

I have to work now, so bug me in Omnimaga or Cemetech or CodeWalrus chats for info until I fill this in.
