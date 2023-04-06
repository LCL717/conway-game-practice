#include <iostream>
#include "GameOfLife.h"
#include <chrono>

#define ROW       256
#define COL       256
#define CELL_SIZE 1
#define BOARD_SIZE 2048

/* Disable god function */
//#define EN_GOD

int main(int argc, char** argv)
{
  /* Disable random */
  //srand(time(nullptr));
  
  int interval = 50;
  int snapshot = 100;
  int length = 256;

#ifdef EN_GOD
  void (GameOfLife::*godFunc)() = &GameOfLife::godFuncReverse;
  if(argc == 5) {
#else
  if(argc == 4) {
#endif
    interval = std::stoi(argv[1]);
    snapshot = std::stoi(argv[2]);
    length = std::stoi(argv[3]);
#ifdef EN_GOD
    if(stoi(argv[3]) == 1) {
      godFunc = &GameOfLife::godFuncThanos;
    }
    else if(stoi(argv[3]) == 2) {
      godFunc = &GameOfLife::godFuncCreator;
    }
    else {
      godFunc = &GameOfLife::godFuncReverse;
    }
#endif
  }

  GameOfLife game(length, length, interval);
  cv::VideoWriter video("game_of_life.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 1000 / interval , cv::Size(BOARD_SIZE, BOARD_SIZE), false);
  // start
  auto start = std::chrono::high_resolution_clock::now();

  for (int i = 0; i < 1000; i++) {   
    cv::Mat frame(BOARD_SIZE, BOARD_SIZE, CV_8UC1, cv::Scalar(0)); 
#ifdef EN_GOD
    (game.*godFunc)();
#endif
    game.draw(frame);
    video.write(frame); 

    if(i == snapshot - 1) {
      cv::imwrite("snapshot.bmp", frame);
    }
    game.update();
  }
  // end
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
  std::cout << "Execution time: " << duration << "ms" << std::endl;
  
  return 0;
}