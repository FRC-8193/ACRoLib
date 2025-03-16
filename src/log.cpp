#include <acro/log.hpp>

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
