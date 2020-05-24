#include "..\..\..\..\Headers\Engine\Components\Custom\animator.h"

sukkryst::Animator::Animator(Spline *newTrack, const std::string & param) : Component("Animator")
{
	track = newTrack;
	this->param = param;
}

void sukkryst::Animator::Update()
{
	if (!animating)
		return;
	internalTime += 0.01f * speed;

	if (param == "position")
		transform->position = track->Evaluate(internalTime);
	if (param == "rotation")
		transform->rotation = track->Evaluate(internalTime);
}

void sukkryst::Animator::OnClick()
{
	animating = !animating;
}

sukkryst::Animator::~Animator()
{
}
