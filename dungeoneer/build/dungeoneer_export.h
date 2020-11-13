
#ifndef DUNGEONEER_EXPORT_H
#define DUNGEONEER_EXPORT_H

#ifdef DUNGEONEER_STATIC_DEFINE
#  define DUNGEONEER_EXPORT
#  define DUNGEONEER_NO_EXPORT
#else
#  ifndef DUNGEONEER_EXPORT
#    ifdef dungeoneer_EXPORTS
        /* We are building this library */
#      define DUNGEONEER_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define DUNGEONEER_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef DUNGEONEER_NO_EXPORT
#    define DUNGEONEER_NO_EXPORT 
#  endif
#endif

#ifndef DUNGEONEER_DEPRECATED
#  define DUNGEONEER_DEPRECATED __declspec(deprecated)
#endif

#ifndef DUNGEONEER_DEPRECATED_EXPORT
#  define DUNGEONEER_DEPRECATED_EXPORT DUNGEONEER_EXPORT DUNGEONEER_DEPRECATED
#endif

#ifndef DUNGEONEER_DEPRECATED_NO_EXPORT
#  define DUNGEONEER_DEPRECATED_NO_EXPORT DUNGEONEER_NO_EXPORT DUNGEONEER_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef DUNGEONEER_NO_DEPRECATED
#    define DUNGEONEER_NO_DEPRECATED
#  endif
#endif

#endif /* DUNGEONEER_EXPORT_H */
