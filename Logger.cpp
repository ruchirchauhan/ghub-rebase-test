#include "Logger.h"

#include <iostream>
#include <mutex>
#include <pthread.h>
#include <array>

namespace sdvstreamer {

    constexpr uint32_t LOG_FILE_TAG_WIDTH = 56U;
    constexpr std::size_t LOG_MAX_SIZE = STREAMER_LOG_MAX_SIZE + LOG_FILE_TAG_WIDTH;

    inline constexpr std::size_t LOG_TAG_MAX = 100U;
    inline constexpr int THREAD_NAME_MAX = 26;
    // inline constexpr int CLASS_NAME_FORMAT_WIDTH = 26;
    constexpr std::string_view CLASS_LINE_NO_FORMAT_WIDTH = "4";
    // #ifdef __linux__
    //         constexpr std::string_view THREAD_NAME_FORMAT_WIDTH = "16";
    // #else
    //         constexpr std::string_view THREAD_NAME_FORMAT_WIDTH = "32";
    // #endif

#define CLASS_NAME_FORMAT_WIDTH "26"
#ifdef __linux__
#define THREAD_NAME_FORMAT_WIDTH "16"
#else
#define THREAD_NAME_FORMAT_WIDTH "32"
#endif

#if defined (__ANDROID__)

/* Android Logging */
    /**
     * @brief
     * Android Logging
     *
     * @param prefix
     * prefix - log priority
     * @param fname
     * fname - Tag name
     * @param lineno
     * lineno - line number
     * @param logmsg
     * logmsg - Log message to print.
     */
    void
    ALogMsg(android_LogPriority const prefix, const char *fname, int lineno, const char *logmsg) {

        std::array<char, LOG_TAG_MAX> tagging{};
        (void) snprintf(tagging.data(), tagging.size(),
                        "[IVS_%-*s]:%*d", CLASS_NAME_FORMAT_WIDTH,
                        fname, CLASS_LINE_NO_FORMAT_WIDTH, lineno);

        pthread_t const tid{pthread_self()};
        char thread_name[THREAD_NAME_MAX];
        (void) pthread_getname_np(tid, (char *) thread_name, sizeof(thread_name));

        (void) __android_log_print(prefix, tagging.data(),
                            "[%-*s]%s", THREAD_NAME_FORMAT_WIDTH,
                                   (char *) thread_name, logmsg);
    }

#else
    /* Sys Logging */
    void LogMsg( int8_t* const prefix, int8_t* const fname, int8_t* const logmsg) {
#if defined(NO_SDK_LOG)
        NOT_USED(prefix);
        NOT_USED(logmsg);
#else
        static std::mutex mtxLog;
        static char bufLog[LOG_MAX_SIZE];

        char buf_hms[32] = {0};
        struct timespec t;
        if (clock_gettime(CLOCK_REALTIME, &t) != 0) {
            (void)sprintf(buf_hms, "00:00:00");
        } else {
            struct tm info;
            (void)localtime_r(&t.tv_sec, &info);
            (void)strftime(buf_hms, sizeof(buf_hms), "%H:%M:%S", &info);
        }

        pthread_t tid = pthread_self();
        int8_t thread_name[THREAD_NAME_MAX];
        (void)pthread_getname_np(tid, reinterpret_cast<char *>(thread_name), sizeof(thread_name));
        {
            const std::lock_guard<std::mutex> lock(mtxLog);
            (void)snprintf(bufLog, sizeof(bufLog),
                    "[%s.%03lu]"
                    "[%2jd (%-" THREAD_NAME_FORMAT_WIDTH "s)]"
                    "[%s] %s",
                    buf_hms, (int64_t)(t.tv_nsec)/1000000, (intmax_t)tid, thread_name, prefix, logmsg);
            bufLog[sizeof(bufLog)-1U] = '\0';
            std::cerr << bufLog << std::endl;
        syslog(LOG_CRIT,"[IVS_%-" CLASS_NAME_FORMAT_WIDTH "s]%s", fname, bufLog);
        }
#endif
    }

#endif
}