// Included in CorePublic.h

//////////////////////////////////////////////////////////////////////////
// Configurations
#if defined(DEBUG) || defined(_DEBUG)
#   define BM_DEBUG         1
#elif defined(NDEBUG)
#   define BM_RELEASE       1
#else
#   error "Invalid Configuration"
#endif
//////////////////////////////////////////////////////////////////////////