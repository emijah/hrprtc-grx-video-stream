// -*-C++-*-
/*!
 * @file  VideoStreamServiceSVC_impl.cpp
 * @brief Service implementation code of VideoStreamService.idl
 *
 */

#include "VideoStreamServiceSVC_impl.h"

/*
 * Example implementational code for IDL interface VideoStreamService
 */
VideoStreamServiceSVC_impl::VideoStreamServiceSVC_impl ()
{
	// Please add extra constructor code here.
	numCapture = 0;
}


VideoStreamServiceSVC_impl::~VideoStreamServiceSVC_impl ()
{
	// Please add extra destructor code here.
}


/*
 * Methods corresponding to IDL attributes and operations
 */
void
VideoStreamServiceSVC_impl::capture (::CORBA::Long times)
{
	numCapture = times;
}


// End of example implementational code
