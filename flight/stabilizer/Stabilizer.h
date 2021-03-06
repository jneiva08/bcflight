/*
 * BCFlight
 * Copyright (C) 2016 Adrien Aubry (drich)
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/

#ifndef STABILIZER_H
#define STABILIZER_H

#include <Frame.h>
#include "PID.h"

class Main;

class Stabilizer
{
public:
	typedef enum {
		Rate = 0,
		Stabilize = 1,
		ReturnToHome = 2,
		Follow = 3,
	} Mode;

	Stabilizer( Main* main, Frame* frame );
	~Stabilizer();

	virtual void setRollP( float p );
	virtual void setRollI( float i );
	virtual void setRollD( float d );
	Vector3f getRollPID() const;
	virtual void setPitchP( float p );
	virtual void setPitchI( float i );
	virtual void setPitchD( float d );
	Vector3f getPitchPID() const;
	virtual void setYawP( float p );
	virtual void setYawI( float i );
	virtual void setYawD( float d );
	Vector3f getYawPID() const;
	virtual Vector3f lastPIDOutput() const;

	virtual void setOuterP( float p );
	virtual void setOuterI( float i );
	virtual void setOuterD( float d );
	Vector3f getOuterPID() const;
	virtual Vector3f lastOuterPIDOutput() const;

	virtual void setHorizonOffset( const Vector3f& v );
	virtual Vector3f horizonOffset() const;

	virtual void setMode( uint32_t mode );
	virtual uint32_t mode() const;
	virtual void setAltitudeHold( bool enabled );
	virtual bool altitudeHold() const;

	virtual bool armed() const;
	virtual float thrust() const;
	virtual const Vector3f& RPY() const;
	virtual void Arm();
	virtual void Disarm();
	virtual void setRoll( float value );
	virtual void setPitch( float value );
	virtual void setYaw( float value );
	virtual void setThrust( float value );

	virtual void CalibrateESCs();
	virtual void MotorTest(uint32_t id);
	virtual void Reset( const float& yaw );
	virtual void Update( IMU* imu, Controller* ctrl, float dt );

protected:
	Main* mMain;
	Frame* mFrame;
	Mode mMode;
	float mRateFactor;
	bool mAltitudeHold;

	PID<float> mRateRollPID;
	PID<float> mRatePitchPID;
	PID<float> mRateYawPID;
	PID<Vector3f> mHorizonPID;
	PID<float> mAltitudePID;
	float mAltitudeControl;

	bool mArmed;
	Vector4f mExpo;
	Vector3f mRPY;
	float mThrust;
	float mThrustAccum;

	int mLockState;
	Vector3f mHorizonMultiplier;
	Vector3f mHorizonOffset;
	Vector3f mHorizonMaxRate;
};

#endif // STABILIZER_H
