#include "Engine/Components/Custom/day_night.h"

float clip(float n, float lower, float upper) {
	return std::max(lower, std::min(n, upper));
}

DayNight::DayNight(Scene& scene) : Component("DayNight"), scene(scene)
{
}

void DayNight::Update()
{
	if (!use)
		return;

	transform->SetPos(glm::vec3(0.0, 0.0, 0.0));
	transform->Rotate(speed);
	transform->Move(transform->Front() * -500.0f);

	float tod = 1.0f;
	float rot = transform->rotation[0];
	tod = clip(transform->rotation[0] - 180.0 - (floor((int)rot / 360) * 360), 0.0, 180.0);
	tod -= 90;
	tod = abs(tod);
	float fog = 0.8f;
	float blend = 1.0f;
	float intensity = 1.0f;
	if (tod < 90 && tod > 60) {
		fog = 1.0 - abs((90.0 - tod) / 30.0 * 0.5 + 0.2);
		blend = 1.0 - abs((90.0 - tod) / 30.0 * 1.0);
	}
	else if (tod < 90 - 30) {
		fog = 0.3f;
		blend = 0.0f;
	}

	if (tod < 90) {
		intensity = 1.0 - abs((90.0 - tod) / 90.0 * 0.5);
	}
	scene.lightData.fogAmount = 1-fog;

	scene.lightData.dirAmount = intensity;
	scene.lightData.fogColor = glm::mix(scene.lightData.fogDefaultColor, nightFogColor, blend);
}

std::string DayNight::Print() const
{
	return "";
}

DayNight::~DayNight()
{

}

std::ostream& operator<<(std::ostream& out, const DayNight& component)
{
	return out;
}
