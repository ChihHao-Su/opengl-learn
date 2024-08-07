#ifndef REF_INL
#define REF_INL

#include <memory>
#include <variant>

// 定义一个 concept，用于约束类型转换
template<typename From, typename To>
concept ConvertibleTo = std::is_convertible_v<From, To>;

template<typename T>
class FlexibleRef {
public:
	// 静态工厂方法，用于创建引用动态存储区对象的 FlexibleRef 对象
	static FlexibleRef makeFlexibleRefToDynObj(std::shared_ptr<T> dynObj) {
		FlexibleRef ref;
		ref.data = dynObj;
		return ref;
	}

	// 静态工厂方法，用于创建引用静态存储区对象的 FlexibleRef 对象
	static FlexibleRef makeFlexibleRefToStaticObj(T* staticObj) {
		FlexibleRef ref;
		ref.data = staticObj;
		return ref;
	}

	// 复制构造函数
	FlexibleRef(const FlexibleRef& other) : data(other.data) {}

	// 移动构造函数
	FlexibleRef(FlexibleRef&& other) noexcept : data(std::move(other.data)) {}

	// 模板复制构造函数，允许从 FlexibleRef<U> 构造 FlexibleRef<T>，前提是 T* 可以从 U* 转换
	template<ConvertibleTo<T*> U>
	FlexibleRef(const FlexibleRef<U>& other) : data(std::visit([](auto&& arg) -> std::variant<std::shared_ptr<T>, T*> {
		if constexpr (std::is_same_v<std::shared_ptr<U>, std::decay_t<decltype(arg)>>) {
			return std::static_pointer_cast<T>(arg);
		}
		else {
			return arg;
		}
		}, other.data)) {}

	// 模板移动构造函数，允许从 FlexibleRef<U> 移动构造 FlexibleRef<T>，前提是 T* 可以从 U* 转换
	template<ConvertibleTo<T*> U>
	FlexibleRef(FlexibleRef<U>&& other) noexcept : data(std::visit([](auto&& arg) -> std::variant<std::shared_ptr<T>, T*> {
		if constexpr (std::is_same_v<std::shared_ptr<U>, std::decay_t<decltype(arg)>>) {
			return std::static_pointer_cast<T>(std::move(arg));
		}
		else {
			return arg;
		}
		}, std::move(other.data))) {}

	// 复制赋值运算符
	FlexibleRef& operator=(const FlexibleRef& other) {
		if (this != &other) {
			data = other.data;
		}
		return *this;
	}

	// 移动赋值运算符
	FlexibleRef& operator=(FlexibleRef&& other) noexcept {
		if (this != &other) {
			data = std::move(other.data);
		}
		return *this;
	}

	// 模板赋值运算符，允许 FlexibleRef<U> 赋值给 FlexibleRef<T>，前提是 T* 可以从 U* 转换
	template<ConvertibleTo<T*> U>
	FlexibleRef& operator=(const FlexibleRef<U>& other) {
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

	// 私有构造函数，禁止外部直接创建 FlexibleRef 对象
	FlexibleRef() = default;

	template<typename U> friend class FlexibleRef;
};

#endif // REF_INL