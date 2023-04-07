 
 # createGrafixFont
```c
createGrafixFont(grafixFont *font, char* directory ,int fontSize)
```
Get the window's Frame Per Seconds `(FPS)`

`window` - window object | `grafixWindow` <br>
`directory` - the path to the font file | `char*` <br>
`fontSize` - setting the fontSize for the GrafixFont | `int` <br>

returns nothing | `void`

## Example
```c
grafixFont FONT;
createGrafixFont(&FONT,"jbr.ttf",16);
```
<br>

# drawGrafixText
```c
drawGrafixText(grafixWindow window, grafixFont font, int x, int y, char* text, grafixColor color)
```

`window` - window object | `grafixWindow` <br>
`font` - set the font | `grafixFont` <br>
`x` - x position of the text | `int` <br>
`y` - y position of the text | `int` <br>
`text` - text should be rendered on the frame | `char*` <br>
`color` - text color | `grafixColor` <br>

returns nothing | `void`

## Example
```c
grafixFont FONT;
createGrafixFont(&FONT,"jbr.ttf",16);
drawGrafixText(window,FONT,10,10,"Hello cGrafix",WHITE);
```
<br>
