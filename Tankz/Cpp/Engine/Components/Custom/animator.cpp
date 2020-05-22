#include "..\..\..\..\Headers\Engine\Components\Custom\animator.h"

Animator::Animator(Spline* newTrack, const std::string& name) : Component("Animator")
{
	track = newTrack;
	param = name;
}

void Animator::Update()
{
	if (!animating)
		return;
	internalTime += 0.01f * speed;

	if (param == "position")
		transform->position = track->Evaluate(internalTime);
	if (param == "rotation")
		transform->rotation = track->Evaluate(internalTime);
}

void Animator::OnClick()
{
	animating = !animating;
}

std::string Animator::Print() const
{
	return std::string();
}

Animator::~Animator()
{
}

std::ostream& operator<<(std::ostream& out, const Animator& component)
{
	return out << component.Print();
}
