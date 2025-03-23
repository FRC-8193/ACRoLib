#pragma once
#include <typeindex>
#include <cstdint>

namespace acro {
	class Motor;
	class MotorFeature;
}

class acro::MotorFeature {
public:
	using ID = uint64_t;

private:
	ID current_uuid = 0;

protected:
	template<typename T>
	ID get_uuid() {
		static const int uuid = current_uuid++;
		return uuid;
	}
};

class acro::Motor {
public:
	Motor() = delete;

	const MotorFeature& get_feature(MotorFeature::ID id) const;

	virtual ~Motor() = 0;
};
