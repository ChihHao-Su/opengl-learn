#include "static_obj_holder.hxx"
#include "essentials/panic.hxx"

namespace Essentials::Memory
{
	_StaticObjHolderImpl::_StaticObjHolderImpl()
	{
	}
	_StaticObjHolderImpl::~_StaticObjHolderImpl()
	{
		if (refCount > 0) {
			panic("Static object destructed with non-zero reference count");
		}
	}

	void _StaticObjHolderImpl::retain() {
		refCount++;
	}

	void _StaticObjHolderImpl::release() {
		refCount--;
	}
}