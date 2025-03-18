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
