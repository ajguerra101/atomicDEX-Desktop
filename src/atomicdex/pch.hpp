#pragma once

#if defined(_WIN32) || defined(WIN32)
#    ifndef GLOG_NO_ABBREVIATED_SEVERITIES
#        define GLOG_NO_ABBREVIATED_SEVERITIES
#    endif
#endif

//! Std headers
#include <map>

#ifdef __APPLE__
#    include <Availability.h>
#endif

//! Global Helpers
#if defined(PREFER_BOOST_FILESYSTEM)
#    include <boost/filesystem.hpp>
namespace fs        = boost::filesystem;
using fs_error_code = boost::system::error_code;
#    define ANTARA_BOOST_FILESYTEM
#else
#    if __has_include(<filesystem>)
#        include <filesystem>
namespace fs        = std::filesystem;
using fs_error_code = std::error_code;
#        define ANTARA_STD_FILESYTEM
#    elif __has_include(<boost/filesystem.hpp>)
#        include <boost/filesystem.hpp>
namespace fs        = boost::filesystem;
using fs_error_code = boost::system::error_code;
#        define ANTARA_BOOST_FILESYTEM
#    endif
#endif

constexpr auto
get_override_options()
{
#if defined(ANTARA_STD_FILESYTEM)
    return fs::copy_options::overwrite_existing;
#elif defined(ANTARA_BOOST_FILESYTEM)
    return fs::copy_option::overwrite_if_exists;
#endif
}

constexpr std::size_t operator"" _sz(unsigned long long n) { return n; }

template <typename T>
constexpr std::size_t
bit_size() noexcept
{
    return sizeof(T) * CHAR_BIT;
}

template <class Key, class T, class Compare, class Alloc, class Pred>
void
erase_if(std::map<Key, T, Compare, Alloc>& c, Pred pred)
{
    for (auto i = c.begin(), last = c.end(); i != last;)
    {
        if (pred(*i))
        {
            i = c.erase(i);
        }
        else
        {
            ++i;
        }
    }
}

template <class... Ts>
struct overloaded : Ts...
{
    using Ts::operator()...;
};
template <class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;


//! Boost Headers
#include <boost/algorithm/string/trim.hpp>
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>
using t_float_50 = boost::multiprecision::cpp_dec_float_50;
using t_rational = boost::multiprecision::cpp_rational;

inline std::string
get_formated_float(t_float_50 value)
{
    std::stringstream ss;
    ss.precision(8);
    ss << std::fixed << value;
    return ss.str();
}

inline std::string
adjust_precision(const std::string& current)
{
    std::string       result;
    std::stringstream ss;
    t_float_50        current_f(current);

    ss << std::fixed << std::setprecision(8) << current_f;
    result = ss.str();

    boost::trim_right_if(result, boost::is_any_of("0"));
    boost::trim_right_if(result, boost::is_any_of("."));
    return result;
}

#pragma clang diagnostic pop

#include <spdlog/async.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

//! SDK Headers
#include <antara/gaming/core/open.url.browser.hpp>

namespace ag = antara::gaming;
