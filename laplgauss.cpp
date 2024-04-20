#include <iostream>
#include <opencv2/opencv.hpp>

void printmask(cv::Mat &m) {
  for (int i = 0; i < m.size().height; i++) {
    for (int j = 0; j < m.size().width; j++) {
      std::cout << m.at<float>(i, j) << ",";
    }
    std::cout << std::endl;
  }
}

int main(int, char **) {
  cv::VideoCapture cap;

  float media[] = {0.1111, 0.1111, 0.1111, 0.1111, 0.1111,
                   0.1111, 0.1111, 0.1111, 0.1111};
  float gauss[] = {0.0625, 0.125,  0.0625, 0.125, 0.25,
                   0.125,  0.0625, 0.125,  0.0625};
  float horizontal[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
  float vertical[] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
  float laplacian[] = {0, -1, 0, -1, 4, -1, 0, -1, 0};
  float boost[] = {0, -1, 0, -1, 5.2, -1, 0, -1, 0};

  cv::Mat frame, framegray, frame32f, frameFiltered, frameFiltered2;
  cv::Mat mask(3, 3, CV_32F), mask2(3, 3, CV_32F);
  cv::Mat result;
  double width, height;
  int absolut, cont = 0;
  char key;

  cap.open(0);

  if (!cap.isOpened()) 
    return -1;

  cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
  cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);

  cv::namedWindow("filtroespacial", cv::WINDOW_NORMAL);
  cv::namedWindow("original", cv::WINDOW_NORMAL);

  mask = cv::Mat(3, 3, CV_32F, media);

  absolut = 1;  // calcula absoluto da imagem

  for (;;) {
    cap >> frame;  // captura nova imagem da camera
    cv::cvtColor(frame, framegray, cv::COLOR_BGR2GRAY);
    cv::flip(framegray, framegray, 1);
    cv::imshow("original", framegray);
    framegray.convertTo(frame32f, CV_32F);
    cv::filter2D(frame32f, frameFiltered, frame32f.depth(), mask, cv::Point(1, 1), cv::BORDER_REPLICATE);
    if(cont==1){
      cv::filter2D(frame32f, frameFiltered2, frame32f.depth(), mask, cv::Point(1, 1), cv::BORDER_REPLICATE);
      cv::filter2D(frameFiltered2, frameFiltered, frame32f.depth(), mask2, cv::Point(1, 1), cv::BORDER_REPLICATE);
    }
    if (absolut) {
      frameFiltered = cv::abs(frameFiltered);
    }

    frameFiltered.convertTo(result, CV_8U);

    cv::imshow("filtroespacial", result);

    key = (char)cv::waitKey(10);
    if (key == 27) break;  // tecla ESC pressionada!
    switch (key) {
      case 'a':
        absolut = !absolut;
        break;
      case 'm':
        cont = 0;
        mask = cv::Mat(3, 3, CV_32F, media);
        
        printmask(mask);
        break;
      case 'g':
        cont = 0;
        mask = cv::Mat(3, 3, CV_32F, gauss);
        printmask(mask);
        break;
      case 'h':
        cont = 0;
        mask = cv::Mat(3, 3, CV_32F, horizontal);
        printmask(mask);
        break;
      case 'v':
        cont = 0;
        mask = cv::Mat(3, 3, CV_32F, vertical);
        
        printmask(mask);
        break;
      case 'l':
        cont = 0;
        mask = cv::Mat(3, 3, CV_32F, laplacian);
        printmask(mask);
        break;
      case 'b':
        cont = 0;
        mask = cv::Mat(3, 3, CV_32F, boost);
        break;
      case 'x':
        cont = 1;
        mask = cv::Mat(3, 3, CV_32F, gauss);
        mask2 = cv::Mat(3, 3, CV_32F, laplacian);
        break;
      default:
        break;
    }
  }
  return 0;
}
