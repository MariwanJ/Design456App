//
// Basic instrumentation profiler by Cherno

// Usage: include this header file somewhere in your code (eg. precompiled header), and then use like:
//
//  FR_PROFILE_BEGIN_SESSION("Session Name", "FILENAME_.json);        // Begin session
// {
//     FR_PROFILE_SCOPE("Profiled Scope Name");   // Place code like this in scopes you'd like to include in profiling
//     // Code
// }
// FR_PROFILE_END_SESSION()                       // End Session
//
//
#include <string>
#include <chrono>
#include <algorithm>
#include <fstream>

#include <thread>

#include "Fr_Log.h"
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <string>
#include <thread>
#include <mutex>
#include <sstream>

namespace FR {
#pragma once
#include <chrono>
#include <fstream>
#include <iomanip>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>
#include <unordered_map>
#include <iostream>

    // Floating-point microseconds for high-precision timestamps
    using FloatingPointMicroseconds = std::chrono::duration<double, std::micro>;

    struct ProfileResult
    {
        std::string Name;
        FloatingPointMicroseconds Start;
        std::chrono::microseconds ElapsedTime;
        std::thread::id ThreadID;
    };

    struct InstrumentationSession
    {
        std::string Name;
    };

    class Instrumentor
    {
    public:
        Instrumentor(const Instrumentor&) = delete;
        Instrumentor(Instrumentor&&) = delete;

        static Instrumentor& Get()
        {
            static Instrumentor instance;
            return instance;
        }

        void BeginSession(const std::string& name, const std::string& filepath = "results.json")
        {
            std::lock_guard<std::mutex> lock(m_Mutex);

            if (m_CurrentSession)
            {
                InternalEndSession();
            }

            m_OutputStream.open(filepath);
            if (m_OutputStream.is_open())
            {
                m_CurrentSession = new InstrumentationSession{ name };
                WriteHeader();
            }
            else
            {
                std::cerr << "Instrumentor could not open results file: " << filepath << std::endl;
            }
        }

        void EndSession()
        {
            std::lock_guard<std::mutex> lock(m_Mutex);
            InternalEndSession();
        }

        void WriteProfile(const ProfileResult& result)
        {
            std::stringstream json;
            json << std::setprecision(3) << std::fixed;
            json << "{";
            json << "\"cat\":\"function\",";
            json << "\"dur\":" << result.ElapsedTime.count() << ",";
            json << "\"name\":\"" << result.Name << "\",";
            json << "\"ph\":\"X\",";
            json << "\"pid\":0,";
            json << "\"tid\":" << std::hash<std::thread::id>{}(result.ThreadID) << ",";
            json << "\"ts\":" << result.Start.count();
            json << "}";

            std::lock_guard<std::mutex> lock(m_Mutex);
            if (m_CurrentSession)
            {
                if (m_ProfileCount++ > 0)
                    m_OutputStream << ",";
                m_OutputStream << json.str();
                m_OutputStream.flush();
            }
        }

    private:
        Instrumentor()
            : m_CurrentSession(nullptr), m_ProfileCount(0)
        {
        }

        ~Instrumentor()
        {
            EndSession();
        }

        void WriteHeader()
        {
            m_OutputStream << "{\"otherData\": {},\"traceEvents\":[";
            m_OutputStream.flush();
        }

        void WriteFooter()
        {
            m_OutputStream << "]}";
            m_OutputStream.flush();
        }

        void InternalEndSession()
        {
            if (m_CurrentSession)
            {
                WriteFooter();
                m_OutputStream.close();
                delete m_CurrentSession;
                m_CurrentSession = nullptr;
                m_ProfileCount = 0;
            }
        }

    private:
        std::mutex m_Mutex;
        InstrumentationSession* m_CurrentSession;
        std::ofstream m_OutputStream;
        size_t m_ProfileCount;
    };

    class InstrumentationTimer
    {
    public:
        InstrumentationTimer(const char* name)
            : m_Name(name), m_Stopped(false)
        {
            m_StartTimepoint = std::chrono::steady_clock::now();
        }

        ~InstrumentationTimer()
        {
            if (!m_Stopped)
                Stop();
        }

        void Stop()
        {
            auto endTimepoint = std::chrono::steady_clock::now();
            FloatingPointMicroseconds highResStart{ m_StartTimepoint.time_since_epoch() };
            auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(endTimepoint - m_StartTimepoint);

            Instrumentor::Get().WriteProfile({ m_Name, highResStart, elapsedTime, std::this_thread::get_id() });

            m_Stopped = true;
        }

    private:
        const char* m_Name;
        std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
        bool m_Stopped;
    };

    namespace InstrumentorUtils {

        template <size_t N>
        struct ChangeResult
        {
            char Data[N];
        };

        template <size_t N, size_t K>
        constexpr auto CleanupOutputString(const char(&expr)[N], const char(&remove)[K])
        {
            ChangeResult<N> result = {};
            size_t srcIndex = 0;
            size_t dstIndex = 0;

            while (srcIndex < N - 1) // skip null terminator
            {
                size_t matchIndex = 0;
                while (matchIndex < K - 1 && expr[srcIndex + matchIndex] == remove[matchIndex])
                    matchIndex++;

                if (matchIndex == K - 1)
                    srcIndex += matchIndex;

                result.Data[dstIndex++] = expr[srcIndex] == '"' ? '\'' : expr[srcIndex];
                srcIndex++;
            }

            result.Data[dstIndex] = '\0'; // null terminate
            return result;
        }

    } // namespace InstrumentorUtils

    // Usage macros (optional, for convenience)
#define PROFILE_SCOPE(name) InstrumentationTimer timer##__LINE__(name)
#define PROFILE_FUNCTION() PROFILE_SCOPE(__FUNCTION__)


    //Activate - Or deactivate using FR_PROFILE macro
    #define FR_PROFILE 1
    #if FR_PROFILE
        // Resolve which function signature macro will be used. Note that this only
        // is resolved when the (pre)compiler starts, so the syntax highlighting
        // could mark the wrong one in your editor!
    #if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
    #define FR_FUNC_SIG __PRETTY_FUNCTION__
    #elif defined(__DMC__) && (__DMC__ >= 0x810)
    #define FR_FUNC_SIG __PRETTY_FUNCTION__
    #elif (defined(__FUNCSIG__) || (_MSC_VER))
    #define FR_FUNC_SIG __FUNCSIG__
    #elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
    #define FR_FUNC_SIG __FUNCTION__
    #elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
    #define FR_FUNC_SIG __FUNC__
    #elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
    #define FR_FUNC_SIG __func__
    #elif defined(__cplusplus) && (__cplusplus >= 201103)
    #define FR_FUNC_SIG __func__
    #else
    #define FR_FUNC_SIG "FR_FUNC_SIG unknown!"
    #endif

    #define FR_PROFILE_BEGIN_SESSION(name, filepath) ::FR::Instrumentor::Get().BeginSession(name, filepath)
    #define FR_PROFILE_END_SESSION() ::FR::Instrumentor::Get().EndSession()
    #define FR_PROFILE_SCOPE_LINE2(name, line) constexpr auto fixedName##line = ::FR::InstrumentorUtils::CleanupOutputString(name, "__cdecl ");\
											       ::FR::InstrumentationTimer timer##line(fixedName##line.Data)
    #define FR_PROFILE_SCOPE_LINE(name, line) FR_PROFILE_SCOPE_LINE2(name, line)
    #define FR_PROFILE_SCOPE(name) FR_PROFILE_SCOPE_LINE(name, __LINE__)
    #define FR_PROFILE_FUNCTION() FR_PROFILE_SCOPE(FR_FUNC_SIG)
    #else
    #define FR_PROFILE_BEGIN_SESSION(name, filepath)
    #define FR_PROFILE_END_SESSION()
    #define FR_PROFILE_SCOPE(name)
    #define FR_PROFILE_FUNCTION()
    #endif
}