#include "GameOfLife.h"

GameOfLife::GameOfLife(int rows, int cols)
    : rows_(rows), cols_(cols)
{
  cells_ = new bool*[rows_];
  newCells_ = new bool*[rows_];
  for (int i = 0; i < rows_; i++) {
    cells_[i] = new bool[cols_];
    newCells_[i] = new bool[cols_];
    for (int j = 0; j < cols_; j++) {
      cells_[i][j] = (rand() % 2 == 0);
    }
  }
}

int GameOfLife::countNeighbours(int row, int col)
{
  int count = 0;
  int rowStart = std::max(0, row - 1);
  int rowEnd = std::min(rows_ - 1, row + 1);
  int colStart = std::max(0, col - 1);
  int colEnd = std::min(cols_ - 1, col + 1);

  for (int i = rowStart; i <= rowEnd; i++) {
    for (int j = colStart; j <= colEnd; j++) {
      if (i == row && j == col) continue;
      count += cells_[i][j];
    }
  }

  return count;
}

bool GameOfLife::updateCells(int row, int col, int count)
{
  return (count == 3 || (cells_[row][col] && count == 2));
}

void GameOfLife::update()
{
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      int count = countNeighbours(i, j);
      newCells_[i][j] = updateCells(i, j, count);
    }
  }
  // swap pointer of cells_ and newcells_
  std::swap(cells_, newCells_);
}

void GameOfLife::draw(cv::Mat image)
{
  cv::Mat mask(image.rows, image.cols, CV_8UC1, cv::Scalar(0));
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (cells_[i][j]) {
        cv::Rect rect(j * cellSize_, i * cellSize_, cellSize_, cellSize_);
        mask(rect).setTo(cv::Scalar(255));
      }
    }
  }
  image.setTo(cv::Scalar(255, 255, 255), mask);
  //cv::imshow("Game of Life", image);
  //cv::waitKey(interval_);
}

void GameOfLife::godFuncThanos() {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if(rand() % 10 == 0) {
        if(cells_[i][j] == true) {
          if(rand() % 2 == 0) cells_[i][j] = false;
        }
      }
    }
  }
}

void GameOfLife::godFuncCreator() {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if(cells_[i][j] == false) {
        if(rand() % 1000 == 0) cells_[i][j] = true;
      }
    }
  }
}

void GameOfLife::godFuncReverse() {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_ - i; j++) {
      cells_[cols_- 1 - j][rows_ - 1 - i] = cells_[i][j];
    }
  }
}