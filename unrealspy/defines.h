// Move somewhere? 
// Define this when building

#if defined(FNAME_WIDECHAR)
    #define UTEXT_PASTE(x) L ## x
    #define FNAME_TYPE WIDECHAR
#elif defined(FNAME_ANSICHAR)
    #define UTEXT_PASTE(x) x
    #define FNAME_TYPE ANSICHAR
#else
    #error Define FNAME_WIDECHAR or FNAME_ANSICHAR
#endif

// Rename TO FNAME_TEXT or FNTEXT?
// TEXT() doesn't quite work for us as the FName types (widechar or ansichar) are game dependent.
#define UTEXT(x) UTEXT_PASTE(x)
