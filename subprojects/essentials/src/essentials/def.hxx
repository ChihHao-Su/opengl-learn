#include <memory>
#include <gsl/util>
#include <variant>

/**
 * 内存管理
 */
template<class T, class D = std::default_delete<T>>
using Box = std::unique_ptr<T, D>;

template<class T>
using Ref = std::shared_ptr<T>;

#define UNSAFE(sth) sth

#define FINALLY(actions) \
	auto finalAct = gsl::finally([&]{ \
		actions \
	});


/**
 * 抽象
 */
#define SATISFIES(traitName) \
	: private __trait_itfc_##traitName

#define DEF_TRAIT_ITFC(traitName) class __trait_itfc_##traitName

#define DEF_TRAIT_VARIANT(traitName, ...) \
	using traitName = std::variant<__VA_ARGS__>;

#define FUNC_CLASS struct