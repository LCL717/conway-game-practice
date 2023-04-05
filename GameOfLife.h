#pragma once

#include <iostream>
#include <opencv2/opencv.hpp>



class GameOfLife {
public:
  GameOfLife(int rows, int cols);
  void update();
  void draw(cv::Mat image);
  void godFuncThanos();
  void godFuncCreator();
  void godFuncReverse();
  
private:
  int rows_;
  int cols_;
  bool** cells_;
  bool** newCells_;
  int cellSize_ = 1;
  int countNeighbours(int row, int col);
  bool updateCells(int row, int col, int count);
};