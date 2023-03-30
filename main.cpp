#include <iostream>
#include <opencv2/opencv.hpp>
#include "GameOfLife.h"


int main(int argc, char** argv)
{
  srand(time(nullptr));
  
  int interval = 500;
  int snapshot = 100;
  void (GameOfLife::*godFunc)();
  godFunc = &GameOfLife::godFuncReverse;
  
  if(argc == 4) {
    interval = stoi(argv[1]);
    snapshot = stoi(argv[2]);
    if(stoi(argv[3]) == 1) {
      godFunc = &GameOfLife::godFuncThanos;
    }
    else if(stoi(argv[3]) == 2) {
      godFunc = &GameOfLife::godFuncCreator;
    }
    else {
      godFunc = &GameOfLife::godFuncReverse;
    }
  }

  GameOfLife game(100, 100, interval);
  cv::VideoWriter video("game_of_life.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 2.0, cv::Size(1000, 1000), false);
  
  

  for (int i = 0; i < 150; i++) {   
    cv::Mat frame(100 * 10, 100 * 10, CV_8UC1, cv::Scalar(0)); 
    (game.*godFunc)();
    game.draw(frame);
    video.write(frame); 

    if(i == snapshot - 1) {
      cv::imwrite("snapshot.jpg", frame, {cv::IMWRITE_JPEG_QUALITY, 80});
    }
    game.update();
  }
  return 0;
}