#include <opencv/cv.h>
#include <opencv/highgui.h>

typedef uint32_t DWORD;
typedef DWORD HCAM;

class camera
{
public:
    typedef enum {uEye, UVC}
    camType;
    camera (camType type = uEye);
    ~camera ();
    int init (unsigned int devId, bool fileout = false, int cam_num=1);
    void start();
    uchar *capture ();
    double getHeight ();
    double getWidth ();

    bool updateBrightness(float brightness);
    bool updateContrast(float Contrast);
    bool updateSaturation(float Saturation);
    bool updateHue(float hue);
    float brightness;
    float contrast;
    float saturation;
    float hue;
private:
    HCAM m_hCam;
    cv::Ptr<cv::VideoCapture> Cap;
    cv::Mat frame;
    cv::VideoWriter vw;
    double width, height, fps;

    camType type;
    int num, cam_num;
    bool fileout;
    char *m_pcImageMemory;
};
