#define SUBSYS(name) __subsys_##name
#define DECL_SYBSYS(name) namespace __subsys_##name
#define DECL_SYBSYS_INIT_FUNC() void init()
#define IMPL_SYBSYS(name) namespace __subsys_##name
#define IMPL_SYBSYS_INIT_FUNC() void init()
#define INIT_SUBSYS(name) __subsys_##name::init()

#define IMPL_SUBSYS_INTERNAL namespace __internal
#define SUBSYS_INTERNAL __internal
