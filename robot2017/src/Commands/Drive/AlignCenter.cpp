#include "AlignCenter.h"

AlignCenter::AlignCenter(float inputAngle)
{
	Requires(Robot::drivebaseSubsystem.get());
	SetTimeout(1);
	distanceToCenter = 0;
	adjyaw = 0;
	isDone = false;
	speed = 0;
	speedX = 0;
	speedY = 0;
	//std::cout << "Align Constructor" << std::endl;
	gearAngle = inputAngle;
	isRotDone = false;
	finalAutoRot = 0;
}

void AlignCenter::Initialize()
{
	//std::cout << "Align Init" << std::endl;
	distanceToCenter = 0;
	adjyaw = 0;
	isDone = false;
	speed = 0;
	speedX = 0;
	speedY = 0;
	isRotDone = false;
	SetTimeout(1);
	//Robot::ledSubsystem->SetRedLED(1);
	//Robot::ledSubsystem->SetGreenLED(0);
	//Robot::ledSubsystem->SetBlueLED(0);
}

void AlignCenter::Execute()
{
	//std::cout << "Align Execute" << std::endl;
	RobotMap::tigerDrive->turnController->SetSetpoint(gearAngle);
	adjyaw = Robot::drivebaseSubsystem->GetAdjYaw();
	isRotDone = Robot::drivebaseSubsystem->GetIsRotDone();
	finalAutoRot = Robot::drivebaseSubsystem->CalculateRotValue(gearAngle, 1);
	distanceToCenter = (320 / 2) - Robot::visionTable->GetNumber("centerX", 0.0);
	SmartDashboard::PutNumber("distanceToCenter", distanceToCenter);


	if(fabs(Robot::oi->GetLeftXAxisDriver()) > .1 || fabs(Robot::oi->GetLeftYAxisDriver()) > .1 || fabs(Robot::oi->GetRightXAxisDriver()) > .1) {
		//std::cout << "Override!" << std::endl;
		this->Cancel();
		isDone = true;
	}


	//I'm ignoring the return value and and directly using x and y - needed to translate FOD from ROD
	speed = CalculateSpeedValue(distanceToCenter);
	//std::cout << "speedX: " << speedX << std::endl;


	if(speedX == 0 || abs(distanceToCenter) <= 2) {
		//Robot::ledSubsystem->SetRedLED(0);
		//Robot::ledSubsystem->SetGreenLED(0);
		//Robot::ledSubsystem->SetBlueLED(1);
		Robot::drivebaseSubsystem->MecanumDrive(0, 0, 0, 0);
		isDone = true;
		//std::cout << "DONE WITH ALIGNMENT!" << std::endl;
	}
	else {
		//std::cout << speedX << " " << speedY << " " << finalAutoRot  << " " << adjyaw << std::endl;
		Robot::drivebaseSubsystem->MecanumDrive(speedX, speedY, finalAutoRot, adjyaw);
		isDone = false;
	}

	//std::cout << "isDone: " <<  isDone << std::endl;
}

bool AlignCenter::IsFinished()
{
	return isDone;
}

void AlignCenter::End()
{
	//std::cout << "Align End" << std::endl;
}

void AlignCenter::Interrupted()
{
	//std::cout << "Align Interrupted" << std::endl;
}

float AlignCenter::CalculateSpeedValue(int distToCenter) {
	float returnedSpeed = 0;
	if(distToCenter > 2) {
		std::cout << "TOO FAR RIGHT" << std::endl;
		returnedSpeed = -.2;
		speedX = -.5;
		speedY = .86;
		isDone = false;
	}

	if(distToCenter < -2 ) {
		std::cout << "TOO FAR LEFT" << std::endl;
		returnedSpeed = .2;
		speedX = .5;
		speedY = -.86;
		isDone = false;
	}

	if(abs(distToCenter) <= 2) {
		std::cout << "MADE IT" << std::endl;
		returnedSpeed = 0;
		speedX = 0;
		speedY = 0;
		isDone = true;
	}

	if (gearAngle > 0) {
		speedX = speedX * 1;
		speedY = speedY * -1;
	}
	//std::cout << "speedX: " << speedX << " speedY: " << speedY << std::endl;


	return speed;
}
