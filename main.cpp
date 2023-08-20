#include <iostream>
#include <iomanip>
#include "infer.h"
#include <filesystem>
#include <fstream>


void performObjectDetection(DCSP_CORE *&p, const cv::Mat &inputImage, const std::string &outputPath) {
    std::vector<DCSP_RESULT> res;
    cv::Mat inputCopy = inputImage.clone();
    p->RunSession(inputCopy, res);

    cv::Mat outputImage = inputImage.clone();

    for (const auto &re : res) {
        cv::RNG rng(cv::getTickCount());
        cv::Scalar color(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));

        cv::rectangle(outputImage, re.box, color, 3);

        float confidence = floor(100 * re.confidence) / 100;
        std::string label = p->classes[re.classId] + " " +
                            std::to_string(confidence).substr(0, std::to_string(confidence).size() - 4);

        cv::rectangle(
            outputImage,
            cv::Point(re.box.x, re.box.y - 25),
            cv::Point(re.box.x + label.length() * 15, re.box.y),
            color,
            cv::FILLED
        );

        cv::putText(
            outputImage,
            label,
            cv::Point(re.box.x, re.box.y - 5),
            cv::FONT_HERSHEY_SIMPLEX,
            0.75,
            cv::Scalar(0, 0, 0),
            2
        );
    }

    cv::imwrite(outputPath, outputImage);
}

int main() {
    DCSP_CORE *yoloDetector = new DCSP_CORE;
    yoloDetector->classes = {"lp"};
    std::string model_path = "../models/lp-n.onnx";
    // CPU inference
    std::cout << "Using cpu inference !" << std::endl;
    DCSP_INIT_PARAM params{model_path, YOLO_ORIGIN_V8, {640, 640}, 0.5, 0.5, false};
    yoloDetector->CreateSession(params);

    cv::Mat inputImage = cv::imread("/home/thanhln/Desktop/projects/yolov8/inference/images/img_00059.jpg");
    std::string outputImagePath = "output_image.jpg";
    performObjectDetection(yoloDetector, inputImage, outputImagePath);

    delete yoloDetector;
    return 0;
}