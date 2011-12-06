// -*- C++ -*-
/*!
 * @file  VideoStream.cpp * @brief Sequence InPort component * $Date$
 *
 * $Id$
 */
#include <sstream>
#include "VideoStream.h"
#include "VectorConvert.h"

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
    "conf.default.update_params","0",
    "conf.default.camera_id",    "0",
    "conf.default.brightness", "0.5",
    //    "conf.default.contrast",   "0.5",
    //    "conf.default.saturation", "0.5",
    //    "conf.default.hue",        "0.5",
    ""
};

// </rtc-template>

VideoStream::VideoStream (RTC::Manager * manager)
// <rtc-template block="initializer">
    :
    RTC::DataFlowComponentBase (manager),
    m_MultiCameraImagesOut ("MultiCameraImages", m_MultiCameraImages),
    m_service0(*this),
    m_CameraCaptureServicePort ("CameraCaptureService")
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
    m_CameraCaptureServicePort.registerProvider ("service0", "CameraCaptureService", m_service0);

    // Set service consumers to Ports

    // Set CORBA Service Ports
    addPort (m_CameraCaptureServicePort);

    // </rtc-template>

    // <rtc-template block="bind_config">
    // Bind variables and configuration variable

    // </rtc-template>

    RTC::Properties & prop = getProperties ();
    fileout = coil::toBool (prop["fileout"].c_str(), "YES", "NO", false);

    std::vector<int> devIds;
    coil::stringTo (devIds, prop["camera_dev_id"].c_str ());

    camera::camType cam_t;
    if(prop["camera_type"]=="UVC" ||prop["camera_type"]=="uvc")
        cam_t = camera::UVC;
    else if (prop["camera_type"]=="uEye" ||prop["camera_type"]=="ueye")
        cam_t = camera::uEye;
    else if (prop["camera_type"]=="HRP" ||prop["camera_type"]=="hrp")
        cam_t = camera::HRP;
    else if (prop["camera_type"]=="RAW" ||prop["camera_type"]=="raw")
        cam_t = camera::RAW;

    m_MultiCameraImages.data.image_seq.length (devIds.size ());
    for (unsigned int i = 0; i < devIds.size (); i++)
    {
        std::cout << "** devId:" << devIds[i] << std::endl;
        camera *cam = new camera (cam_t);
        cam->init(devIds[i], fileout, devIds.size(), m_pORB);
        m_cameras.push_back (cam);
        m_MultiCameraImages.data.image_seq[i].image.width = cam->getWidth ();
        m_MultiCameraImages.data.image_seq[i].image.height = cam->getHeight ();
        m_MultiCameraImages.data.image_seq[i].image.raw_data.length (cam->getWidth () * cam->getHeight () * 3);
    }
    bindParameter("update_params",  m_update_params,"0");
    bindParameter("camera_id",  m_camera_id,    "0");
    bindParameter("brightness", m_brightness, "0.5");
    //    bindParameter("saturation", m_saturation, "0.5");
    //    bindParameter("contrast",   m_contrast,   "0.5");
    //    bindParameter("hue",        m_hue,        "0.5");

    /*    SDOPackage::Configuration_var config = this->getObjRef()->get_configuration();
        SDOPackage::ConfigurationSet_var aset = config->get_active_configuration_set();
        NVList activeData = aset->configuration_data;
        for (int i=0; i<activeData.length(); i++) {
            CORBA::Any anyval;
            if (strcmp(activeData[i].name,"brightness") == 0)
                anyval <<= m_cameras[0]->brightness;
            else if (strcmp(activeData[i].name, "saturation") == 0)
                anyval <<= m_cameras[0]->saturation;
            else if (strcmp(activeData[i].name, "contrast") == 0)
                anyval <<= m_cameras[0]->contrast;
            else if (strcmp(activeData[i].name, "hue") == 0)
                anyval <<= m_cameras[0]->hue;
            else
                continue;
            //activeData[i].value = anyval;
            float val;
            activeData[i].value >>= val;
            std::cout << activeData[i].name << ":" << val << std::endl;
            config->set_configuration_set_values(aset);
        }
        config->activate_configuration_set(aset->id);
     */
    return RTC::RTC_OK;
}


/*
   RTC::ReturnCode_t VideoStream::onFinalize()
   {
   return RTC::RTC_OK;
   }
 */

RTC::ReturnCode_t VideoStream::onStartup(RTC::UniqueId ec_id)
{

    for (unsigned int i = 0; i < m_cameras.size (); i++)
        m_cameras[i]->start();

    return RTC::RTC_OK;
}


/*
   RTC::ReturnCode_t VideoStream::onShutdown(RTC::UniqueId ec_id)
   {
   return RTC::RTC_OK;
   }
 */


RTC::ReturnCode_t VideoStream::onActivated(RTC::UniqueId ec_id)
{
    return RTC::RTC_OK;
}


/*
   RTC::ReturnCode_t VideoStream::onDeactivated(RTC::UniqueId ec_id)
   {
   return RTC::RTC_OK;
   }
 */

RTC::ReturnCode_t VideoStream::onExecute (RTC::UniqueId ec_id)
{
    if (m_update_params)
    {
        m_cameras[m_camera_id]->updateBrightness(m_brightness);
        //        m_cameras[m_camera_id]->updateContrast(m_contrast);
        //        m_cameras[m_camera_id]->updateSaturation(m_saturation);
        //        m_cameras[m_camera_id]->updateHue(m_hue);
    }

    /*if (m_service0.numCapture != 0)
       {
        capture();
        if (m_service0.numCapture > 0)
            m_service0.numCapture--;
        m_MultiCameraImagesOut.write ();
       }*/
    return RTC::RTC_OK;
}

void VideoStream::capture()
{
    m_MultiCameraImages.error_code = 0;
    for (unsigned int i = 0; i < m_cameras.size (); i++)
    {
        m_MultiCameraImages.data.image_seq[i].image.format = Img::CF_RGB;
        m_MultiCameraImages.data.camera_set_id = 0;
        uchar *imgFrom = m_cameras[i]->capture();
        memcpy (m_MultiCameraImages.data.image_seq[i].image.raw_data.get_buffer(), imgFrom,
                m_MultiCameraImages.data.image_seq[i].image.raw_data.length() * sizeof (uchar));
        //std::cout << "[" << i << "] " << (unsigned int) imgFrom[1000] << " ";
    }
    //std::cout << std::endl;
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
void VideoStreamInit (RTC::Manager * manager)
{
    coil::Properties profile (videostream_spec);
    manager->registerFactory (profile,
                              RTC::Create < VideoStream >,
                              RTC::Delete < VideoStream >);
}
};
