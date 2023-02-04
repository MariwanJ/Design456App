#pragma once

#include<frtk.h>
#include<Fr_Core.h>
#include <Transform.h>
#include <Mesh.h>
#include <Node.h>
#include <Light.h>
std::shared_ptr<Transform>CreateGrid();
std::shared_ptr<Transform>bunny();

class Grid :public Node
{
public:

	Grid();
	~Grid();

	void setDimentionPoints(int x1, int y1, int x2, int y2, int angle);
	void setDimention(int x, int y, int width, int angle); //Width and length are equal

	virtual void Render(RenderInfo& info, const glm::mat4& modelview) override;

	void setGridSize(int sizeINmm);
};

