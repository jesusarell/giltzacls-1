#ifndef SEGMENTATION_H
#define SEGMENTATION_H

#include <mainwindow.h>
#include <ui_mainwindow.h>
#include <helper.h>

class MainWindow;
struct performSegmentationResponse{
      std::vector<cv::Mat> keys;
      cv::Mat unlabeledImage;
      std::vector<cv::Point> labelsPosition;
};

class Segmentation : public QObject {
    Q_OBJECT

public:
    Segmentation(MainWindow* parent);
    ~Segmentation();

    void setup(void);
    cv::Mat imageThresholded;
    cv::Mat imageThresholdedGeneral;
    cv::Mat cropped;

private:
    MainWindow* parent;
    std::vector<cv::Rect>  boundRect;
    std::vector<cv::RotatedRect> rotatedRect;
public slots:
    cv::Mat thresholdingTrimmed(cv::Mat);
    performSegmentationResponse performSegmentation(cv::Mat, bool = true);
    std::vector<cv::RotatedRect> findBoundingBox1(cv::Mat);
    void List_BoundingBox(std::vector<cv::RotatedRect>);
    void show_BoundingBox(void);
    cv::Mat show_BoundingBoxOriented(int, std::vector<cv::RotatedRect>, cv::Mat);
    cv::Mat SecondthresholdingTrimmed(cv::Mat ImageCropped);
    cv::Mat SecondthresholdingTrimmedV2(cv::Mat ImageCropped);
    void BotonSegmentarListener(void);
    void representBoundigBox(cv::Mat);
    cv::Mat drawBoundingBox(std::vector<cv::RotatedRect>, cv::Mat);
    void drawThresholdedImage(cv::Mat);
    void drawThresholdedkey(cv::Mat);
    void onSelectedIndexCrop(int);
    void watershed(cv::Mat);
    void watershedV2(cv::Mat);
    void watershedV3(cv::Mat);
    cv::Mat limpiezaBordes(cv::Mat);
};

#endif // SEGMENTATION_H
