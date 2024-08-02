#ifndef REF_INL
#define REF_INL

#include <memory>
#include <variant>

// 定义一个 concept，用于约束类型转换
template<typename From, typename To>
concept ConvertibleTo = std::is_convertible_v<From, To>;

template<typename T>
class Ref {
public:
	// 静态工厂方法，用于创建引用动态存储区对象的 Ref 对象
	static Ref makeRefToDynObj(std::shared_ptr<T> dynObj) {
		Ref ref;
		ref.data = dynObj;
		return ref;
	}

	// 静态工厂方法，用于创建引用静态存储区对象的 Ref 对象
	static Ref makeRefToStaticObj(T* staticObj) {
		Ref ref;
		ref.data = staticObj;
		return ref;
	}

	// 复制构造函数
	Ref(const Ref& other) : data(other.data) {}

	// 移动构造函数
	Ref(Ref&& other) noexcept : data(std::move(other.data)) {}

	// 模板复制构造函数，允许从 Ref<U> 构造 Ref<T>，前提是 T* 可以从 U* 转换
	template<ConvertibleTo<T*> U>
	Ref(const Ref<U>& other) : data(std::visit([](auto&& arg) -> std::variant<std::shared_ptr<T>, T*> {
		if constexpr (std::is_same_v<std::shared_ptr<U>, std::decay_t<decltype(arg)>>) {
			return std::static_pointer_cast<T>(arg);
		}
		else {
			return arg;
		}
		}, other.data)) {}

	// 模板移动构造函数，允许从 Ref<U> 移动构造 Ref<T>，前提是 T* 可以从 U* 转换
	template<ConvertibleTo<T*> U>
	Ref(Ref<U>&& other) noexcept : data(std::visit([](auto&& arg) -> std::variant<std::shared_ptr<T>, T*> {
		if constexpr (std::is_same_v<std::shared_ptr<U>, std::decay_t<decltype(arg)>>) {
			return std::static_pointer_cast<T>(std::move(arg));
		}
		else {
			return arg;
		}
		}, std::move(other.data))) {}

	// 复制赋值运算符
	Ref& operator=(const Ref& other) {
		if (this != &other) {
			data = other.data;
		}
		return *this;
	}

	// 移动赋值运算符
	Ref& operator=(Ref&& other) noexcept {
		if (this != &other) {
			data = std::move(other.data);
		}
		return *this;
	}

	// 模板赋值运算符，允许 Ref<U> 赋值给 Ref<T>，前提是 T* 可以从 U* 转换
	template<ConvertibleTo<T*> U>
	Ref& operator=(const Ref<U>& other) {
		data = std::visit([](auto&& arg) -> std::variant<std::shared_ptr<T>, T*> {
			if constexpr (std::is_same_v<std::shared_ptr<U>, std::decay_t<decltype(arg)>>) {
				return std::static_pointer_cast<T>(arg);
			}
			else {
				return arg;
			}
			}, other.data);
		return *this;
	}

	// 获取引用的对象
	T* get() const {
		return std::visit([](auto&& arg) -> T* {
			if constexpr (std::is_same_v<std::shared_ptr<T>, std::decay_t<decltype(arg)>>) {
				return arg.get();
			}
			else {
				return arg;
			}
			}, data);
	}

private:
	std::variant<std::shared_ptr<T>, T*> data;

	// 私有构造函数，禁止外部直接创建 Ref 对象
	Ref() = default;

	template<typename U> friend class Ref;
};

#endif // REF_INL