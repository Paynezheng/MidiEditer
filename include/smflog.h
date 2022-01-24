#include <stdlib.h>  
#include <stdio.h>  
  
#ifdef SMF_LOG_ERROR
#undef SMF_LOG_ERROR
#endif

#ifdef SMF_LOG_INFO
#undef SMF_LOG_INFO
#endif

#ifdef SMF_LOG_DEBUG
#undef SMF_LOG_DEBUG
#endif

#ifdef SMF_LOG_FATAL
#undef SMF_LOG_FATAL
#endif

#ifdef SMF_LOG_TRACE
#undef SMF_LOG_TRACE
#endif

#ifdef SMF_LOG_WARN
#undef SMF_LOG_WARN
#endif

namespace smf
{

#define SMF_LOG_ERROR(fmt, ...) printf("[ERROR] \u001b[0;31m"); PRINT_SMF_LOG_INFO; printf(fmt, ##__VA_ARGS__); printf("\u001b[0m\n"); 
#define SMF_LOG_INFO(fmt, ...) printf("[INFO] \u001b[0;37m"); PRINT_SMF_LOG_INFO; printf(fmt, ##__VA_ARGS__); printf("\u001b[0m\n");
#define SMF_LOG_DEBUG(fmt, ...) printf("[DEBUG] \u001b[0;37m"); PRINT_SMF_LOG_INFO; printf(fmt, ##__VA_ARGS__); printf("\u001b[0m\n");
#define SMF_LOG_FATAL(fmt, ...) printf("[FATAL] \u001b[0;31m"); PRINT_SMF_LOG_INFO; printf(fmt, ##__VA_ARGS__); printf("\u001b[0m\n");
#define SMF_LOG_TRACE(fmt, ...) printf("[TRACE] \u001b[0;37m"); PRINT_SMF_LOG_INFO; printf(fmt, ##__VA_ARGS__); printf("\u001b[0m\n");
#define SMF_LOG_WARN(fmt, ...) printf("[WARN] \u001b[0;33m"); PRINT_SMF_LOG_INFO; printf(fmt, ##__VA_ARGS__); printf("\u001b[0m\n");

#define PRINT_SMF_LOG_INFO printf("[%s, %s][%s:%d], [func:%s]\t", \  
    __DATE__, __TIME__, __FILE__, __LINE__ , __FUNCTION__);  //); printf format; //, ##__VA_ARGS__);  

enum ELogLevel
{
    EN_LOG_LEVEL__TRACE = 0,
    EN_LOG_LEVEL__DEBUG,
    EN_LOG_LEVEL__INFO,
    EN_LOG_LEVEL__WARN,
    EN_LOG_LEVEL__ERROR,
    EN_LOG_LEVEL__FATAL,
};

}


