#include <iostream>
#include <chrono>
#include <thread>
#include <opencv2/opencv.hpp>

using namespace std;

class GameOfLife {
public:
  GameOfLife(int rows, int cols, int interval);
  void update();
  void draw(cv::Mat image);
  
private:
  int rows_;
  int cols_;
  bool** cells_;
  int cellSize_ = 10;
  int interval_ = 500;
  int countNeighbours(int row, int col);
  bool updateCells(int row, int col, int count);
};

GameOfLife::GameOfLife(int rows, int cols, int interval)
    : rows_(rows), cols_(cols), interval_(interval)
{
  cells_ = new bool*[rows_];
  for (int i = 0; i < rows_; i++) {
    cells_[i] = new bool[cols_];
    for (int j = 0; j < cols_; j++) {
      cells_[i][j] = (rand() % 2 == 0);
    }
  }
}

int GameOfLife::countNeighbours(int row, int col)
{
  int count = 0;
  int rowStart = max(0, row - 1);
  int rowEnd = min(rows_ - 1, row + 1);
  int colStart = max(0, col - 1);
  int colEnd = min(cols_ - 1, col + 1);

  for (int i = rowStart; i <= rowEnd; i++) {
    for (int j = colStart; j <= colEnd; j++) {
      if (i == row && j == col) continue;
        if (cells_[i][j]) count++;
    }
  }

  return count;
}

bool GameOfLife::updateCells(int row, int col, int count)
{
  if (cells_[row][col]) {
    if (count == 2 || count == 3) {
      return true;
    } 
    else {
      return false;
    }
  }
  else {
    if (count == 3) {
      return true;
    }
    else {
      return false;
    }
  }
}

void GameOfLife::update()
{
  bool** newCells = new bool*[rows_];
  for (int i = 0; i < rows_; i++) {
    newCells[i] = new bool[cols_];
    for (int j = 0; j < cols_; j++) {
      int count = countNeighbours(i, j);
      newCells[i][j] = updateCells(i, j, count);
    }
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      cells_[i][j] = newCells[i][j];
    }
      delete[] newCells[i];
  }
  delete[] newCells;
}

void GameOfLife::draw(cv::Mat image)
{
  //cv::Mat image(rows_ * cellSize_, cols_ * cellSize_, CV_8UC1, cv::Scalar(0));
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (cells_[i][j]) {
        cv::Rect rect(j * cellSize_, i * cellSize_, cellSize_, cellSize_);
        cv::rectangle(image, rect, cv::Scalar(255), -1);
      }
    }
  }
  cv::imshow("Game of Life", image);
  cv::waitKey(interval_);
}

int main(int argc, char** argv)
{
  int interval = 500;
  int snapshot = 100;
  if(argc > 1) {
    interval = stoi(argv[1]);
    snapshot = stoi(argv[2]);
  }

  GameOfLife game(100, 100, interval);
  cv::VideoWriter video("game_of_life.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 2.0, cv::Size(1000, 1000), false);
  
  for (int i = 0; i < 100; i++) {   
    cv::Mat frame(100 * 10, 100 * 10, CV_8UC1, cv::Scalar(0)); 
    game.draw(frame);
    video.write(frame); 

    if(i == snapshot - 1){
      cv::imwrite("snapshot.jpg", frame, {cv::IMWRITE_JPEG_QUALITY, 80});
    }
    game.update();
  }
  return 0;
}