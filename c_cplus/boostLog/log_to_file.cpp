#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

#include <boost/log/trivial.hpp>
#include <boost/log/core.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <sstream>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
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

void init_log() {
    logging::add_file_log(
        // keywords::file_name = "sample_%N.log", // 文件名模板
        keywords::file_name = get_log_filename(),
        keywords::rotation_size = 10 * 1024 * 1024, // 每个日志文件的大小（10MB）
        keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0), // 每天凌晨旋转日志文件
        keywords::format = "[%TimeStamp%] [%ThreadID%] [%Severity%] %Message%" // 日志格式
    );

    // 设置全局日志属性
    logging::add_common_attributes();
}

// void set_log_level(boost::log::trivial::severity_level level) {
//     boost::log::core::get()->set_logging_enabled(level);
//     // boost::log::core::get()->set_filter(level);
// }

void set_log_level(boost::log::trivial::severity_level level) {
    boost::log::core::get()->set_filter(boost::log::trivial::severity >= level);
}

int main() {
    // 初始化日志系统
    init_log();

    // boost::log::trivial::severity_level level = boost::log::trivial::severity_level::info;

    set_log_level(boost::log::trivial::severity_level::info);

    // 记录一些日志消息
    BOOST_LOG_TRIVIAL(trace) << "A trace severity message";
    BOOST_LOG_TRIVIAL(debug) << "A debug severity message";
    BOOST_LOG_TRIVIAL(info) << "An informational severity message";
    BOOST_LOG_TRIVIAL(warning) << "A warning severity message";
    BOOST_LOG_TRIVIAL(error) << "An error severity message";
    BOOST_LOG_TRIVIAL(fatal) << "A fatal severity message";

    return 0;
}