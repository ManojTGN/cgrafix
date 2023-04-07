# manageGrafixEvent
```c
manageGrafixEvent(grafixWindow window, grafixEvent** event, int* size)
```
get the current tick events and store each events in the event pointer and update the size of  the currect tick event size

`window` - window object | `grafixWindow` <br>
`grafixEvent` - grafixEvent pointer's address `(**)` | `grafixEvent**` <br>
`Size` - to store the current event size | `int*` <br>

returns nothing | `int`

## Example
```c
grafixEvent* event;
int eventSize = 0;

manageGrafixEvent(window,&event,&eventSize);
for(int i = 0; i < eventSize; i++){
    if(event[i].type == WM_DESTROY){
        endGrafixWindow(window);
    }
}
```
<br>
