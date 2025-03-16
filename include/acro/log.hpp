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
