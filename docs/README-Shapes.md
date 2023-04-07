# drawGrafixLine
```c
drawGrafixLine(grafixWindow window, int x1, int y1, int x2, int y2, grafixColor color)
```
Draws a line on the frame from (x1,y1) to (x2,y2) with fixed borderWidth 1

`window` - window object | `grafixWindow` <br>
`x1` - x position of the line 1 | `int` <br>
`y1` - y position of the line 1 | `int` <br>
`x2` - x position of the line 2 | `int` <br>
`y2` - y position of the line 2 | `int` <br>
`color` - set the color for the line | `grafixColor` <br>

returns nothing | `int`

## Example
```c
drawGrafixLine(window,0,0,800,800,(grafixColor){255,255,255});
```
<br>

# drawGrafixRect
```c
drawGrafixRect(grafixWindow window, int x, int y, int width, int height, grafixColor color, int fillMode, int borderWidth)
```
Draws a rectangle to the frame starting from the top left corner of the rectangle with (x,y) and to the bottom left corner with ( x + width, y + height) with a borderWidth and can be filled with the fillmode

`window` - window object | `grafixWindow` <br>
`x` - x position of the rectangle (top left) | `int` <br>
`y` - y position of the rectangle (top left) | `int` <br>
`width` - width of the rectangle | `int` <br>
`height` - height of the rectangle | `int` <br>
`color` - set the color for the line | `grafixColor` <br>
`fillMode` - set the fill mode of the rectangle, there are 3 state
- `FM_EMPTY` - does not fill the outline and wont fill the rectangle
- `FM_OUTLINE` - fill only the outline of the rectangle
- `FM_FILL` - totally fill the rectangle
`borderWidth` - set the border width of the rectangle | `int` <br>

returns nothing | `void`

## Example
```c
drawGrafixRect(window,100,100,400,400,(grafixColor){255,255,255},FM_OUTLINE,0);
```
<br>

# drawGrafixCircle
```c
drawGrafixCircle(grafixWindow window, int x, int y, int radius, grafixColor color, int fillMode, int borderWidth)
```
Draws a circle to the frame with a center point (x,y) with the specified radius

`window` - window object | `grafixWindow` <br>
`x` - x position of the circle (top left) | `int` <br>
`y` - y position of the circle (top left) | `int` <br>
`radius` - radius of the circle | `int` <br>
`color` - set the color for the line | `grafixColor` <br>
`fillMode` - set the fill mode of the rectangle, there are 3 state
- `FM_EMPTY` - does not fill the outline and wont fill the rectangle
- `FM_OUTLINE` - fill only the outline of the rectangle
- `FM_FILL` - totally fill the rectangle
`borderWidth` - set the border width of the rectangle | `int` <br>

returns nothing | `void`

## Example
```c
drawGrafixCircle(window,400,400,50,(grafixColor){255,255,255},FM_OUTLINE,0);
```
<br>
