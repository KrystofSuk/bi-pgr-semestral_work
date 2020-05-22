#pragma once

#include "Engine/Core/component.h"
#include "Engine/Core/spline.h"

struct Animator : public Component {

	bool animating = true;
	float internalTime = 0;
	float speed = 1.0f;
	std::string param;
	Spline * track;

	Animator(Spline* track, const std::string & name);

	void Update();

	void OnClick();

	std::string Print() const;

	friend std::ostream& operator<<(std::ostream& out, const Animator& component);

	~Animator();
};