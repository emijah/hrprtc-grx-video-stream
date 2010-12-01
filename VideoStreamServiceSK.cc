// This file is generated by omniidl (C++ backend)- omniORB_4_1. Do not edit.

#include "VideoStreamService.hh"
#include <omniORB4/IOP_S.h>
#include <omniORB4/IOP_C.h>
#include <omniORB4/callDescriptor.h>
#include <omniORB4/callHandle.h>
#include <omniORB4/objTracker.h>

OMNI_USING_NAMESPACE (omni)
static const char *_0RL_library_version = omniORB_4_1;

VideoStreamService_ptr VideoStreamService_Helper::_nil ()
{
	return::VideoStreamService::_nil ();
}


::CORBA::Boolean VideoStreamService_Helper::is_nil (::
VideoStreamService_ptr p)
{
	return::CORBA::is_nil (p);

}


void
VideoStreamService_Helper::release (::VideoStreamService_ptr p)
{
	::CORBA::release (p);
}


void
VideoStreamService_Helper::marshalObjRef (::VideoStreamService_ptr obj,
cdrStream & s)
{
	::VideoStreamService::_marshalObjRef (obj, s);
}


VideoStreamService_ptr
VideoStreamService_Helper::unmarshalObjRef (cdrStream & s)
{
	return::VideoStreamService::_unmarshalObjRef (s);
}


void
VideoStreamService_Helper::duplicate (::VideoStreamService_ptr obj)
{
	if (obj && !obj->_NP_is_nil ())
		omni::duplicateObjRef (obj);
}


VideoStreamService_ptr
VideoStreamService::_duplicate (::VideoStreamService_ptr obj)
{
	if (obj && !obj->_NP_is_nil ())
		omni::duplicateObjRef (obj);
	return obj;
}


VideoStreamService_ptr VideoStreamService::_narrow (::CORBA::Object_ptr obj)
{
	if (!obj || obj->_NP_is_nil () || obj->_NP_is_pseudo ())
		return _nil ();
	_ptr_type
		e = (_ptr_type) obj->_PR_getobj ()->_realNarrow (_PD_repoId);
	return e ? e : _nil ();
}


VideoStreamService_ptr
VideoStreamService::_unchecked_narrow (::CORBA::Object_ptr obj)
{
	if (!obj || obj->_NP_is_nil () || obj->_NP_is_pseudo ())
		return _nil ();
	_ptr_type e = (_ptr_type) obj->_PR_getobj ()->_uncheckedNarrow (_PD_repoId);
	return e ? e : _nil ();
}


VideoStreamService_ptr VideoStreamService::_nil ()
{
	#ifdef OMNI_UNLOADABLE_STUBS
	static _objref_VideoStreamService
		_the_nil_obj;
	return &_the_nil_obj;
	#else
	static _objref_VideoStreamService *
		_the_nil_ptr = 0;
	if (!_the_nil_ptr)
	{
		omni::nilRefLock ().lock ();
		if (!_the_nil_ptr)
		{
			_the_nil_ptr = new _objref_VideoStreamService;
			registerNilCorbaObject (_the_nil_ptr);
		}
		omni::nilRefLock ().unlock ();
	}
	return _the_nil_ptr;
	#endif
}


const char *
VideoStreamService::_PD_repoId = "IDL:VideoStreamService:1.0";

_objref_VideoStreamService::~_objref_VideoStreamService ()
{

}


_objref_VideoStreamService::_objref_VideoStreamService (omniIOR * ior, omniIdentity * id):
omniObjRef (::VideoStreamService::_PD_repoId, ior, id,
1)
{
	_PR_setobj (this);
}


void *
_objref_VideoStreamService::_ptrToObjRef (const char *id)
{
	if (id ==::VideoStreamService::_PD_repoId)
		return (::VideoStreamService_ptr) this;

	if (id ==::CORBA::Object::_PD_repoId)
		return (::CORBA::Object_ptr) this;

	if (omni::strMatch (id,::VideoStreamService::_PD_repoId))
		return (::VideoStreamService_ptr) this;

	if (omni::strMatch (id,::CORBA::Object::_PD_repoId))
		return (::CORBA::Object_ptr) this;

	return 0;
}


// Proxy call descriptor class. Mangled signature:
//  void_i_clong
class _0RL_cd_35cc28abecf0f672_00000000:public omniCallDescriptor
{
	public:
		inline _0RL_cd_35cc28abecf0f672_00000000 (LocalCallFn lcfn, const char *op_, size_t oplen, _CORBA_Boolean upcall = 0):
		omniCallDescriptor (lcfn, op_, oplen, 0, 0, 0,
			upcall)
		{

		}

		void marshalArguments (cdrStream &);
		void unmarshalArguments (cdrStream &);

		::CORBA::Long arg_0;
};

void
_0RL_cd_35cc28abecf0f672_00000000::marshalArguments (cdrStream & _n)
{
	arg_0 >>= _n;

}


void
_0RL_cd_35cc28abecf0f672_00000000::unmarshalArguments (cdrStream & _n)
{
	(::CORBA::Long &) arg_0 <<= _n;

}


// Local call call-back function.
static void
_0RL_lcfn_35cc28abecf0f672_10000000 (omniCallDescriptor * cd,
omniServant * svnt)
{
	_0RL_cd_35cc28abecf0f672_00000000 *tcd =
		(_0RL_cd_35cc28abecf0f672_00000000 *) cd;
	_impl_VideoStreamService *impl =
		(_impl_VideoStreamService *) svnt->
		_ptrToInterface (VideoStreamService::_PD_repoId);
	impl->capture (tcd->arg_0);

}


void
_objref_VideoStreamService::capture (::CORBA::Long times)
{
	_0RL_cd_35cc28abecf0f672_00000000
		_call_desc (_0RL_lcfn_35cc28abecf0f672_10000000, "capture", 8);
	_call_desc.arg_0 = times;

	_invoke (_call_desc);

}


_pof_VideoStreamService::~_pof_VideoStreamService ()
{
}


omniObjRef *
_pof_VideoStreamService::newObjRef (omniIOR * ior, omniIdentity * id)
{
	return new::_objref_VideoStreamService (ior, id);
}


::CORBA::Boolean _pof_VideoStreamService::is_a (const char *id) const const
{
	if (omni::ptrStrMatch (id,::VideoStreamService::_PD_repoId))
		return 1;

	return 0;
}


const _pof_VideoStreamService
_the_pof_VideoStreamService;

_impl_VideoStreamService::~_impl_VideoStreamService ()
{
}


::CORBA::Boolean
_impl_VideoStreamService::_dispatch (omniCallHandle & _handle)
{
	const char *op = _handle.operation_name ();

	if (omni::strMatch (op, "capture"))
	{

		_0RL_cd_35cc28abecf0f672_00000000
			_call_desc (_0RL_lcfn_35cc28abecf0f672_10000000, "capture", 8, 1);

		_handle.upcall (this, _call_desc);
		return 1;
	}

	return 0;
}


void *
_impl_VideoStreamService::_ptrToInterface (const char *id)
{
	if (id ==::VideoStreamService::_PD_repoId)
		return (::_impl_VideoStreamService *) this;

	if (id ==::CORBA::Object::_PD_repoId)
		return (void *) 1;

	if (omni::strMatch (id,::VideoStreamService::_PD_repoId))
		return (::_impl_VideoStreamService *) this;

	if (omni::strMatch (id,::CORBA::Object::_PD_repoId))
		return (void *) 1;
	return 0;
}


const char *
_impl_VideoStreamService::_mostDerivedRepoId ()
{
	return::VideoStreamService::_PD_repoId;
}


POA_VideoStreamService::~POA_VideoStreamService ()
{
}
