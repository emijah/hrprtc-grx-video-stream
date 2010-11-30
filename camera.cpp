#include <stdio.h>
#include <camera.h>

camera::camera ()
{
	width = 320;
	height = 240;
	num = 0;

	cvCapture = cvCaptureFromCAM (0);
	cvSetCaptureProperty (cvCapture, CV_CAP_PROP_FRAME_WIDTH, width);
	cvSetCaptureProperty (cvCapture, CV_CAP_PROP_FRAME_HEIGHT, height);
	vw =
		cvCreateVideoWriter ("cap.avi", CV_FOURCC ('X', 'V', 'I', 'D'), 15,
		cvSize ((int) width, (int) height));

	cvInitFont (&font, CV_FONT_HERSHEY_COMPLEX, 0.7, 0.7);
	cvNamedWindow ("Capture", CV_WINDOW_AUTOSIZE);
}


camera::~camera ()
{
	cvReleaseVideoWriter (&vw);
	cvReleaseCapture (&cvCapture);
	cvDestroyWindow ("Capture");
}


void
camera::capture ()
{
	frame = cvQueryFrame (cvCapture);
	snprintf (str, 64, "%03d[frame]", num);
	cvPutText (frame, str, cvPoint (10, 20), &font, CV_RGB (0, 255, 100));
	cvWriteFrame (vw, frame);
	cvShowImage ("Capture", frame);
	num++;
}
