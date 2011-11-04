#include "VideoStream.h"

RTC::ReturnCode_t VideoStream::onExecute (RTC::UniqueId ec_id)
{
    m_camera.capture ();
    return RTC::RTC_OK;
}
