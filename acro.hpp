#pragma once
#ifdef ACRO_FEATURE_LOG
#ifndef ACRO_LOG_HPP
#define ACRO_LOG_HPP

#include <spdlog/spdlog.h>
#include <spdlog/sinks/sink.h>
#include <spdlog/fmt/bundled/chrono.h>

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
#ifdef ACRO_FEATURE_MOTOR
#include <memory>
#include <unordered_map>
#include <typeindex>

#ifndef ACRO_BASE_MOTOR_HPP
#define ACRO_BASE_MOTOR_HPP

namespace acro {

/**
* @brief A base motor/motor controller interface.
* Classes implementing this interface should define a struct Config, a Constructor(const Config&), and implement all pure virtual functions.
* NOTE: The Config struct should include a using MotorType = X; where X is the class implementing BaseMotorImpl.
*/
class BaseMotorImpl {
public:
	struct Config {
		using MotorType = BaseMotorImpl;
	};

	inline BaseMotorImpl() {}

	/**
	* @brief Check if the motor was created properly and has no fatal errors.
	*/
	virtual bool is_ok() = 0;

	template<typename T>
	T *get_feature() {
		if (this->features.find(typeid(T)) != this->features.end()) {
			return (T *) this->features.at(typeid(T));
		}

		return (T *)nullptr;
	}
protected:
	std::unordered_map<std::type_index, void *> features;
}; // class BaseMotorImpl

/**
* @brief A software interface with a motor or motor controller.
*/
class Motor {
public:
	/**
	* @brief Create a new motor.
	* @tparam T The motor controller implementation type. (See @ref acro::BaseMotorImpl)
	* @param config The configuration, corresponding to the specified hardware.
	*/
	template<typename T>
	Motor(const T& config) {
		this->impl = std::make_unique<typename T::MotorType>(config);
	}

	BaseMotorImpl *operator->() {
		return this->impl.get();
	}

private:
	std::unique_ptr<BaseMotorImpl> impl;
}; // class Motor
} // namespace acro

#endif // ACRO_BASE_MOTOR_HPP
#endif