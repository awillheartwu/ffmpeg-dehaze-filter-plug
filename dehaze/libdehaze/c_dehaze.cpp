#include <stdint.h>

#include "dehazor.h"
#include "c_dehaze.h"

int doDehaze(uint8_t *pData[3], const int width, const int height)
{   // 1. yuv420p -> Rgb
    const int ySize = width * height;
    cv::Mat yuvImg;      
    yuvImg.create(height*3/2, width, CV_8UC1);  
    // copy y
    memcpy(yuvImg.data, pData[0], ySize);  
    // copy uv
    memcpy(yuvImg.data + ySize, pData[1], ySize/4);  
    memcpy(yuvImg.data + ySize*5/4, pData[2], ySize/4);  
    // yuv420p -> Rgb
    cv::Mat rgbImg;   
    cv::cvtColor(yuvImg, rgbImg, CV_YUV2BGR_I420);  

    // 2. do dehaze process
    Dehazor dehazor;
    // set dehazor params
    //const int kernelSize = (int)(std::max(std::max(3.0, width*0.01), height*0.01));
    //dehazor.setWindowsize(kernelSize);
    //dehazor.setLocalWindowsize(kernelSize*4);
    dehazor.setFogFactor(0.95f);
    dehazor.setWindowsize(15);
    dehazor.setLocalWindowsize(21);    
    
    cv::Mat origImage; //(height, width, CV_8U, pData); // create a mat for process
    cv::Mat dehazedImage =  dehazor.process(rgbImg);

    // 3. copy the dehazed image data back
    cvtColor(dehazedImage, yuvImg, CV_RGB2YUV_I420); //BGR2YUV
    memcpy(pData[0], yuvImg.data, ySize);
    memcpy(pData[1], yuvImg.data + ySize, ySize/4);    
    memcpy(pData[2], yuvImg.data + ySize*5/4, ySize/4);
    
    return 0;
}
