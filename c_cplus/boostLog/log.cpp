// #include <boost/log/trivial.hpp>
// int main(int, char*[])
// {
//     BOOST_LOG_TRIVIAL(trace) << "A trace severity message";
//     BOOST_LOG_TRIVIAL(debug) << "A debug severity message";
//     BOOST_LOG_TRIVIAL(info) << "An informational severity message";
//     BOOST_LOG_TRIVIAL(warning) << "A warning severity message";
//     BOOST_LOG_TRIVIAL(error) << "An error severity message";
//     BOOST_LOG_TRIVIAL(fatal) << "A fatal severity message";
//     return 0;
// }


///////////////////////////////////////////////////////////////////////////////////////
#include <boost/log/trivial.hpp>
#include <boost/log/core.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <sstream>

namespace logging = boost::log;
namespace keywords = boost::log::keywords;

std::string get_log_filename()
{
    // 获取当前时间
    auto now = boost::posix_time::second_clock::local_time();
    std::ostringstream oss;
    oss << boost::posix_time::to_iso_extended_string(now);
    // 替换 ':' 为 '-' 以便于文件名
    std::string filename = "log_" + oss.str() + ".log";
    return filename;
}

void init_logging()
{
    std::string log_filename = get_log_filename();

    logging::add_console_log(std::cout,
                             keywords::format = "[%TimeStamp%] [%Severity%]: %Message%");

    logging::add_file_log(log_filename,
                          keywords::format = "[%TimeStamp%] [%Severity%]: %Message%");

    logging::add_common_attributes();
}

int main()
{
    init_logging();

    BOOST_LOG_TRIVIAL(info) << "This is an informational message";
    BOOST_LOG_TRIVIAL(warning) << "This is a warning message";

    return 0;
}
