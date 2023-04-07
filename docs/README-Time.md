# getGrafixFPS
```c
getGrafixFPS(grafixWindow window)
```
Get the window's Frame Per Seconds `(FPS)`

`window` - window object | `grafixWindow` <br>

returns the fps of the window | `int`

## Example
```c
int fps;
fps = getGrafixFPS(window);
```
<br>

# tickGrafix
```c
tickGrafix(grafixWindow window, int tick)
```
Note: This method should be called once per frame. It will compute how many milliseconds have passed since the previous call.

`window` - window object | `grafixWindow` <br>
`tick` - maximum frames can be rendered | `int` <br>

returns nothing | `void`

## Example
```c
drawGrafixRect(window,100,100,400,400,(grafixColor){255,255,255},FM_OUTLINE,0);
```
<br>

# waitGrafixWindow `development`
```c
waitGrafixWindow(grafixWindow window, int millisecond)
```
It will stop or puts the window to sleep for the specified millisecond and every processed will be paused.

`window` - window object | `grafixWindow` <br>
`millisecond` - millisecond to put the window on sleep | `int` <br>

returns nothing | `void`

## Example
```c
waitGrafixWindow(window, 1000);
```
<br>

# updateGrafixTime
```c
updateGrafixTime(grafixWindow window)
```
Update the wait timer for the tick function and calculate the frame per seconds for the window.

`window` - window object | `grafixWindow` <br>

returns nothing | `void`

## Example
```c
updateGrafixTime(window);
```
<br>
