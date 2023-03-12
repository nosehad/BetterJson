#ifndef INLINE_H
    #define INLINE_H
    #ifndef __cplusplus
        #define EXTERN_I extern inline
        #define STATIC_I static inline
    #else
        #define EXTERN_I
        #define STATIC_I static inline
    #endif
#endif