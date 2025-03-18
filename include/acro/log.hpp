#ifndef ACRO_LOG_HPP
#define ACRO_LOG_HPP

#include <spdlog/spdlog.h>

namespace acro {
namespace log {

/**
* @class DSSink
* @brief A logging sink for the NI Driver Station.
*
* This may be passed into @ref acro::log::setup_logging() as a valid sink.
*/
class DSSink : public spdlog::sinks::sink {
public:
	void set_pattern(const std::string& pattern) override;
	void set_formatter(std::unique_ptr<spdlog::formatter> _) override;

	void log(const spdlog::details::log_msg& msg) override;

	void flush() override;
private:
	std::string pattern = "{} [{}] - {}";
}; // class DSSink

/**
* @brief Initialize the logging system, with the specified sink and log level.
* @tparam T The logger sink to use. @see spdlog::sinks::sink.
* @param level The log level to use.
*/
template<typename T>
void setup_logging(spdlog::level::level_enum level) {
	auto sink = std::make_shared<T>();

	auto logger = std::make_shared<spdlog::logger>("ACRoLib", sink);

	logger->set_level(level);

	spdlog::set_default_logger(logger);

	spdlog::info("ACRoLib logging enabled!");
}
} // namespace log
} // namespace acro

#endif // ACRO_LOG_HPP

//![SOURCE] ./src/log.cpp
