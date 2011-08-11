// -*-C++-*-
/*!
 * @file  VideoStreamServiceSVC_impl.h
 * @brief Service implementation header of VideoStreamService.idl
 *
 */
#ifndef VIDEOSTREAMSERVICESVC_IMPL_H
#define VIDEOSTREAMSERVICESVC_IMPL_H

//#include "VideoStreamServiceSkel.h"
#include "VideoStreamService.hh"

/*
 * Example class implementing IDL interface VideoStreamService
 */
class VideoStreamServiceSVC_impl:public virtual POA_OpenHRP::VideoStreamService,
public virtual
PortableServer::RefCountServantBase
{
	private:
		// Make sure all instances are built on the heap by making the
		// destructor non-public
		//virtual ~VideoStreamServiceSVC_impl();

	public:
		// standard constructor
		VideoStreamServiceSVC_impl ();
		virtual ~
			VideoStreamServiceSVC_impl ();

		// attributes and operations
		void
			capture (::CORBA::Long times);
		int
			numCapture;
};
#endif							 // VIDEOSTREAMSERVICESVC_IMPL_H
