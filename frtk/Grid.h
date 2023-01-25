#pragma once

#include <Fr_Core.h>
#include <Node.h>

class Grid :public Node
{
public:

	Grid();
	~Grid();

	void setDimention(int x1, int y1, int x2, int y2, int angle);
	void setDimention(int x, int y, int width, int length, int angle);
	void setDimention(int x, int y, int width, int angle); //Width and length are equal

	virtual void Render(RenderInfo& info, const glm::mat4& modelview) override;

	void setGridSize(int sizeINmm);
	void setGridSize(int sizeINmm);
};

