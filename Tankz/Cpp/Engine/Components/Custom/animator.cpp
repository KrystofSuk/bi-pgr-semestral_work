#include "..\..\..\..\Headers\Engine\Components\Custom\animator.h"

sukkryst::Animator::Animator(Spline *newTrack, const std::string &name) : Component("Animator")
{
	track = newTrack;
	param = name;
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

std::string sukkryst::Animator::Print() const
{
	return std::string();
}

sukkryst::Animator::~Animator()
{
}

std::ostream &operator<<(std::ostream &out, const sukkryst::Animator &component)
{
	return out << component.Print();
}
