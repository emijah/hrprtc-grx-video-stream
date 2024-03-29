/*
   ImgSVC_impl.h

   Copyright (c) 2011 AIST  All Rights Reserved.
   Eclipse Public License v1.0 (http://www.eclipse.org/legal/epl-v10.html)
 */
// -*-C++-*-
/*!
 * @file  ImgSVC_impl.h
 * @brief Service implementation header of Img.idl
 */

#include "BasicDataTypeSkel.h"

#include "ImgSkel.h"

#ifndef IMGSVC_IMPL_H
#define IMGSVC_IMPL_H

class VideoStream;

/*!
 * @class CameraCaptureServiceSVC_impl
 * Example class implementing IDL interface Img::CameraCaptureService
 */
class CameraCaptureServiceSVC_impl
    : public virtual POA_Img::CameraCaptureService,
    public virtual PortableServer::RefCountServantBase
{
private:
    // Make sure all instances are built on the heap by making the
    // destructor non-public
    //virtual ~CameraCaptureServiceSVC_impl();

    VideoStream& m_comp;

public:
    /*!
     * @brief standard constructor
     */
    CameraCaptureServiceSVC_impl(VideoStream& comp);
    /*!
     * @brief destructor
     */
    virtual ~CameraCaptureServiceSVC_impl();

    // attributes and operations
    void take_one_frame();
};



#endif // IMGSVC_IMPL_H


