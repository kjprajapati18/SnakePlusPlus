#pragma once
#include "SDL.h"


class Collision {
public:
	static bool AABB(const SDL_Rect& A, const SDL_Rect& B) {
		if (
			A.x + A.w >= B.x &&
			B.x + B.w >= A.x &&
			A.y + A.h >= B.y &&
			B.y + B.h >= A.y
			)
		{
			return true;
		}

		return false;
	}

	static bool A2B(const TransformComponent& A, const TransformComponent& B) {

		//Get the A's corner points relative to B.
		//First rotate A corners relative to A.
		//Add A's x,y position to get absolute position of corners
		//Subtract B's pos to get A's corners relative to B's corner
		//Unrotate by B's angle to get A's corners relative to B's space.

		Vector2D corners[4];
		float aX = A.getX();
		float aY = A.getY();
		float bX = B.getX();
		float bY = B.getY();
		float aAng = A.getAngle();
		float bAng = B.getAngle();

		float midAX = A.width * A.scaleW / 2;
		float midAY = A.height * A.scaleH / 2;
		float midBX = B.width * B.scaleW / 2;
		float midBY = B.height * B.scaleH / 2;

		corners[0].x = -midAX;
		corners[0].y = midAY;
		corners[1].x = -midAX;
		corners[1].y = -midAY;
		corners[2].x = midAX;
		corners[2].y = midAY;
		corners[3].x = midAX;
		corners[3].y = -midAY;

		float AxToBx = midAX + aX - bX - midBX;
		float AyToBy = midAY + aY - bY - midBY;
		//Rotate all of the corners in reference to B. Check if inside
		for (int i = 0; i < 4; i++) {
			rotate(corners[i], -1 * aAng);
			corners[i].x += AxToBx;
			corners[i].y += AyToBy;
			rotate(corners[i], bAng);

			if (corners[i].x > -midBX &&
				corners[i].x < midBX &&
				corners[i].y > -midBY &&
				corners[i].y < midBY)
			{
				return true;
			}
		}
		return false;
	}

	//Rotates Counter Clockwise
	static void rotate(Vector2D& vec, float angle) {
		float tempX = vec.x;
		float tempY = vec.y;

		vec.x = tempX * cos(angle) - tempY * sin(angle);
		vec.y = tempX * sin(angle) + tempY * cos(angle);
		return;
	}
};