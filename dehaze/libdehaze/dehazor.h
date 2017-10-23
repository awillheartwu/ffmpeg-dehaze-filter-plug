#ifndef DEHAZOR_H
#define DEHAZOR_H

#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "guidedfilter.h"

using::std::string;

class Dehazor
{
public:
    Dehazor() {}
    ~Dehazor() {}
    cv::Mat process(const string & theImage);
    cv::Mat process(const cv::Mat & image);
    
private:
    // window size -General parameter
    int m_windowsize = 3;
    // fog reservation factor-General parameter
    double m_fog_reservation_factor = 0.0;
    // local window size -guided filter parameter
    int m_localwindowsize = 12;
    // regularization eps filter parameter
    float m_eps = 10^-6;
    // output image
    cv::Mat m_dehazedImage;
    // raw transmission map
    cv::Mat m_rawImage;
    // refined transmission map
    cv::Mat m_refinedImage;

private:
    cv::Mat boxfilter(cv::Mat &im,int r);
    cv::Mat guildedfilter_color(const cv::Mat &Img,cv::Mat &p,int r,float &epsi);

public:
    void setWindowsize(int px) 
    {
        if (px<0)
            px = 0;
        m_windowsize = px;
    }
    void setFogFactor(double factor) 
    {
        if (factor < 0)
            factor = 0;
        m_fog_reservation_factor = factor;
    }
    void setLocalWindowsize(int lpx) 
    {
        if (lpx<0)
            lpx=0;
        m_localwindowsize = lpx;
    }
    void setEpsilon(float epsilon) 
    {
        if (epsilon<0)
            epsilon=0;
        m_eps = epsilon;
    }

    cv::Mat & getRawMap(){return m_rawImage;}
    cv::Mat & getRefinedMap() {return m_refinedImage;}
    cv::Mat & getDehazedMap() {return m_dehazedImage;}
};

#endif // DEHAZOR_H
