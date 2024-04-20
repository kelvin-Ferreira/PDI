#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    int nbins = 64;
    const float range[] = {0, 255};
    const float* histrange[] = { range };
    bool uniform = true;
    bool accumulate = false;
    int key;

    cv::VideoCapture cap(0);

    if (!cap.isOpened()) {
        std::cout << "Câmera indisponível";
        return -1;
    }

    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    double width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    double height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);

    std::cout << "largura = " << width << std::endl;
    std::cout << "altura  = " << height << std::endl;

    cv::Mat image, histImgR, histImgG, histImgB;
    std::vector<cv::Mat> planes(3);
    cv::Mat histR, histG, histB, past;

    int cont = 0, histw = nbins, histh = nbins / 2;

    while (true) {
        cap >> image;
        if (image.empty())
            break;

        cv::split(image, planes);

        
        cv::calcHist(&planes[2], 1, 0, cv::Mat(), histR, 1, &nbins, histrange, uniform, accumulate);
        cv::normalize(histR, histR, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());

        cv::imshow("image", image);

        char key = cv::waitKey(30);
        if (key == 27)
            break;

        
        if (!past.empty()) {
            double correl = cv::compareHist(histR, past, cv::HISTCMP_CORREL);

            if (correl < 0.8) {
                std::cout << "MOVIMENTO DETECTADO!!!" << std::endl;
            }
        }

        
        past = histR.clone();
    }

    return 0;
}

