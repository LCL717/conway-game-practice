# Conway Game Practice

For the convenience of debugging, I conducted optimization experiments on the basis of 150 cycles for execution time. During the experiment, all execution times were measured based on 150 cycles.

Execution time in branch A is **57775ms**.

*I use symbol ✅ to denote the optimization solution that I have ultimately adopted.*

## Step 1: Some basic optimazation.

1. Due to the previously implemented visualization window, there was a 50ms delay during each cycle. Therefore, this functionality has been removed to optimize the execution time. ✅

    After removing show image window: 
    `Execution time: 48089ms`
2. Using cv::mask instead of cv::rectangle avoids drawing directly on the original image.: ✅

    `Execution time: 46830ms`

This step has improved the execution time by approximately **11000ms**.

## Step 2 Test which function has the greatest impact on runtime

1. Execution time after removing  `draw` : **33522ms**
2. Execution time after removing  `update`: **36281ms**
3. Execution time after removing  `writevideo`: **39196ms**

Both the draw and update functions have a significant negative impact on execution speed, while the impact of video encoding is not as significant as expected.

## Step 3 Optimization of `update` function.

- Make `newCells_` private to avoid allocating memory for it every time `update` is called. ✅

  Execution time: **46496ms**

- Optimize `countNeighbours` by replacing `if (cells_[i][j]) count++` with `count += cells_[i][j]` to avoid meaningless conditional statements. ✅
    
    Execution time: **40344ms**
- Optimize `updateCells` by reducing the number of conditional statements executed. ✅

    Execution time: **39857ms**

- Avoid data copying between `newcells_` and `cells_` by swapping the pointers of their first addresses.: ✅

    Execution time: **38678ms**

This step has improved the execution time by approximately **8000ms**.

## Step 4 Optimization of `draw` function.
 The main purpose of this function is to convert `cells_` to the commonly used `Mat` type in OpenCV, all elements of `cells_` are determined before data conversion. Therefore, it is possible to optimize the program using multi-threading.

- Try `<thread>` from the C++ standard library. After conducting experiments, I found that the most significant time optimization for my device (8 cores) occurred when I divided the function into **four** threads. ✅
    
    Execution time: **36515ms**

- Next, I tried using OpenCV's multi-threading tool `cv::parallel_for_`. The execution time I got using this method was **39746ms**. There was no significant improvement in performance using the OpenCV `parallel_for_` tool.

This step has improved the execution time by approximately **2000ms**.

## Step 5 Others

- Use bitwise operation to replace modulo 2: 

  `Execution time: 36757ms`
  
  No apparent optimization.

- Then I tried removing Initial state generator `rand()`: 

  `Execution time: 25390ms`
  
  The efficiency of random number generators can have a significant impact.

  1. replace rand() with std::random_device:    
      `Execution time: 36526ms`
  
      No apparent optimization.
  
  2. try multi-threads: 
        
        `Execution time: 36366ms`
  
        No apparent optimization.

- Replace two-dimensional array with one-dimensional array: 
  
  `Execution time: 36620ms`

   No apparent optimization.

## Conduct experiment over 1000 cycles.

### branch A
 ```
 Execution time: 332637ms
 ```
### branch B
```
Execution time: 214784ms 
```

## Conclution

Based on the experiment with 1000 cycles, I managed to reduce the execution time by approximately 35.4%.

Another approach for further optimization would be to utilize GPU processing for the graphical part of the Game of Life simulation, provided that the computer has GPU capabilities. This could potentially offload some of the processing burden from the CPU and improve overall performance.