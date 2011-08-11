#include "VideoStream.h"
#include "camera.h"

class VideoStreamImpl:public VideoStream
{
	public:
		VideoStreamImpl (RTC::Manager * manager);
		~VideoStreamImpl ();
		virtual RTC::ReturnCode_t onExecute (RTC::UniqueId ec_id);

	private:
		camera m_camera;
};
