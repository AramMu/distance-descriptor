#ifndef UTILITY_H
#define UTILITY_H
#include <opencv2/opencv.hpp>
#include "edge.h"

class Utility {
public:
    static double dist (const cv::Point& p1, const cv::Point& p2);
    static std::vector <cv::Point> getWhitePoints (const cv::Mat& input);
    static std::vector <int>  getEdgePoints (const cv::Mat& input, const std::vector <cv::Point>& maskPoints);
    static std::vector <double> getShortestDistance (const Graph& graph, int start);
    static std::vector <double> createHistogram (const std::vector<double>& values, int bucketCount);
    static std::vector <double> normalizeHistogram (const std::vector<double>& values);
};

#endif // UTILITY_H
