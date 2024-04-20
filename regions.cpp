#include <iostream>
#include <opencv2/opencv.hpp>

int main(int, char**) {
  cv::Mat image;
  cv::Vec3b val;

  image = cv::imread("biel.png", cv::IMREAD_GRAYSCALE);
  if (!image.data) std::cout << "Nao abriu biel.png" << std::endl;

  cv::namedWindow("janela", cv::WINDOW_AUTOSIZE);
  cv::Point p1, p2;
  int aux = 0, i = 0, j = 0;
  
  std:: cout << "Coordendas do ponto um\n";
  std:: cin >> aux;
  p1.x = aux;
  std:: cin >> aux;
  p1.y = aux;
  std:: cout << "Coordendas do ponto dois\n";
  std:: cin >> aux;
  p2.x = aux;
  std:: cin >> aux;
  p2.y = aux;
  
  for(i = p1.x; i <= p2.x; i++){
     for(j = p1.y; j <= p2.y; j++){
        image.at<uchar> (i, j) = 255 - image.at<uchar> (i, j);
     }
  }
  	
  cv::imshow("janela", image);
  cv::waitKey();
  return 0;
}


