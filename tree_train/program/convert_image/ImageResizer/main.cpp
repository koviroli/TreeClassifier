#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <opencv2/gpu/gpu.hpp>
#include <opencv2/objdetect/objdetect.hpp>

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

#include <QFile>
#include <QFileDialog>
#include <QStringList>
#include <QDebug>

void resize(cv::Mat& m)
{
    cv::resize(m, m, cv::Size(80, 60));
    if(m.channels() == 3)
        cv::cvtColor(m , m, cv::COLOR_BGR2GRAY);
}

void save_img(cv::Mat m, const std::string path)
{
    resize(m);
    cv::imwrite(path, m);
}

//this is for human frontal faces
void cut_face(cv::Mat m, const QString fileex)
{
    if(!m.data)return;

    cv::CascadeClassifier classifier;
    std::string faceXML = "../lbpcascade_frontalface.xml";
    const std::string path2save = "../resized_images/";

    static int img_counter = 0;

    if(!classifier.load(faceXML))
    {
        std::cerr << "error: cannot found" << faceXML.c_str();
        exit(EXIT_FAILURE);
    }

    std::vector<cv::Rect> objects;
    //detecting
    cv::Rect rect;

    cv::Mat histeq;
    cv::cvtColor (m, histeq, cv::COLOR_BGR2GRAY );
    cv::equalizeHist (histeq, histeq );
    classifier.detectMultiScale(histeq, objects, 1.1, 3, 0, cv::Size(60, 60));

    if(objects.size() > 0)
    {
        cv::Point x0(objects[0].x - 1, objects[0].y - 1);
        cv::Point y0(objects[0].x + objects[0].width+2, objects[0].y + objects[0].height + 2);
        rect = cv::Rect(x0, y0);
        cv::rectangle(m, x0, y0, cv::Scalar(0, 0, 0));

        cv::Mat crop = m(rect);
        save_img(crop, path2save + "img -" + std::to_string(img_counter++) + "." + fileex.toStdString());
    }
}

int main(int argc, char *argv[])
{
	 QString pos_path = "../pos/";
	 QString neg_path = "../neg/";
    QDir input_dir(pos_path);
    const std::string path2save = "../resized_images/";
    QString file_extension;
    cv::Mat src_img;
    int img_counter = 0;

    if (!input_dir.exists())
    {
        qDebug() << input_dir.path() +" doesn't exists.\n";
        exit(EXIT_FAILURE);
    }
    else
    {
        QStringList files_list = input_dir.entryList(QDir::NoDotAndDotDot | QDir::Files, QDir::NoSort);

        for (QStringList::iterator it = files_list.begin(); it != files_list.end(); ++it)
        {
            QStringList curr_img = it->split(QRegExp("\\."));
            file_extension = curr_img.at(1);

            QString image_full_parh = input_dir.path() + "/" +(*it);

            src_img = cv::imread(image_full_parh.toStdString());
            if(!src_img.data) continue;

            //cut_face(src_img, file_extension);
            save_img(src_img, path2save + "img-" + std::to_string(img_counter++) + ".jpg");
            std::cout << (*it).toStdString() << " saved." << std::endl;
        }
    }
    cv::waitKey();
    return 0;

}
