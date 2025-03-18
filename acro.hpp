#pragma once
#ifdef ACRO_FEATURE_LOG
#ifndef ACRO_LOG_HPP
#define ACRO_LOG_HPP

#include <spdlog/spdlog.h>
#include <type_traits>

namespace acro {
namespace log {

class DSSink : public spdlog::sinks::sink {
public:
	void set_pattern(const std::string& pattern) override;
	void set_formatter(std::unique_ptr<spdlog::formatter> _) override;

	void log(const spdlog::details::log_msg& msg) override;

	void flush() override;
private:
	std::string pattern = "{} [{}] - {}";
}; // class DSSink

template<typename T>
typename std::enable_if<std::is_base_of<spdlog::sinks::sink, T>::value>::type
setup_logging(const spdlog::level::level_enum level) {
	auto sink = std::make_shared<T>();

	auto logger = std::make_shared<spdlog::logger>("ACRoLib", sink);

	logger->set_level(level);

	spdlog::set_default_logger(logger);

	spdlog::info("ACRoLib logging enabled!");
}
} // namespace log
} // namespace acro

#endif

#ifdef ACRO_IMPL

#include <iostream>

namespace acro {
namespace log {

void DSSink::set_pattern(const std::string &pattern) {
	this->pattern = pattern;
}

void DSSink::set_formatter(std::unique_ptr<spdlog::formatter> sink_formatter) {
	spdlog::warn("Attempted to set a formatter for DSSink, which is unsupported and will be ignored!");
}

void DSSink::log(const spdlog::details::log_msg& msg) {
	std::string message = fmt::format(this->pattern, msg.time, spdlog::level::to_string_view(msg.level), msg.payload);
		// TODO: WPILib logging
	std::cout << message << std::endl;
}

void DSSink::flush() {
	std::cout.flush();
}

} // namespace log
} // namespace acro
#endif
#endif