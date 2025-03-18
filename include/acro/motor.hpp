#ifndef ACRO_BASE_MOTOR_HPP
#define ACRO_BASE_MOTOR_HPP

#include <memory>

namespace acro {

/**
* @brief A base motor/motor controller interface.
* Classes implementing this interface should define a struct Config, a Constructor(const Config&), and implement all pure virtual functions.
*/
class BaseMotorImpl {
public:
	struct Config {};

	inline BaseMotorImpl() {}

	/**
	* @brief Check if the motor was created properly and has no fatal errors.
	*/
	virtual bool is_ok() = 0;
}; // class BaseMotorImpl

/**
* @brief A software interface with a motor or motor controller.
*/
class Motor {
public:
	/**
	* @brief Create a new motor.
	* @tparam Hardware The motor controller implementation type. (See @ref acro::BaseMotorImpl)
	* @param config The configuration, corresponding to the specified hardware.
	*/
	template<typename Hardware>
	Motor(const typename Hardware::Config& config) {
		this->impl = std::make_unique<Hardware>(config);
	}

private:
	std::unique_ptr<BaseMotorImpl> impl;
}; // class Motor
} // namespace acro

#endif // ACRO_BASE_MOTOR_HPP
