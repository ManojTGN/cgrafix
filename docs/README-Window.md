# CreateGrafixWindow
```c
createGrafixWindow ( grafixWindow* window, int width, int height, char* name )
```
Create dynamic memory for the window handler and frame buffer then add the window to the `grafix::WINDOWS` array to manage it properly. if fails at creating memory for the window or frame buffer it results in 0. 

`window` - Pointer of the window | `grafixWindow` <br>
`width` - Width of the window | `int` <br>
`height` - Height of the window | `int` <br>
`name` - Name of the window | `char*` <br>

returns `1` if window created successfully else `0` | `int`

## Example
```c
grafixWindow window;
createGrafixWindow(&window,800,800,"GrafixWindow");
```
<br>

# showGrafixWindow
```c
showGrafixWindow(grafixWindow window)
```
set the visibility of the window to 1 (visible).

`window` - window object | `grafixWindow`

returns nothing | `void`

## Example
```c
grafixWindow window;
createGrafixWindow(&window,800,800,"GrafixWindow");

showGrafixWindow(window);
```
<br>

# hideGrafixWindow
```c
hideGrafixWindow(grafixWindow window)
```
set the visibility of the window to 0 (hidden).

`window` - window object | `grafixWindow`

returns nothing | `void`

## Example
```c
grafixWindow window;
createGrafixWindow(&window,800,800,"GrafixWindow");

hideGrafixWindow(window);
```
<br>

# endGrafixWindow
```c
void endGrafixWindow(grafixWindow window)
```
delete the window and free the framebuffer of the window. removed the window from `grafix::WINDOWS` array. but events are not removed. so you can still access the last tick events.

`window` - window object | `grafixWindow`

returns nothing | `void`

## Example
```c
...
for(int i = 0; i < eventSize; i++){
    if(event[i].type == WM_DESTROY){
        endGrafixWindow(window);
    }
}
...
```
<br>

# isGrafixWindowEnded
```c
int isGrafixWindowEnded(grafixWindow window)
```
checks if the window is deleted or not

`window` - window object | `grafixWindow`

returns `1` if the window is ended else `0` | `int`

## Example
```c
while(  ! isGrafixWindowEnded(window)  ){
  
  ...

}
```
<br>

# updateGrafixWindow
```c
void updateGrafixWindow(grafixWindow window);
```
update the currect frameBuffer of the specified window to the window.

`window` - window object | `grafixWindow`

returns nothing | `void`

## Example
```c
while(  ! isGrafixWindowEnded(window)  ){
  
  updateGrafixWindow(window);

}
```
<br>

# fillGrafixWindow
```c
void fillGrafixWindow(grafixWindow window, grafixColor color);
```
fill the window frame to the specified color and the existing frame will be erased.

`window` - window object | `grafixWindow`
`color` - color of the screen to be filled | `grafixColor`

returns nothing | `void`

## Example
```c
while(  ! isGrafixWindowEnded(window)  ){
  
  fillGrafixWindow(window,(grafixColor){0,0,0});

}
```
<br>

# getGrafixWindow `deprecated`
```c
grafixWindow* getGrafixWindow(int id)
```
get the window from the `grafix::WINDOWS` array if exists

`id` - window id to get the window object | `int`

returns window object if exists else `NULL` | `grafixWindow`

## Example
```c
grafixWindow window = getGrafixWindow(0);
```
<br>
