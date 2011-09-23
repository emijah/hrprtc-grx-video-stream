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
