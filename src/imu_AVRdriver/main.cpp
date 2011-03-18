#include "WProgram.h"
#include <stdio.h>
#include "avr_ros/ros.h"
#include "avr_ros/string.h"
#include "avr_ros/RazorImu.h"
#include "SF9DOF_AHRS.h"


imu_9drazor::RazorImu imu_msg;

namespace ros {
	void byte_put(uint8_t c) {
		Serial.write(c);
	}

	int byte_get(void) {
		return Serial.read();
	}
}

unsigned long pubTimer = 0;
void setup()
{
	setupIMU();
	//set up the imu message


	pubTimer = millis();
}

void loop()
{
	node.spin();
	stepIMU();

	if ( (millis() - pubTimer) >=20) {
		imu_msg.angular_velocity.x = Gyro_Vector[0];
		imu_msg.angular_velocity.y = Gyro_Vector[1];
		imu_msg.angular_velocity.z = Gyro_Vector[2];

		imu_msg.linear_acceleration.x = Accel_Vector[0]/256;
		imu_msg.linear_acceleration.y = Accel_Vector[1]/256;
		imu_msg.linear_acceleration.z = Accel_Vector[2]/256;

		imu_msg.roll = roll;
		imu_msg.pitch = pitch;
		imu_msg.yaw = yaw;


		node.publish(0,&imu_msg);
		pubTimer = millis();
	}

	delay(1);
}

