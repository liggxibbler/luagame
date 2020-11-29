#pragma once

class RenderComponent;

#include <vector>

class RenderManager
{
public:
	void Render();

	void AddRenderComponent(RenderComponent* render);
	void RemoveRenderComponent(RenderComponent* render);

private:
	std::vector<RenderComponent*> m_objects;
};