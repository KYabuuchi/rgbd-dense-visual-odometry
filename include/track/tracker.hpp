#pragma once
#include "track/frame.hpp"

class Tracker
{
public:
    struct Config {
        cv::Mat1f intrinsic;
        int level;
        bool is_chatty;
    };

    struct Scene {
        const Frame& pre_frame;
        const Frame& cur_frame;
        const cv::Mat& warped_image;
        const int COL;
        const int ROW;
        cv::Mat1f xi;
        float residual;
    };

private:
    cv::Mat1f calcJacobi(const Frame& frame, cv::Point2f x_i, float depth);
    void showImage(const Scene& scene);
    cv::Mat1f optimize(Scene& scene);

    bool m_initialized;

    Config m_config;
    std::vector<Frame> m_pre_frames;
    std::vector<Frame> m_cur_frames;
    std::vector<std::vector<float>> m_vector_of_residuals;

public:
    void plot(bool block = false);

    Tracker(const Config& config) : m_initialized(false), m_config(config)
    {
        cv::namedWindow("show", cv::WINDOW_NORMAL);
    }

    void init(cv::Mat depth_image, cv::Mat gray_image);

    cv::Mat1f track(const cv::Mat& depth_image, const cv::Mat& gray_image);
};
