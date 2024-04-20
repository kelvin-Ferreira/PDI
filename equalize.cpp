#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char** argv){
    cv::Mat image;
    int width, height;
    cv::VideoCapture cap;
    cv::Mat hist;
    int nbins = 64;
    float range[] = {0, 255};
    const float *histrange = { range };
    bool uniform = true;
    bool accumulate = false;
    int key;

    cap.open(0);

    if(!cap.isOpened()){
        std::cout << "Câmera indisponível";
        return -1;
    }

    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);

    std::cout << "Largura = " << width << std::endl;
    std::cout << "Altura  = " << height << std::endl;

    int histw = nbins, histh = nbins/2;
    cv::Mat histImg(histh, histw, CV_8UC3, cv::Scalar(0,0,0));

    while(1){
        cap >> image;
        cv::cvtColor(image, image, cv::COLOR_BGR2GRAY);
        cv::calcHist(&image, 1, 0, cv::Mat(), hist, 1,
                     &nbins, &histrange,
                     uniform, accumulate);

        cv::normalize(hist, hist, 0, histImg.rows, cv::NORM_MINMAX, -1, cv::Mat());

        histImg.setTo(cv::Scalar(0));
        
        cv::Mat eqImg;
        cv::equalizeHist(image, eqImg);
        
        for(int i=0; i<nbins/2; i++){
            for(int j=0; j<nbins; j++){
               image.at<uchar>(i,j) = 0;
           }
        }

        for(int i=0; i<nbins; i++){
            cv::line(image,
                     cv::Point(i, histh),
                     cv::Point(i, histh-cvRound(hist.at<float>(i))),
                     cv::Scalar(255, 255, 255), 1, 8, 0);
        }
        
        cv::calcHist(&eqImg, 1, 0, cv::Mat(), hist, 1,
                     &nbins, &histrange,
                     uniform, accumulate);
        cv::normalize(hist, hist, 0, histImg.rows, cv::NORM_MINMAX, -1, cv::Mat());
        
        for(int i=0; i<nbins/2; i++){
            for(int j=0; j<nbins; j++){
               eqImg.at<uchar>(i,j) = 0;
           }
        }

        for(int i=0; i<nbins; i++){
            cv::line(eqImg,
                     cv::Point(i, histh),
                     cv::Point(i, histh-cvRound(hist.at<float>(i))),
                     cv::Scalar(255, 255, 255), 1, 8, 0);
        }

        cv::Mat concImg;
        cv::hconcat(image, eqImg, concImg);
        cv::imshow("image", concImg);
        key = cv::waitKey(30);
        if(key == 27) break;
    }
    return 0;
}

