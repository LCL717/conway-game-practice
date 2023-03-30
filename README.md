# Conway Game Practice

Make sure to install OpenCV before compiling.

The initial state is random.

The first command-line argument represents the duration of a cycle in milliseconds in the visualization module.

The second command-line argument represents which snapshot of the life cycle the user wants to capture. The value range is between 1 and 150.

There are three god functions, controlled by the third command-line argument.

1. godFuncThanos: In each cycle, there is a one in ten chance of eliminating half of the cells.
2. godFuncCreator: There is a one in a thousand chance of reviving a dead cell.
3. godFuncReverse: copy the top-left half of the board's lives to the bottom-right.

```
make
./main [wait_time] [snap_shot_frame] [god_func_mode]
```

