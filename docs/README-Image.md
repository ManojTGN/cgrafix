# createGrafixImage
```c
createGrafixImage(grafixImage *image,  const char* filePath, int fileType)
```
Note: Only supports `.BMP` file formats

reads the image file and set the data to the image object.

`window` - window object | `grafixWindow` <br>
`filePath` - the file path to the image | `grafixWindow` <br>
`fileType` - the extension or type of the file. Currently it has 3 types | `int` <br>
- `FT_BMP`
- `FT_PNG`
- `FT_JPG`

returns `1` if the image creation is successfull else `0` | `int`

## Example
```c
grafixImage image;
createGrafixImage(&image,"cgrafix.bmp",FT_BMP);
```
<br>

# drawGrafixImage
```c
drawGrafixImage(grafixWindow window, grafixImage image, int x, int y)
```
render the image to the frame of the specified window

`window` - window object | `grafixWindow` <br>
`image` - image object | `grafixImage` <br>
`x` - starting position of the image's x axis | `int` <br>
`y` - starting position of the image's y axis | `int` <br>

returns nothing | `void`

## Example
```c
drawGrafixImage(window,image,100,100);
```
<br>

# rotateGrafixImage `development`
```c
rotateGrafixImage(grafixImage *image, float angle)
```
Rotate the image in clockwise direction with the specified angle.

`image` - image object | `grafixImage` <br>
`angle` - image rotation angle 0.0-360.0 | `float` <br>

returns nothing | `void`

## Example
```c
waitGrafixWindow(window, 1000);
```
<br>
