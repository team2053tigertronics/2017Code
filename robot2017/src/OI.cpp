#include "OI.h"

#include "SmartDashboard/SmartDashboard.h"
#include "Commands/Drive/ZeroYaw.h"
#include "Commands/Shooter/ShooterWheel.h"
#include "Commands/Shooter/LoaderWheel.h"
#include "Commands/Drive/AlignCenter.h"
#include "Commands/Climber/ClimbMotor.h"
#include "Commands/Gears/GearRetractGroup.h"
#include "Commands/Gears/GearRetrieveGroup.h"
#include "Commands/Gears/PushGearGroup.h"
#include "Commands/Gears/RetractGearGroup.h"
#include "Commands/Gears/ChuteSolenoid.h"
#include "Commands/Gears/FlapperSolenoid.h"
#include "Commands/Gears/PusherSolenoid.h"
#include "Commands/Leds/SetLeds.h"
#include "Commands/Shooter/ShooterEndGroup.h"
#include "Commands/Shooter/ShooterGroup.h"

OI::OI() {
	driverJoystick.reset(new Joystick(0));
	operatorJoystick.reset(new Joystick(1));

	aButtonOperator.reset(new JoystickButton(operatorJoystick.get(), 1));
	bButtonOperator.reset(new JoystickButton(operatorJoystick.get(), 2));
	xButtonOperator.reset(new JoystickButton(operatorJoystick.get(), 3));
	yButtonOperator.reset(new JoystickButton(operatorJoystick.get(), 4));
	//leftBumperOperator.reset(new JoystickButton(operatorJoystick.get(), 5));
	rightBumperOperator.reset(new JoystickButton(operatorJoystick.get(), 6));
	StartButtonOperator.reset(new JoystickButton(operatorJoystick.get(), 8));

	StartButtonDriver.reset(new JoystickButton(driverJoystick.get(), 8));
	StartButtonDriver->WhenPressed(new AlignCenter(-60));

	rightBumperOperator->WhenPressed(new ShooterGroup);
	rightBumperOperator->WhenReleased(new ShooterEndGroup);

	aButtonOperator->WhileHeld(new ShooterWheel(4000, 0));
	aButtonOperator->WhenReleased(new ShooterWheel(0, 0));

	xButtonOperator->WhenPressed(new LoaderWheel(4000, 0));
	xButtonOperator->WhenReleased(new LoaderWheel(0, 0));

	//xButtonOperator->WhenPressed(new ShooterGroup());
	//xButtonOperator->WhenReleased(new ShooterEndGroup());

	bButtonOperator->WhenPressed(new GearRetrieveGroup());
	bButtonOperator->WhenReleased(new GearRetractGroup());

	//yButtonOperator->WhenPressed(new PushGearGroup());
	//yButtonOperator->WhenReleased(new RetractGearGroup());
	yButtonOperator->WhenPressed(new PushGearGroup());
	yButtonOperator->WhenReleased(new RetractGearGroup());


	StartButtonOperator->WhenPressed(new ClimbMotor(1, 0));
	StartButtonOperator->WhenReleased(new ClimbMotor(0, 0));




	SmartDashboard::PutData("Zero Yaw", new ZeroYaw());

}

double OI::GetLeftXAxisDriver() {
	double joystickValue = OI::DeadBandJoystick(driverJoystick.get()->GetRawAxis(0));
	return joystickValue;
}

double OI::GetLeftYAxisDriver() {
	double joystickValue = OI::DeadBandJoystick(driverJoystick.get()->GetRawAxis(1));
	return joystickValue;
}

double OI::GetRightXAxisDriver() {
	double joystickValue = OI::DeadBandJoystick(driverJoystick.get()->GetRawAxis(4));
	return joystickValue;
}

double OI::GetRightYAxisDriver() {
	double joystickValue = OI::DeadBandJoystick(driverJoystick.get()->GetRawAxis(5));
	return joystickValue;
}

double OI::GetLeftXAxisOperator() {
	double joystickValue = OI::DeadBandJoystick(operatorJoystick.get()->GetRawAxis(0));
	return joystickValue;
}

double OI::GetLeftYAxisOperator() {
	double joystickValue = OI::DeadBandJoystick(operatorJoystick.get()->GetRawAxis(1));
	return joystickValue;
}

double OI::GetRightXAxisOperator() {
	double joystickValue = OI::DeadBandJoystick(operatorJoystick.get()->GetRawAxis(4));
	return joystickValue;
}

double OI::GetRightYAxisOperator() {
	double joystickValue = OI::DeadBandJoystick(operatorJoystick.get()->GetRawAxis(5));
	return joystickValue;
}

float OI::DeadBandJoystick(float axis) {
	if(axis > -0.20 && axis < 0.20)
	{
		axis = 0;
	}
	else
	{
		axis = axis * fabs(axis);
	}
	return axis;
}

bool OI::GetAButtonDriver() {
	return driverJoystick->GetRawButton(1);
}

bool OI::GetBButtonDriver() {
	return driverJoystick->GetRawButton(2);
}

bool OI::GetXButtonDriver() {
	return driverJoystick->GetRawButton(3);
}

bool OI::GetYButtonDriver() {
	return driverJoystick->GetRawButton(4);
}

bool OI::GetLeftBumperDriver() {
	return driverJoystick->GetRawButton(5);
}

bool OI::GetRightBumperDriver() {
	return driverJoystick->GetRawButton(6);
}

bool OI::GetBackButtonDriver() {
	return driverJoystick->GetRawButton(7);
}

bool OI::GetStartButtonDriver() {
	return driverJoystick->GetRawButton(8);
}

bool OI::GetLeftStickButtonDriver() {
	return driverJoystick->GetRawButton(9);
}

bool OI::GetRightStickButtonDriver() {
	return driverJoystick->GetRawButton(10);
}

bool OI::GetAButtonOperator() {
	return operatorJoystick->GetRawButton(1);
}

bool OI::GetBButtonOperator() {
	return operatorJoystick->GetRawButton(2);
}

bool OI::GetXButtonOperator() {
	return operatorJoystick->GetRawButton(3);
}

bool OI::GetYButtonOperator() {
	return operatorJoystick->GetRawButton(4);
}

bool OI::GetLeftBumperOperator() {
	return operatorJoystick->GetRawButton(5);
}

bool OI::GetRightBumperOperator() {
	return operatorJoystick->GetRawButton(6);
}

bool OI::GetBackButtonOperator() {
	return operatorJoystick->GetRawButton(7);
}

bool OI::GetStartButtonOperator() {
	return operatorJoystick->GetRawButton(8);
}

bool OI::GetLeftStickButtonOperator() {
	return operatorJoystick->GetRawButton(9);
}

bool OI::GetRightStickButtonOperator() {
	return operatorJoystick->GetRawButton(10);
}
