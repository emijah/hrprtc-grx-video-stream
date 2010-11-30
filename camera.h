#include <opencv/cv.h>
#include <opencv/highgui.h>

class camera
{
	public:
		camera ();
		~camera ();
		void capture ();
	private:
		CvCapture * cvCapture;
		IplImage *frame;
		CvVideoWriter *vw;
		CvFont font;
		double width, height;
		int num;
		char str[64];
};
