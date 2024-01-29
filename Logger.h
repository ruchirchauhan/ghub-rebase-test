#ifndef STREAMER_LOGGER_H_
#define STREAMER_LOGGER_H_

#include <stdio.h>
#include <syslog.h>

#if defined(__ANDROID__)
    #include <android/log.h>
#endif

inline constexpr size_t STREAMER_LOG_MAX_SIZE = 1024;
#define __SHORT_FILE__ (__builtin_strrchr(__FILE__, '/') ? __builtin_strrchr(__FILE__, '/') + 1 : __FILE__)

#if defined (__ANDROID__)
    /* Android Logging */
    #define LogInfo(...) ANDROID_LOG(ANDROID_LOG_INFO, __SHORT_FILE__, __VA_ARGS__)
    #define LogWarn(...) ANDROID_LOG(ANDROID_LOG_WARN, __SHORT_FILE__, __VA_ARGS__)
    #define LogErr(...) ANDROID_LOG(ANDROID_LOG_ERROR, __SHORT_FILE__, __VA_ARGS__)
    #define LogDebug(...) ANDROID_LOG(ANDROID_LOG_DEBUG, __SHORT_FILE__, __VA_ARGS__)

    /* Android Logging with custom tag */
    #define ALOGInfo(tag, ...) __android_log_print(ANDROID_LOG_INFO, tag, __VA_ARGS__)
    #define ALOGWarn(tag, ...) __android_log_print(ANDROID_LOG_WARN, tag, __VA_ARGS__)
    #define ALOGErr(tag, ...) __android_log_print(ANDROID_LOG_ERROR, tag, __VA_ARGS__)
    #define ALOGDebug(tag, ...) __android_log_print(ANDROID_LOG_DEBUG, tag, __VA_ARGS__)

    #define ANDROID_LOG(sev, fname, ...) do{  char szBuf[STREAMER_LOG_MAX_SIZE]; \
        (void)snprintf(szBuf, sizeof(szBuf), __VA_ARGS__); \
        szBuf[sizeof(szBuf)-1u] = '\0';sdvstreamer::ALogMsg((sev), fname, __LINE__, szBuf); \
    } while(false)

    namespace sdvstreamer {
        void ALogMsg(android_LogPriority const prefix, const char* fname, int lineno, const char* logmsg);
    }

#else
    /* Sys Logging */
    #define LogInfo(...)         STREAMER_LOG("INF", __SHORT_FILE__, __VA_ARGS__)
    #define LogInfo1345(...)         STREAMER_LOG("INF", __SHORT_FILE__, __VA_ARGS__)
    #define LogWarn(...)         STREAMER_LOG("WRN", __SHORT_FILE__, __VA_ARGS__)
    #define LogWarn1(...)         STREAMER_LOG("WRN", __SHORT_FILE__, __VA_ARGS__)


    #define LogErr(...)          STREAMER_LOG("ERR", __SHORT_FILE__, __VA_ARGS__)
    #define DebugErr(fmt, ...)   LogErr("%s:%d-" fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__)
    #define DebugErr1(fmt, ...)   LogErr("%s:%d-" fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__)

    #define STREAMER_LOG(sev, fname, ...) do { char szBuf[STREAMER_LOG_MAX_SIZE]; \
        (void)snprintf(szBuf, sizeof(szBuf), __VA_ARGS__); \
        szBuf[sizeof(szBuf)-1u] = '\0'; LogMsg((sev), fname, szBuf); \
    } while(false)

    void LogMsg(const char* prefix, const char* fname, const char* logmsg);
    void LogMsg1(const char* prefix, const char* fname, const char* logmsg);
    void LogMsg2(const char* prefix, const char* fname, const char* logmsg);
    void LogMsg2(const char* prefix, const char* fname, const char* logmsg);
    void LogMsg2(const char* prefix, const char* fname, const char* logmsg);
    void LogMsg2(const char* prefix, const char* fname, const char* logmsg);
    void LogMsg2(const char* prefix, const char* fname, const char* logmsg);
    void LogMsg2(const char* prefix, const char* fname, const char* logmsg);
#endif

#endif /* STREAMER_LOGGER_H_ */
