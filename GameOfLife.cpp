#include "GameOfLife.h"
#include <thread>
#include <random>

GameOfLife::GameOfLife(int rows, int cols)
    : rows_(rows), cols_(cols)
{
  cells_ = new bool*[rows_];
  newCells_ = new bool*[rows_];
  cellSize_ = IMAGE_SIZE / rows;

#ifdef EN_NEWRAND
  std::random_device rd; 
  std::mt19937 gen(rd());
  std::bernoulli_distribution dis(0.5);
#endif
  for (int i = 0; i < rows_; i++) {
    cells_[i] = new bool[cols_];
    newCells_[i] = new bool[cols_];
    for (int j = 0; j < cols_; j++) {
#ifdef EN_NEWRAND
      cells_[i][j] = dis(gen);
#else
      cells_[i][j] = (rand() % 2 == 0);
#endif
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
  std::vector<std::thread> threads;
  // thread number
  int numThreads = 4;
  int rowsPerThread = rows_ / numThreads;

  for (int t = 0; t < numThreads; t++) {
    threads.push_back(std::thread([=] {
      int startRow = t * rowsPerThread;
      int endRow = (t == numThreads - 1) ? rows_ : startRow + rowsPerThread;
      for (int i = startRow; i < endRow; i++) {
        for (int j = 0; j < cols_; j++) {
          if (cells_[i][j]) {
            cv::Rect rect(j * cellSize_, i * cellSize_, cellSize_, cellSize_);
            mask(rect).setTo(cv::Scalar(255));
          }
        }
      }
    }));
  }

  for (auto& thread : threads) {
    thread.join();
  }

  image.setTo(cv::Scalar(255, 255, 255), mask);
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