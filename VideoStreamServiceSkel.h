// -*- C++ -*-
/*!
 *
 * THIS FILE IS GENERATED AUTOMATICALLY!! DO NOT EDIT!!
 *
 * @file VideoStreamServiceSkel.h
 * @brief VideoStreamService server skeleton header wrapper code
 * @date Wed Dec  1 09:06:30 2010
 *
 */

#ifndef VIDEOSTREAMSERVICESKEL_H
#define VIDEOSTREAMSERVICESKEL_H

#include <rtm/config_rtc.h>
#undef PACKAGE_BUGREPORT
#undef PACKAGE_NAME
#undef PACKAGE_STRING
#undef PACKAGE_TARNAME
#undef PACKAGE_VERSION

#if   defined ORB_IS_TAO
#  include "VideoStreamServiceC.h"
#  include "VideoStreamServiceS.h"
#elif defined ORB_IS_OMNIORB
#  if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#    undef USE_stub_in_nt_dll
#  endif
#  include "VideoStreamService.hh"
#elif defined ORB_IS_MICO
#  include "VideoStreamService.h"
#elif defined ORB_IS_ORBIT2
#  include "/VideoStreamService-cpp-stubs.h"
#  include "/VideoStreamService-cpp-skels.h"
#else
#  error "NO ORB defined"
#endif
#endif							 // VIDEOSTREAMSERVICESKEL_H
