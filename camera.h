#include <opencv/cv.h>
#include <opencv/highgui.h>

class camera
{
	public:
		camera (unsigned int devId);
		~camera ();
		char *capture ();
		double getHeight ();
		double getWidth ();
	private:
		CvCapture * cvCapture;
		IplImage *frame;
		CvVideoWriter *vw;
		CvFont font;
		double width, height;
		int num;
		char str[64];
};
