#include <iostream>
#include "utility.h"
#include <opencv2/opencv.hpp>
#include "edge.h"

//Improvis:)2016

std::vector <double> getHistogram (const cv::Mat& input, int bucketCount) {
    std::vector <cv::Point> maskPoints = Utility::getWhitePoints(input);
    //std::cout << "White point count is " << maskPoints.size() << std::endl;
    std::vector <int> edgePoints = Utility::getEdgePoints (input, maskPoints);

    Graph graph(maskPoints.size(), std::vector<double> (maskPoints.size()));
    for (int i = 0; i < maskPoints.size(); ++i) {
        for (int j = 0; j < maskPoints.size(); ++j) {
            graph[i][j] = Utility::dist(maskPoints[i], maskPoints[j]);
        }
    }


    //std::vector <std::vector <double> > shortest = Utility::getShortestDistance (graph, edgePoints);
    std::vector <std::vector <double> > shortest (edgePoints.size(), std::vector<double>(edgePoints.size()));
    for (int i = 0; i < shortest.size(); ++i) {
        std::vector <double> tmp = Utility::getShortestDistance(graph, edgePoints[i]);
        for (int j = 0; j < edgePoints.size(); ++j) {
            shortest[i][j] = tmp[edgePoints[j]];
            //std::cout << shortest[i][j] << " ";
        }
        //std::cout << std::endl;
    }


    std::vector <double> allHistValues (shortest.size() * (shortest.size() - 1) / 2);
    int ind=0;
    for (int i = 0; i < shortest.size(); ++i) {
        for (int j = i+1; j < shortest[i].size(); ++j) {
            if (shortest[i][j] == 0) {
                continue;
            }
            allHistValues[ind] = shortest[i][j];
            //std::cout << allHistValues[ind] << " ";
            ind++;
        }
    }

    std::vector <double> histogram = Utility::createHistogram (allHistValues, bucketCount);
    histogram = Utility::normalizeHistogram (histogram);
    //for (int i = 0; i < histogram.size(); ++i) {
    //    std::cout << histogram[i] << " ";
    //}
    return histogram;
}

int main() {
    std::string inputFile1 ("Data/1.png");
    cv::Mat input1 = cv::imread(inputFile1, CV_LOAD_IMAGE_GRAYSCALE);
    std::string inputFile2 ("Data/2.png");
    cv::Mat input2 = cv::imread(inputFile2, CV_LOAD_IMAGE_GRAYSCALE);
    int binCount = 100;
    std::vector <double> hist1 = getHistogram(input1, binCount);
    std::vector <double> hist2 = getHistogram(input2, binCount);

    double dif = 0;
    for (int i = 0; i < hist1.size(); ++i) {
        dif += std::pow (std::abs (hist1[i] - hist2[i]), 2);
    }
    std::cout << "Difference is " << dif;
    //cv::imshow ("AAA", input1);
    //cv::waitKey(0);
    //cv::destroyAllWindows();
    return 0;
}

