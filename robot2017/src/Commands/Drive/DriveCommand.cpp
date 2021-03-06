#include "DriveCommand.h"

DriveCommand::DriveCommand(): Command() {
	Requires(Robot::drivebaseSubsystem.get());

	xAxis = 0;
	yAxis = 0;
	rotAxis = 0;
	adjustedYaw = 0;
	setAngle = 0;
	setSpeed = 1;
	finalAutoRot = 0;
	isRotDone = false;
	buttonAPressed = false;
	buttonBPressed = false;
	buttonXPressed = false;
	buttonYPressed = false;
	leftBumperPressed = false;
	rightBumperPressed = false;
	leftStickPressed = false;
}

void DriveCommand::Initialize() {
	xAxis = 0;
	yAxis = 0;
	rotAxis = 0;
	adjustedYaw = 0;
	setSpeed = 1;
	finalAutoRot = 0;
	setAngle = 0;
	isRotDone = false;
	buttonAPressed = false;
	buttonBPressed = false;
	buttonXPressed = false;
	buttonYPressed = false;
	leftBumperPressed  = false;
	rightBumperPressed = false;
	leftStickPressed = false;
}

void DriveCommand::Execute() {
	//puts useful info on smart dashboard
	SmartDashboard::PutNumber("IMU Yaw", adjustedYaw);
	SmartDashboard::PutNumber("X Axis", xAxis);
	SmartDashboard::PutNumber("Y Axis", yAxis);
	SmartDashboard::PutNumber("Rot Axis", rotAxis);

	//Gets joystick values and deadbands them
	xAxis = Robot::oi->GetLeftXAxisDriver();
	yAxis = Robot::oi->GetLeftYAxisDriver();
	rotAxis = Robot::oi->GetRightXAxisDriver();

	//Gets if buttons are pressed (for rotating to angles)
	buttonAPressed = Robot::oi->GetAButtonDriver();
	buttonBPressed = Robot::oi->GetBButtonDriver();
	buttonXPressed = Robot::oi->GetXButtonDriver();
	buttonYPressed = Robot::oi->GetYButtonDriver();
	leftBumperPressed  = Robot::oi->GetLeftBumperDriver();
	rightBumperPressed = Robot::oi->GetRightBumperDriver();
	leftStickPressed = Robot::oi->GetLeftStickButtonDriver();

	//gets imu yaw and if the robot is done rotating
	adjustedYaw = Robot::drivebaseSubsystem->GetAdjYaw();
	isRotDone = Robot::drivebaseSubsystem->GetIsRotDone();

	//writes to setAngle to set which angle to go to depending on button
	DriveCommand::SetAngleWithButton();
	//sends values to rotate to angle if button is pressed or we are not done rotating
	DriveCommand::RotateCommand();
	//checks if we overrided the rotating with the rotAxis
	DriveCommand::CheckRotateOverride();
	//Calls mecanum drive function to actually run motors
	DriveCommand::CallToMecanumDrive();
}

bool DriveCommand::IsFinished() {
    return false;
}

void DriveCommand::End() {

}

void DriveCommand::Interrupted() {

}

void DriveCommand::SetAngleWithButton()
{
	if(buttonAPressed) {
		RobotMap::tigerDrive->turnController->SetSetpoint(180);
		setAngle = 180;
	}

	if(buttonBPressed) {
		RobotMap::tigerDrive->turnController->SetSetpoint(60);
		setAngle = 60;
	}

	if(buttonXPressed) {
		RobotMap::tigerDrive->turnController->SetSetpoint(-60);
		setAngle = -60;
	}

	if(buttonYPressed) {
		RobotMap::tigerDrive->turnController->SetSetpoint(0);
		setAngle = 0;
	}

	if(leftBumperPressed){
		RobotMap::tigerDrive->turnController->SetSetpoint(-30);
		setAngle = -30;
	}
	if(rightBumperPressed){
		RobotMap::tigerDrive->turnController->SetSetpoint(30);
		setAngle = 30;
	}
	if(leftStickPressed)
	{
		if(xAxis != 0 && yAxis != 0) {
			double rad = atan2(xAxis, yAxis);
			double degrees = rad * (180 / M_PI);
			setAngle = degrees;
		}
	}
	//potential buttons to add later for rope:
	//-30, 90, -150
}

void DriveCommand::RotateCommand()
{
	if(((leftStickPressed || rightBumperPressed || leftBumperPressed || buttonYPressed == true||buttonXPressed == true || buttonAPressed == true || buttonBPressed == true) && isRotDone == true) || (isRotDone == false))
	if(((rightBumperPressed || leftBumperPressed || buttonYPressed == true||buttonXPressed == true || buttonAPressed == true || buttonBPressed == true || leftStickPressed == true) && isRotDone == true) || (isRotDone == false))
	{
		finalAutoRot = Robot::drivebaseSubsystem->CalculateRotValue(setAngle, setSpeed);
	}
}

void DriveCommand::CheckRotateOverride() {
	if(Robot::drivebaseSubsystem->GetIsRotDoneOverride())
	{
		finalAutoRot = 0;
	}
}

void DriveCommand::CallToMecanumDrive() {
	if(rotAxis == 0)
	{
		Robot::drivebaseSubsystem->SetIsRotDoneOverride(false);
		Robot::drivebaseSubsystem->MecanumDrive(xAxis, yAxis, finalAutoRot, adjustedYaw);
	}
	else
	{
		Robot::drivebaseSubsystem->SetIsRotDoneOverride(true);
		Robot::drivebaseSubsystem->SetIsRotDone(true);
		Robot::drivebaseSubsystem->SetTimesThroughLoop(0);
		Robot::drivebaseSubsystem->MecanumDrive(xAxis, yAxis, rotAxis, adjustedYaw);
	}
}
