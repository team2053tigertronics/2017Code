#include "GearAlignLeft.h"
#include "../Drive/AlignCenter.h"
#include "DriveCommandAuto.h"
#include "../Autonomous/DoNothingAuto.h"
#include "DriveToBoilerShootCenter.h"
#include "../Gears/RetractGearGroup.h"
#include "../Gears/PushGearGroup.h"
#include "DriveToHopper.h"


GearAlignLeft::GearAlignLeft() {
	AddSequential(new PrintCommand("Starting Gear Align Left"));

	AddSequential(new DriveCommandAuto(0, -.5, 0, .65, 0));  //drive forward
	AddSequential(new DriveCommandAuto(.25, -.43, 0, .4, 60)); //drive towards airship
	AddSequential(new PrintCommand("GOT TO ALIGN IN GEARALIGN LEFT"));

	if(false) {
		std::cout << "GOT TO CAMERA IN GEAR ALIGN LEFT" << std::endl;
		AddSequential(new AlignCenter(60)); //align with gear
	}
	AddSequential(new PrintCommand("FINISHED ALIGNING IN GEARALIGN LEFT"));
	AddSequential(new DriveCommandAuto(.25, -.43, 0, 1.5, 60)); //drive onto airship

	AddSequential(new DoNothingAuto(.25)); //wait
	AddSequential(new PushGearGroup());
	AddSequential(new DoNothingAuto(.45)); //wait
	//AddSequential(new RetractGearGroup());
	//AddSequential(new DoNothingAuto(.5)); //wait


	AddSequential(new DriveCommandAuto(-.25, .43, 0, .6, 60)); //backs up
	AddSequential(new RetractGearGroup());

	AddSequential(new PrintCommand("Finished Gear Align Left"));

	if(Robot::doBoiler) {
		AddSequential(new PrintCommand("Calling Boiler From Left"));


		AddSequential(new PrintCommand("Finished Boiler From Left"));
	}

	//if(Robot::doHopper) {
		//AddSequential(new DriveToHopper("leftblue"));
	//}

}
