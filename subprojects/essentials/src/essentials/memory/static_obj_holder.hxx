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


	/**
	 * 一个非动态存储期对象的 Holder。
	 * 
	 * 配合 StaticObjHolder 使用，用于方便调试。本类不提供任何内存管理功能。
	 *
	 * 当 StaticObjHolder 持有的非动态存储期对象销毁时，若仍存在引用
	 * 之的 StaticObjRef，程序将终止并显示错误信息。
	 */
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

		T* operator->() { return &obj; }
		T* operator&()  { return &obj; }

	private:
		T obj;
		_StaticObjHolderImpl impl;
	};
}

#endif // STATIC_OBJ_HOLDER_HXX