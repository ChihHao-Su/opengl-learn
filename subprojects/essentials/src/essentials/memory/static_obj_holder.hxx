#ifndef STATIC_OBJ_HOLDER_HXX
#define STATIC_OBJ_HOLDER_HXX

#include <utility>

namespace Essentials::Memory
{

	class _StaticObjHolderImpl
	{
	public:
		_StaticObjHolderImpl();
		~_StaticObjHolderImpl();
		void retain();
		void release();

	private:
		int refCount;
	};

	template<class T>
	class StaticObjHolder {
	public:
		//template<typename... Args>
		//StaticObjHolder(Args&&... args) : obj(std::forward<Args>(args)...) { }

		// 
		StaticObjHolder(T obj): obj(obj) { }

		void retain() {
			impl.retain();
		}
		void release() {
			impl.release();
		}

		T* operator->() const { return &obj; }
		T* operator&() const { return &obj; }

	private:
		T obj;
		_StaticObjHolderImpl impl;
	};
}

#endif // STATIC_OBJ_HOLDER_HXX