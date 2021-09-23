#pragma once
#include "Components.h"
#include "Vector2D.h"

class TransformComponent : public Component
{
private:
	Vector2D position;
	Vector2D velocity;
	Vector2D accel;
	float angle;

public:
	int height = 32;
	int width = 32;
	int scaleW = 2;
	int scaleH = 2;

	TransformComponent(float x = 0.0f, float y = 0.0f, int h = 32, int w = 32, int scH = 2, int scW = 2):
	height(h), width(w), scaleW(scW), scaleH(scH)
	{
		setPos(x, y);
		angle = 0;
		velocity.x = velocity.y = 0;
		accel.x = accel.y = 0;
	}

	float getX() const{ return position.x; }
	float getY() const{ return position.y; }
	

	void update() override {
		position.x += velocity.x;
		position.y += velocity.y;
	}

	void setPos(float x, float y) {
		position.x = x;
		position.y = y;
	}

	Vector2D& getVel() {
		return velocity;
	}
	Vector2D& getAccel() {
		return accel;
	}

	float getAngle() const{
		return angle;
	}
	void setAngle(float a) {
		angle = a;
	}
};