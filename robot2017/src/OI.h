#ifndef OI_H
#define OI_H

#include "WPILib.h"

#include "Util/TigerTrigger/TigerLeftTrigger.h"
#include "Util/TigerTrigger/TigerRightTrigger.h"

class OI {
private:
	std::shared_ptr<Joystick> driverJoystick;
	std::shared_ptr<Joystick> operatorJoystick;
public:
	OI();

	std::shared_ptr<Joystick> GetDriverJoystick();
	std::shared_ptr<Joystick> GetOperatorJoystick();

	std::shared_ptr<JoystickButton> aButtonOperator;
	std::shared_ptr<JoystickButton> bButtonOperator;
	std::shared_ptr<JoystickButton> xButtonOperator;

	double GetLeftXAxisDriver();
	double GetLeftYAxisDriver();
	double GetRightXAxisDriver();
	double GetRightYAxisDriver();
	bool GetAButtonDriver();
	bool GetBButtonDriver();
	bool GetXButtonDriver();
	bool GetYButtonDriver();
	bool GetLeftBumperDriver();
	bool GetRightBumperDriver();
	bool GetBackButtonDriver();
	bool GetStartButtonDriver();
	bool GetLeftStickButtonDriver();
	bool GetRightStickButtonDriver();

	double GetLeftXAxisOperator();
	double GetLeftYAxisOperator();
	double GetRightXAxisOperator();
	double GetRightYAxisOperator();
	bool GetAButtonOperator();
	bool GetBButtonOperator();
	bool GetXButtonOperator();
	bool GetYButtonOperator();
	bool GetLeftBumperOperator();
	bool GetRightBumperOperator();
	bool GetBackButtonOperator();
	bool GetStartButtonOperator();
	bool GetLeftStickButtonOperator();
	bool GetRightStickButtonOperator();

	float DeadBandJoystick(float axis);
};

#endif
