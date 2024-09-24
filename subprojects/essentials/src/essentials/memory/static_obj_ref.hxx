#ifndef STATIC_OBJ_REF_HXX
#define STATIC_OBJ_REF_HXX

#include <memory>
#include <variant>

#include "static_obj_holder.hxx"

namespace Essentials::Memory
{
	/**
	 * 一个对 StaticObjHolder 的引用。
	 * 
	 * 配合 StaticObjHolder 使用。用于方便调试。本类不提供任何内存管理功能。
	 * 
	 * 当 StaticObjHolder 持有的非动态存储期对象销毁时，若仍存在引用
	 * 之的 StaticObjRef，程序将终止并显示错误信息。
	 */
	template<typename T>
	class StaticObjRef
	{
	public:
		StaticObjRef(StaticObjHolder<T>& holder) {
			assign(holder);
		}

		~StaticObjRef() {
			if(holder)
				holder->release();
		}

		StaticObjRef(const StaticObjRef<T>& other) = default;
		StaticObjRef(StaticObjRef<T>&& other) = default;

		void assign(StaticObjHolder<T>& newHolder) {
			holder->release();
			holder = std::addressof(newHolder);
			holder->retain();
		}

		StaticObjRef& operator=(const StaticObjRef<T>& other) {
			assign(*other.holder);
			return *this;
		}
		StaticObjRef& operator=(StaticObjHolder<T>& newHolder) {
			assign(newHolder);
			return *this;
		}

		T* operator&()  {
			return holder;
		}

		T* operator->() {
			return &*holder;
		}

		bool operator ==(const StaticObjRef<T>& other) const {
			return holder == other.holder;
		}

		bool operator ==(const T& obj) const {
			return &*holder == &obj;
		}


	private:
		StaticObjHolder<T> *holder;
	};

}


#endif // STATIC_OBJ_REF_HXX
