# Cynthia Digital Display Example

## Overview

Exercises the 7-segment LED digital display on the Elenco Electronic Playground EP-130 project kit. The wiring I used is as follows:
RP Pico W Pin|Display Pin|EP-130 Spring Terminal
---|---|---
GND|cathode|25
GP0|dp|24
GP1|a|17
GP2|b|21
GP3|c|23
GP4|d|20
GP5|e|19
GP6|f|18
GP7|g|22

### Digital Display Segments
```
    a
   ---
 f| g |b
   ---
 e|   |c
   ---  .dp
    d
```

## Characters
I make the display of characters abstract by allowing a function call to display a given character, including digits 0 through 9, decimal point, all segments (which is sort of a "lamp test").