
#ifndef EXPORT_ME_H
#define EXPORT_ME_H

#ifdef OS_WIN

#ifdef ENGINE_EXPORT
#define EXPORTME __declspec(dllexport)
#else
#define EXPORTME __declspec(dllimport)
#endif

#else

#ifdef ENGINE_EXPORT
#define EXPORTME __attribute__((visibility("default")))
#else
#define EXPORTME
#endif

#endif

#endif // EXPORT_ME_H
