#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/gpu/gpu.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <QDebug>

#include <iostream>
#include <algorithm>


int main(int argc, char *argv[])
{
    //BigTree.jpg
    std::string bad_file_loc = "../test_tree/neg-test-10.pgm";
    std::string file_location = "../test_tree/neg-test_Crop.jpg";
    cv::Mat src_img = cv::imread(file_location);
    cv::Mat histeqFrame;
    cv::Mat detectedFrame;

    cv::CascadeClassifier classifier;
    std::string classifierXML = "../treeClassifierDec08.xml";

    if(!src_img.data)
    {
        std::cout << "error: cant open image";
        exit(EXIT_FAILURE);
    }


    if(src_img.channels() == 3)
    {
        cv::cvtColor (src_img, histeqFrame, cv::COLOR_BGR2GRAY );
    }
    //cv::equalizeHist ( histeqFrame, histeqFrame );
    detectedFrame = src_img.clone();

    if(!classifier.load(classifierXML))
    {
        qDebug() << "error: cannot found" << classifierXML.c_str();
        exit(EXIT_FAILURE);
    }

    std::vector<cv::Rect> objects;
    //detecting
    //for little trees cv::Size(50, 50);
    //for bigger trees cv::Size(100, 100);
    //file_location  = 50x50 tree
    //bad files
    classifier.detectMultiScale(histeqFrame, objects, 1.1, 3, 0, cv::Size(40, 40));

    if(objects.size() > 0)
    {
        for(int i = 0; i < objects.size()-1; ++i)
        {
                cv::Point x0(objects[i].x - 1, objects[i].y - 1);
                cv::Point y0(objects[i].x + objects[i].width+2, objects[i].y + objects[i].height + 2);
                cv::rectangle(detectedFrame, x0, y0, cv::Scalar(255, 0, 0));
                cv::putText(detectedFrame, "tree", x0, cv::FONT_HERSHEY_PLAIN, 1.0,  cv::Scalar(255, 0, 0));
        }
    }
    cv::namedWindow("detected", cv::WINDOW_KEEPRATIO);
    cv::imshow("detected", detectedFrame);


    cv::waitKey(0);
}

