#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char**argv) {
  cv::Mat imagemPortadora, imagemEscondida, imagemInicial;
  cv::Vec3b valPortadora, valEscondida, valInicial;
  int nbits = 3;

  imagemInicial = cv::imread(argv[1], cv::IMREAD_COLOR);

  if (imagemInicial.empty()) {
    std::cout << "imagem nao carregou corretamente" << std::endl;
    return (-1);
  }

  imagemPortadora = imagemInicial.clone();
  imagemEscondida = imagemInicial.clone();

  for (int i = 0; i < imagemInicial.rows; i++) {
    for (int j = 0; j < imagemInicial.cols; j++) {
      valInicial = imagemInicial.at<cv::Vec3b>(i, j);
      valPortadora[0] = valInicial[0] >> nbits << nbits;
      valPortadora[1] = valInicial[1] >> nbits << nbits;
      valPortadora[2] = valInicial[2] >> nbits << nbits;
      valEscondida[0] = valInicial[0] << (8-nbits);
      valEscondida[1] = valInicial[1] << (8-nbits);
      valEscondida[2] = valInicial[2] << (8-nbits);
      
      imagemPortadora.at<cv::Vec3b>(i, j) = valPortadora;
      imagemEscondida.at<cv::Vec3b>(i, j) = valEscondida;
    }
  }
  imwrite("Portadora.jpg", imagemPortadora);
  imwrite("Escondida.jpg", imagemEscondida);
  return 0;
}
