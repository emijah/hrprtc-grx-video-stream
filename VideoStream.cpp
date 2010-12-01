// -*- C++ -*-
/*!
 * @file  VideoStream.cpp * @brief Sequence InPort component * $Date$
 *
 * $Id$
 */
#include "VideoStream.h"

// Module specification
// <rtc-template block="module_spec">
static const char *videostream_spec[] =
{
	"implementation_id", "VideoStream",
	"type_name", "VideoStream",
	"description", "Sequence InPort component",
	"version", "1.0",
	"vendor", "General Robotix,Inc.",
	"category", "example",
	"activity_type", "SPORADIC",
	"kind", "SequenceInComponent",
	"max_instance", "1",
	"language", "C++",
	"lang_type", "compile",
	// Configuration variables
	""
};

// </rtc-template>

VideoStream::VideoStream (RTC::Manager * manager)
// <rtc-template block="initializer">
:
RTC::DataFlowComponentBase (manager),
m_MultiCameraImagesOut ("MultiCameraImages", m_MultiCameraImages),
m_VideoStreamServicePort ("VideoStreamService")
// </rtc-template>
{
}


VideoStream::~VideoStream ()
{
}


RTC::ReturnCode_t VideoStream::onInitialize ()
{
	// Registration: InPort/OutPort/Service
	// <rtc-template block="registration">
	// Set InPort buffers

	// Set OutPort buffer
	addOutPort ("MultiCameraImages", m_MultiCameraImagesOut);

	// Set service provider to Ports
	m_VideoStreamServicePort.registerProvider ("service0", "VideoStreamService",
		m_service0);

	// Set service consumers to Ports

	// Set CORBA Service Ports
	addPort (m_VideoStreamServicePort);

	// </rtc-template>

	// <rtc-template block="bind_config">
	// Bind variables and configuration variable

	// </rtc-template>

	std::vector < unsigned int >
		devIds;
	//RTC::Properties& prop = getProperties();
	//coil::stringTo(devIds, prop["camera_dev_id"].c_str());
	devIds.push_back (0);
	devIds.push_back (1);
	for (unsigned int i = 0; i < devIds.size (); i++)
	{
		m_cameras.push_back (new camera (devIds[i]));
	}

	return RTC::RTC_OK;
}


/*
RTC::ReturnCode_t VideoStream::onFinalize()
{
  return RTC::RTC_OK;
}
*/
/*
RTC::ReturnCode_t VideoStream::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/
/*
RTC::ReturnCode_t VideoStream::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/
/*
RTC::ReturnCode_t VideoStream::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/
/*
RTC::ReturnCode_t VideoStream::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

RTC::ReturnCode_t VideoStream::onExecute (RTC::UniqueId ec_id)
{
	if (m_service0.numCapture != 0)
	{
		for (unsigned int i = 0; i < m_cameras.size (); i++)
		{
			m_cameras[i]->capture ();
		}
		if (m_service0.numCapture > 0)
		{
			m_service0.numCapture--;
		}
	}
	return RTC::RTC_OK;
}


/*
RTC::ReturnCode_t VideoStream::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/
/*
RTC::ReturnCode_t VideoStream::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/
/*
RTC::ReturnCode_t VideoStream::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/
/*
RTC::ReturnCode_t VideoStream::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/
/*
RTC::ReturnCode_t VideoStream::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

extern
"C"
{

	void
		VideoStreamInit (RTC::Manager * manager)
	{
		coil::Properties profile (videostream_spec);
		manager->
			registerFactory (profile,
			RTC::Create < VideoStream >,
			RTC::Delete < VideoStream >);
	}

};
