#ifndef G3_Export
#define G3_Export

#ifdef GEOMETRY3PLUS_EXPORTS
#define G3Export __declspec(dllexport)
#else
#define G3Export __declspec(dllimport)
#endif // GEOMETRY3PLUS_EXPORTS

#endif
