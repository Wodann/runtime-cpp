#ifndef MUN_RUNTIME_BINDINGS_H_
#define MUN_RUNTIME_BINDINGS_H_

/* Generated with cbindgen:0.9.1 */

#include <stdbool.h>
#include <stdint.h>

/**
 * A type that represents the privacy level of modules, functions, or variables.
 */
enum MunPrivacy
#ifdef __cplusplus
  : uint8_t
#endif // __cplusplus
 {
    /**
     * Publicly (and privately) accessible
     */
    Public = 0,
    /**
     * Privately accessible
     */
    Private = 1,
};
#ifndef __cplusplus
typedef uint8_t MunPrivacy;
#endif // __cplusplus

typedef uintptr_t MunToken;

/**
 * A C-style handle to an error.
 */
typedef struct {
    MunToken _0;
} MunErrorHandle;

/**
 * A C-style handle to a runtime.
 */
typedef struct {
    void *_0;
} MunRuntimeHandle;

/**
 * Represents a globally unique identifier (GUID).
 *
 * GUIDs are generated by taking the MD5 hash of a type's name.
 *
 * <div rustbindgen derive="Clone" derive="Copy" derive="Debug" derive="PartialEq"></div>
 */
typedef struct {
    /**
     * 16-byte MD5 hash
     */
    uint8_t b[16];
} MunGuid;

/**
 * Represents the type declaration for a value type.
 *
 * TODO: add support for structs, polymorphism, enumerations, type parameters, generic type definitions, and constructed generic types.
 *
 * <div rustbindgen derive="Debug"></div>
 */
typedef struct {
    /**
     * Type GUID
     */
    MunGuid guid;
    /**
     * Type name
     */
    const char *name;
} MunTypeInfo;

/**
 * Represents a function signature.
 *
 * <div rustbindgen derive="Clone" derive="Debug"></div>
 */
typedef struct {
    /**
     * Function name
     */
    const char *name;
    /**
     * Argument types
     */
    const MunTypeInfo *arg_types;
    /**
     * Optional return type
     */
    const MunTypeInfo *return_type;
    /**
     * Number of argument types
     */
    uint16_t num_arg_types;
    /**
     * Function accessibility level
     */
    MunPrivacy privacy;
} MunFunctionSignature;

/**
 * Represents a function declaration.
 *
 * `fn_ptr` can be used to call the declared function.
 *
 * <div rustbindgen derive="Clone" derive="Debug"></div>
 */
typedef struct {
    /**
     * Function signature
     */
    MunFunctionSignature signature;
    /**
     * Function pointer
     */
    const void *fn_ptr;
} MunFunctionInfo;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * Destructs the error corresponding to `error_handle`.
 */
void mun_error_destroy(MunErrorHandle error_handle);

/**
 * Retrieves the error message corresponding to `error_handle`. If the `error_handle` exists, a
 * valid `char` pointer is returned, otherwise a null-pointer is returned.
 */
const char *mun_error_message(MunErrorHandle error_handle);

/**
 * Constructs a new runtime that loads the library at `library_path` and its dependencies. If
 * successful, the runtime `handle` is set, otherwise a non-zero error handle is returned.
 *
 * If a non-zero error handle is returned, it must be manually destructed using
 * [`mun_error_destroy`].
 *
 * The runtime must be manually destructed using [`mun_runtime_destroy`].
 *
 * TODO: expose interval at which the runtime's file watcher operates.
 *
 * # Safety
 *
 * This function receives raw pointers as parameters. If any of the arguments is a null pointer,
 * an error will be returned. Passing pointers to invalid data, will lead to undefined behavior.
 */
MunErrorHandle mun_runtime_create(const char *library_path, MunRuntimeHandle *handle);

/**
 * Destructs the runtime corresponding to `handle`.
 */
void mun_runtime_destroy(MunRuntimeHandle handle);

/**
 * Retrieves the [`FunctionInfo`] for `fn_name` from the runtime corresponding to `handle`. If
 * successful, `has_fn_info` and `fn_info` are set, otherwise a non-zero error handle is returned.
 *
 * If a non-zero error handle is returned, it must be manually destructed using
 * [`mun_error_destroy`].
 *
 * # Safety
 *
 * This function receives raw pointers as parameters. If any of the arguments is a null pointer,
 * an error will be returned. Passing pointers to invalid data, will lead to undefined behavior.
 */
MunErrorHandle mun_runtime_get_function_info(MunRuntimeHandle handle,
                                             const char *fn_name,
                                             bool *has_fn_info,
                                             MunFunctionInfo *fn_info);

/**
 * Updates the runtime corresponding to `handle`. If successful, `updated` is set, otherwise a
 * non-zero error handle is returned.
 *
 * If a non-zero error handle is returned, it must be manually destructed using
 * [`mun_error_destroy`].
 *
 * # Safety
 *
 * This function receives raw pointers as parameters. If any of the arguments is a null pointer,
 * an error will be returned. Passing pointers to invalid data, will lead to undefined behavior.
 */
MunErrorHandle mun_runtime_update(MunRuntimeHandle handle, bool *updated);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif /* MUN_RUNTIME_BINDINGS_H_ */
