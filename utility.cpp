#include "utility.h"
#include "edge.h"
#include <queue>

auto sqr (auto x) -> decltype(x*x) {
    return x*x;
}

double Utility::dist (const cv::Point& p1, const cv::Point& p2) {
    return std::sqrt (sqr(p1.x - p2.x) + sqr(p1.y - p2.y));
}


std::vector <cv::Point> Utility::getWhitePoints (const cv::Mat& input) {
    std::vector <cv::Point> result;
    assert (input.type() == CV_8UC1);
    for (int i = 0; i < input.rows; ++i) {
        for (int j = 0; j < input.cols; ++j) {
            if (input.at<uchar> (i,j)) {
                result.push_back(cv::Point (j,i));
            }
        }
    }
    return result;
}

enum NeighbourMode {
    eN4, eN8
};

bool hasBlackNeighbour (const cv::Mat& input, const cv::Point& p, NeighbourMode neigh = eN4) {
    for (int i = p.y-1; i <= p.y+1; ++i) {
        for (int j = p.x-1; j <= p.x+1; ++j) {
            cv::Point tmp;
            if (tmp == p) {
                continue;
            }
            if (tmp.x < 0 || tmp.y < 0 || tmp.x >= input.cols || tmp.y >= input.rows) {
                continue;
            }
            if (neigh == eN4 && std::abs(p.y - tmp.y) + std::abs(p.x - tmp.x) == 2) {
                continue;
            }
            if (!input.at<uchar>(tmp)) {
                return true;
            }
        }
    }
    return false;
}

std::vector <int> Utility::getEdgePoints (const cv::Mat& input, const std::vector <cv::Point>& maskPoints) {
    assert (input.type() == CV_8UC1);
    std::vector <int> result;
    for (int i = 0; i < maskPoints.size(); ++i) {
        if (hasBlackNeighbour (input, maskPoints[i]) > 0) {
            result.push_back(i);
        }
    }
    return result;
}


std::vector <double> Utility::getShortestDistance (const Graph& graph, int start) {
    std::vector <double> dist(graph.size(), -1);
    //dist[start] = 0;
    std::priority_queue <Vertex, std::vector<Vertex>, Vertex::IsGreater> pq;
    pq.push (Vertex (start, 0));
    while (!pq.empty()) {
        Vertex t = pq.top();
        pq.pop();
        if (dist[t.u] >= 0) {
            continue;
        }
        dist[t.u] = t.w;
        for (int i = 0; i < graph.size(); ++i) {
            Vertex x(i, t.w + graph[t.u][i]);
            if (dist [x.u] >= 0) {
                continue;
            }
            pq.push (x);
        }
    }
    return dist;
}

std::vector <double> Utility::createHistogram (const std::vector<double>& values, int bucketCount) {
    const double inf = 1000000;
    double min=inf, max=-inf;
    for (int i = 0; i < values.size(); ++i) {
        min = std::min(min, values[i]);
        max = std::max(max, values[i]);
    }
    double ratio = (max - min) / bucketCount;
    std::vector <double> hist (bucketCount);
    for (int i = 0; i < values.size(); ++i) {
        int index = (values[i] - min)/ratio;
        if (index == bucketCount) index--;
        assert (index >= 0 && index < bucketCount);
        hist[index]++;
    }
    return hist;
}

std::vector <double> Utility::normalizeHistogram (const std::vector<double>& values) {
    std::vector <double> res(values.size());
    double total = 0;
    for (int i = 0; i < values.size(); ++i) {
        total += values[i];
    }
    for (int i = 0; i < values.size(); ++i) {
        res[i] = values[i] / total;
    }
    return res;
}


