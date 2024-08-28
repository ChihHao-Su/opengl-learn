#ifndef STATIC_OBJ_REF_HXX
#define STATIC_OBJ_REF_HXX

#include <memory>
#include <variant>

#include "static_obj_holder.hxx"

namespace Essentials::Memory
{
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
			holder.release();
			holder = &newHolder;
			holder.sustain();
		}

		StaticObjRef& operator=(const StaticObjRef<T>& other) {
			assign(other.holder);
			return this;
		}
		StaticObjRef& operator=(StaticObjHolder<T>& newHolder) {
			assign(newHolder);
			return this;
		}

		T* operator&() const {
			return holder;
		}

		T& operator->() const {
			return &holder;
		}


	private:
		StaticObjHolder<T> *holder;
	};

}


#endif // STATIC_OBJ_REF_HXX