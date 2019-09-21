# Graphics Tutorial
Grammer offers much faster graphics over BASIC, but a good understanding of the
lower-level graphics is what will make your graphics *good*.

The most important graphics command is `DispGraph`, located at
`[prgm][right][4]`. In Grammer, graphics commands don't get rendered to the LCD
like they do in BASIC. Updating the LCD is a relatively slow operation on the TI-83+/84+ series of calculators (the physical LCD is much slower than the Z80 processor), so the ability to defer updating the LCD offers the biggest boost
in speed over BASIC graphics. This ability to defer is also what makes graphics
smoother.

#### DispGraph
By default, `DispGraph` draws the graphscreen to the LCD. Here is an example:
```
.0:Return
DispGraph
Stop
```
When you run this from the homescreen, you will see something like:
*![Image Description: DispGraph, showing the graph screen](img/000.png)*

You can also display an arbitrary graphics buffer. If you aren't familiar with graphics buffers, see the section on [Graphics Buffers](../drawing.md#graphics-buffers).
```
.0:Return
DispGraph0
Stop
```
*![Image Description: DispGraph, showing garbage](img/001.png)*
This shows garbage because `DispGraph` is reading the start of memory
(at 0x0000) as if it is graphics data.

#### Disp
Most graphics routines allow you to provide an optional argument designating a
graphics buffer to draw to. You can also set a default buffer with the `Disp `
function. For example, `Disp G-T'` (or `Disp π9872` on older versions). Now,
whenever you draw or update the LCD, that is the buffer that will be used. This
means you can preserve the graph screen while still using graphics in Grammer.
Note that `G-T` is the token that you can see near the bottom of the mode menu.

As an example, let's set the secondary buffer as the default buffer and draw
some text (note: This is not the most efficient way to do this!):
```
.0:Return
Disp G-T`
Text(0,0,"HELLO, WORLD!
DispGraph
Stop
```
*![Image Description: Animated GIF displaying "HELLO, WORLD!" on an alternate graphics buffer](img/000.gif)*

`Disp ` is also important if you want to use grayscale graphics. For the
following examples, I will assume you know the basic ideas behind grayscale on
these monochrome calculators. If not,
[brush up on grayscale](../drawing.md#grayscale)
Internally, Grammer cleverly sources data from two graphics buffers to determine
what to display to the LCD when using `DispGraph`. By default, "both" buffers
point to the graph screen, so it is always reading the same color pixel from
both sources, essentially displaying either black, or white, and never
flickering between the two. By default, Grammer sources 50% of the color from
one buffer, and 50% from the other.
Here is an example that draws grayscale bars until the user presses `[CLEAR]`:
```
.0:Return
Disp °G-T'        ;Set the secondary buffer to appBackUpScreen, 0x9872
ClrDraw           ;Clear the primary buffer
ClrDrawG-T'       ;Clear the back buffer
Line(0,0,64,48    ;Draws a black rectangle on the left half of the main buffer
Line(0,0,64,24,1,G-T'    ;Draws a black rectangle on the left quarter of the back buffer
Line(48,0,64,24,1,G-T'   ;Draws a black rectangle on the third quarter of the back buffer
Repeat getKey(15  ;Repeat the loop until key 15 ([clear]) is pressed
DispGraph         ;Display the graph buffers
End
Stop
```
*![Image Description: The left quarter of the screen is black, the right quarter is white, and the middle half is gray](img/002.png)*

You can change how much color is sourced from each buffer by selecting a
different gray mask. Internally, Grammer has 12 different masks, but
realistically only masks 1 and 2 are the most useful. Mask 1 is the default and
sources 50% from each buffer. However Mask 2 sources 75% from the primary buffer
and 25% from the back buffer. Adding `2→Disp` to the start of the above code:
```
.0:Return
2→Disp            ;Set to 75-25 grayscale mode
Disp °G-T'        ;Set the secondary buffer to appBackUpScreen, 0x9872
ClrDraw           ;Clear the primary buffer
ClrDrawG-T'       ;Clear the back buffer
Line(0,0,64,48    ;Draws a black rectangle on the left half of the main buffer
Line(0,0,64,24,1,G-T'    ;Draws a black rectangle on the left quarter of the back buffer
Line(48,0,64,24,1,G-T'   ;Draws a black rectangle on the third quarter of the back buffer
Repeat getKey(15  ;Repeat the loop until key 15 ([clear]) is pressed
DispGraph         ;Display the graph buffers
End
Stop
```
*![Image Description: Four vertical bars, each a quarter of the screen wide: Black, light gray, dark gray, white.](img/003.png)*


#### ClrDraw
`ClrDraw` clears the primary graphics buffer, setting it to white, and resets
the text coordinates to the upper-left, (0,0). Alternatively, you can specify a
graphics buffer to erase, for example: `ClrDrawG-T'` would clear the buffer that
`G-T'` points to (typically used as a back buffer for grayscale).


#### Circle(
The syntax is `Circle(Y,X,R[,Method[,pattern[,buffer`.
This draws a circle using Y and X as pixel coordinates and R as the radius of the circle in pixels. `Method` is how to draw the circle:
* 1 - Black border (Default)
* 2 - White border
* 3 - Inverted border
* 4 - White border, white fill
* 5 - Black border, black fill
* 6 - Invert border, invert fill
* 7 - White border, black fill
* 8 - White border, invert fill
* 9 - Black border, white fill
* 10 - Black border, invert fill
* 11 - Invert border, white fill
* 12 - Invert border, black fill


`Pattern` is a number from 0 to 255 that will be used as a drawing pattern for the border. For example, 85 is `01010101` in binary, so every other pixel will not be drawn. Use 0 for no pattern. If the bit is 0, the pixel will be drawn, if it is 1, it won't be drawn. `Buffer` is the buffer to draw to (useful with grayscale).

For basic usage:
```
.0:Return
Circle(32,48,20
DispGraph
Stop
```
*![Image Description: A black circle of radius 20 pixels is drawn at the center of the screen.](img/004.png)*

Or an example using a pattern, we need to include the method argument.
```
.0:Return
Circle(32,48,20,1,85
DispGraph
Stop
```
*![Image Description: A black circle of radius 20 pixels is drawn at the center of the screen. Dotted every-other pixel.](img/005.png)*
