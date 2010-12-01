#include <cstdio>
#include <boost/lexical_cast.hpp>
#include "camera.h"

camera::camera (unsigned int devId)
{
	width = 320;
	height = 240;
	num = 0;

	cvCapture = cvCaptureFromCAM (devId);
	cvSetCaptureProperty (cvCapture, CV_CAP_PROP_FRAME_WIDTH, width);
	cvSetCaptureProperty (cvCapture, CV_CAP_PROP_FRAME_HEIGHT, height);
	std::string fname =
		"cap" + boost::lexical_cast < std::string > (devId) + ".avi";
	vw =
		cvCreateVideoWriter (fname.c_str (), CV_FOURCC ('X', 'V', 'I', 'D'), 15,
		cvSize ((int) width, (int) height));

	//cvInitFont (&font, CV_FONT_HERSHEY_COMPLEX, 0.7, 0.7);
	//cvNamedWindow ("Capture", CV_WINDOW_AUTOSIZE);
}


camera::~camera ()
{
	cvReleaseVideoWriter (&vw);
	cvReleaseCapture (&cvCapture);
	//cvDestroyWindow ("Capture");
}


char *
camera::capture ()
{
	frame = cvQueryFrame (cvCapture);
	//snprintf (str, 64, "%03d[frame]", num);
	//cvPutText (frame, str, cvPoint (10, 20), &font, CV_RGB (0, 255, 100));
	//cvWriteFrame (vw, frame);
	//cvShowImage ("Capture", frame);
	num++;
	return frame->imageData;
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
