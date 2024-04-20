#include <iostream>
#include <opencv2/opencv.hpp>

int main(int, char**){
  cv::Mat image;
  cv::Vec3b val;

  image= cv::imread("bolhas.png",cv::IMREAD_GRAYSCALE);
  if(!image.data)
    std::cout << "nao abriu bolhas.png" << std::endl;

  cv::namedWindow("Bolhas", cv::WINDOW_AUTOSIZE);
  
  cv::imshow("Bolhas", image);  
  cv::waitKey();
  
  int h, w, cont1=0, cont2=0;
  h = image.rows;
  w = image.cols;
  cv:: Point p;
  
  for(int i=0; i < w; i++){
     image.at<uchar>(0,i)=255;
  }
  
  for(int i = 0; i < w; i++){
     image.at<uchar>(h-1,i)=255;
  }
  
  for(int i=0; i < w; i++){
     image.at<uchar>(i,0)=255;
  }
  
  for(int i = 0; i < w; i++){
     image.at<uchar>(i,w-1)=255;
  }
  
  p.x = 0;
  p.y = 0;
  cv::floodFill(image, p, 0);
  cv::floodFill(image, p, 1);
  
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      if (image.at<uchar>(i, j) == 255) {
        cont1++;
        p.x = j;
        p.y = i;
        cv::floodFill(image, p, 254);
        }
      if (image.at<uchar>(i, j) == 0) {
        if(image.at<uchar>(i, j-1) == 254){
          p.x = j-1;
          p.y = i;
          cv::floodFill(image, p, 150);
          cont2++;
          p.x = j;
          p.y = i;
          cv::floodFill(image, p, 1);
        }else{
             if(image.at<uchar>(i, j-1) == 150){
             p.x = j;
             p.y = i;
             cv::floodFill(image, p, 1);
             }
          }
        }
      }
    }
  
  std::cout << "Total de Bolhas: " << cont1 << "\n";
  std::cout << "Bolhas sem Furos: " << cont1-cont2 << "\n";
  std::cout << "Bolhas com Furos: " << cont2 << "\n";
  imwrite("resultado.png", image);
  cv::imshow("Bolhas", image);  
  cv::waitKey();

  return 0;
}
