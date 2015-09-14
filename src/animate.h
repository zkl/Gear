#ifndef ANIMATE_H
#define ANIMATE_H

#include <map>
#include "object.h"
#include "animation.h"

class Animate : public Object
{
public:
	void run (const char * action);
	void stop(const char * action);

	void setAnimation(Animation * animation);

private:
	void setStufPosition(int x, int y);
	void turnLeft();
	void turnRight();
	void move();
	void jump();
	void idle();

	float _direction; // 弧度
	float _speed;     // 毫秒/像素
	Animation * _animation;
};

inline void Animate::setAnimation(Animation * animation)
{
	_animation = animation;
}

#endif
