#pragma once

#include <frc/TimedRobot.h>
#include <memory>

namespace acro {

class TickerRobotApp {
public:
	virtual void tick_robot() = 0;

	virtual void start_auton() = 0;
	virtual void  tick_auton() = 0;
	virtual void  stop_auton() = 0;

	virtual void start_teleop() = 0;
	virtual void  tick_teleop() = 0;
	virtual void  stop_teleop() = 0;

	virtual void start_disabled() = 0;
	virtual void  tick_disabled() = 0;
	virtual void  stop_disabled() = 0;

	virtual ~TickerRobotApp() = 0;

	template<typename T>
	int run() {
		return frc::StartRobot<Harness<T>>();
	}
private:
	template<typename T>
	class Harness : public frc::TimedRobot {
	public:
		Harness();

		void RobotPeriodic();

		void AutonomousInit();
		void AutonomousPeriodic();

		void TeleopInit();
		void TeleopPeriodic();

		void DisabledInit();
		void DisabledPeriodic();

		~Harness();
	private:
		std::unique_ptr<TickerRobotApp> robot;
	};
}; // class TickerRobotApp



} // namespace acro
