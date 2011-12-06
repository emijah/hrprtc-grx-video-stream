#include <cstdio>
#include <iostream>
#include <iomanip>
#include <uEye.h>
#include <unistd.h>

#include "camera.h"

camera::camera (camType cam_t)
    : width(640), height(480), fps(2), num(0), type(cam_t)
{
}


camera::~camera ()
{
}


int
camera::init(unsigned int devId, bool _fileout, int _cam_num)
{
    cam_num = _cam_num;
    if(type==UVC)
    {
        std::cout << "devID:" << devId << std::endl;
        Cap = new cv::VideoCapture(devId);
        Cap->set(CV_CAP_PROP_FRAME_WIDTH, width);
        Cap->set(CV_CAP_PROP_FRAME_HEIGHT, height);
        width = Cap->get(CV_CAP_PROP_FRAME_WIDTH);
        height = Cap->get(CV_CAP_PROP_FRAME_HEIGHT);
        double _fps = Cap->get(CV_CAP_PROP_FPS);
        if(_fps>0) fps = _fps;
        std::cout << "w:" << width << ", h:" << height << std::endl;

        //std::cout << "FORMAT:" << Cap->get(CV_CAP_PROP_FORMAT)         << std::endl;
        //std::cout << "MODE:"   << Cap->get(CV_CAP_PROP_MODE)         << std::endl;
        brightness = Cap->get(CV_CAP_PROP_BRIGHTNESS);
        contrast   = Cap->get(CV_CAP_PROP_CONTRAST);
        saturation = Cap->get(CV_CAP_PROP_SATURATION);
        hue        = Cap->get(CV_CAP_PROP_HUE);
        std::cout << "BRIGHTNESS:" << brightness << std::endl;
        std::cout << "CONTRAST:"   << contrast   << std::endl;
        std::cout << "SATURATION:" << saturation << std::endl;
        std::cout << "HUE:"        << hue        << std::endl;
        //std::cout << "GAIN:"       << Cap->get(CV_CAP_PROP_GAIN)       << std::endl;
        //std::cout << "CONVERT_RGB:"<< Cap->get(CV_CAP_PROP_CONVERT_RGB)<< std::endl;

        if(!Cap->isOpened())
            return -1;
        frame = cv::Mat(height, width, CV_8UC3);

    }
    else
    {
        m_hCam = static_cast<HCAM>(devId);
        CAMINFO m_ci;
        INT nRet = is_InitCamera(&m_hCam, &m_ci);
        if(nRet != IS_SUCCESS)
        {
            std::cerr << "Open camera failed (Code: " << nRet << ")" << std::endl;
            return -1;
        }
        SENSORINFO m_si;
        int m_nSizeX=0, m_nSizeY=0;
        int m_MaxWidth=0, m_MaxHeight=0;
        int m_nMemoryId;
        is_GetCameraInfo(m_hCam, &m_ci);
        is_GetSensorInfo(m_hCam, &m_si);
        if(m_nSizeX<=0) m_nSizeX = m_MaxWidth = m_si.nMaxWidth;
        if(m_nSizeY<=0) m_nSizeY = m_MaxHeight = m_si.nMaxHeight;
        std::cerr << "maxWidth:"  << m_MaxWidth  << std::endl;
        std::cerr << "maxHeight:" << m_MaxHeight << std::endl;
        if(m_pcImageMemory != NULL )
            nRet = is_FreeImageMem(m_hCam, m_pcImageMemory, m_nMemoryId);
        m_pcImageMemory = NULL;

        std::cout << "o:" << IS_SUCCESS << std::endl;
        std::cout << "x:" << IS_NO_SUCCESS << std::endl;

        int m_nColorMode = IS_SET_CM_RGB24;
        int m_nBitsPerPixel=24;
        nRet = is_SetColorMode(m_hCam, m_nColorMode);
        std::cout << "colormode:" << nRet << std::endl;
        nRet = is_SetSubSampling(m_hCam, IS_SUBSAMPLING_2X_VERTICAL | IS_SUBSAMPLING_2X_HORIZONTAL);
        std::cout << "sub:" << nRet << std::endl;
        int aoi_x=0, aoi_y=0, aoi_w=width, aoi_h=height;
        nRet = is_SetAOI(m_hCam, IS_SET_IMAGE_AOI, &aoi_x, &aoi_y, &aoi_w, &aoi_h);
        std::cout << "aoi:" << nRet << std::endl;
        nRet = is_SetFrameRate(m_hCam, fps, &fps);
        std::cout << "fps:" << nRet << ", new_fps=" << fps << std::endl;
        double new_exp = 0.0;
        nRet = is_SetExposureTime(m_hCam, IS_SET_ENABLE_AUTO_SHUTTER, &new_exp);
        std::cout << "exposure:" << nRet << ", new_exp=" << new_exp << std::endl;
        m_nSizeX = aoi_w;
        m_nSizeY = aoi_h;
        //afeterAOI
        nRet = is_SetPixelClock(m_hCam, 30*2);
        std::cout << "pixel:" << nRet << std::endl;

        nRet = is_AllocImageMem(m_hCam, m_nSizeX, m_nSizeY, m_nBitsPerPixel, &m_pcImageMemory, &m_nMemoryId);
        if(m_pcImageMemory != NULL)
            nRet = is_SetImageMem(m_hCam, m_pcImageMemory, m_nMemoryId);
        else
            return -1;

        if(m_si.nColorMode == IS_COLORMODE_BAYER )
        {
            double dEnable = 1.0;
            nRet = is_SetAutoParameter(m_hCam, IS_SET_AUTO_WB_ONCE, &dEnable, 0);
        }

        frame = cv::Mat(m_nSizeY, m_nSizeX, CV_8UC3);
        std::cerr << "frame_X:" << frame.cols << std::endl;
        std::cerr << "frame_Y:" << frame.rows << std::endl;
    }

    fileout = _fileout;
    if (fileout)
    {
        std::stringstream interpreter;
        interpreter << devId;
        std::string fname = "cap" + interpreter.str() + ".avi";
        vw.open(fname, CV_FOURCC ('X','V','I','D'),
                fps, cv::Size ((int) width, (int) height));
        if (!vw.isOpened()) return -1;
        std::cout << "vw:"<<&vw << std::endl;
    }

    return 0;
}


void
camera::start()
{
    if(type!=UVC)
        // capture start
        int nRet = is_CaptureVideo(m_hCam, IS_DONT_WAIT);
}


uchar *
camera::capture ()
{
    if(type==UVC)
    {
        *Cap >> frame;
        *Cap >> frame;
        *Cap >> frame;
        *Cap >> frame;
        *Cap >> frame;
    }
    else
        frame.data = (uchar*)m_pcImageMemory;

    if (fileout)
    {
        std::stringstream interpreter;
        interpreter << std::setw(3) << std::setfill('0') << num << "[frame]";
        cv::putText(frame, interpreter.str(), cv::Point(10, 20), cv::FONT_HERSHEY_PLAIN, 1, CV_RGB(0,255,100));
        vw << frame;
    }
    num++;

    if (type!=UVC)
    {
        cv::waitKey(static_cast<long>(1000/fps/cam_num));
        //        usleep(1000 * fps/cam_num);
    }

    return frame.data;
}


double
camera::getWidth ()
{
    return width;
}


double
camera::getHeight ()
{
    return height;
}

bool
camera::updateBrightness(float _brightness)
{
    if (brightness != _brightness) {
        brightness = _brightness;
        Cap->set(CV_CAP_PROP_BRIGHTNESS, brightness);
        return true;
    }
    return false;
}

bool
camera::updateContrast(float _contrast)
{
    if (contrast != _contrast) {
        contrast = _contrast;
        Cap->set(CV_CAP_PROP_CONTRAST, contrast);
        return true;
    }
    return false;
}

bool camera::updateSaturation(float _saturation)
{
    if (saturation != _saturation) {
        saturation = _saturation;
        Cap->set(CV_CAP_PROP_SATURATION, saturation);
        return false;
    }
    return false;
}

bool camera::updateHue(float _hue)
{
    if (hue != _hue) {
        hue = _hue;
        Cap->set(CV_CAP_PROP_HUE, hue);
        return false;
    }
    return false;
}
