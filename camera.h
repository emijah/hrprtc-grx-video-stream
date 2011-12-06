#include <opencv/cv.h>
#include <opencv/highgui.h>

#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/types.h>
#include <linux/videodev.h>

#include "ViewSimulator.hh"

typedef uint32_t DWORD;
typedef DWORD HCAM;

class camera
{
public:
    typedef enum {uEye, UVC, RAW, HRP}
    camType;
    camera (camType type = uEye);
    ~camera ();
    int init (unsigned int devId, bool fileout = false, int cam_num=1, CORBA::ORB_ptr orb = NULL);
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

    struct video_picture vp;
    struct video_mbuf vm;
    struct video_mmap vmm;
    int n, fd;
    unsigned char *map;
    unsigned char * yuv2rgb(unsigned char *yuv,unsigned char *rgb_buf,int width,int height);

    OpenHRP::Camera_var virtualCamera;
};
