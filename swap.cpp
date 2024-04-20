#include <iostream>
#include <opencv2/opencv.hpp>

int main(int, char**) {
  cv::Mat image;
  cv::Vec3b val;
  
  image = cv::imread("biel.png", cv::IMREAD_GRAYSCALE);
  
  if (!image.data) std::cout << "Nao abriu biel.png" << std::endl;

  cv::namedWindow("janela", cv::WINDOW_AUTOSIZE);
  int i = 0, j = 0, h = 0, w = 0;
  unsigned char aux;
  h = image.rows;
  w = image.cols;
  
  for(i = 0; i < h; i++){
     for(j = 0; j < w; j++){
        if(i < h/2 && j < w/2){
          aux = image.at<uchar> (i, j);
          image.at<uchar> (i, j) = image.at<uchar> (i + h/2, j + w/2);
          image.at<uchar> (i + h/2, j + w/2) = aux;
        }else if (i >= h/2 && j < w/2){
                 aux = image.at<uchar> (i, j);
                 image.at<uchar> (i, j) = image.at<uchar> (i - h/2 ,j + w/2);
                 image.at<uchar> (i - h/2 ,j + w/2) = aux;
        }  
     }
  }
  	
  cv::imshow("janela", image);
  cv::waitKey();
  return 0;
}


