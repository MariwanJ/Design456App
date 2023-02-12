#pragma once

#include<frtk.h>
#include<Fr_Core.h>
#include <Transform.h>
#include <Mesh.h>
#include <Node.h>
#include <Light.h>
#include <fr_primatives.h>

//Temporary code - just for debuggin
std::shared_ptr<Transform>bunny();
//End Temporary code

class Grid :public Node
{
public:
/**
 * class constructor.
 * 
 */
	Grid();
	
	void setGridParam(unsigned int sections = 50,unsigned int gridSize = 1,	glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3 scale = glm::vec3(0.0f, 0.0f, 0.0f));
	/**
	 * Class destructor.
	 * 
	 */
	~Grid();
	/**
	 * Sets the position of the grid.
	 * 
	 * \param pos Vertext that is the center of the grid
	 */
	void setCenterPosition(glm::vec3 pos);
	/**
	 * Sets Angle of rotation and the axis of rotation.
	 * 
	 * \param axis 3 floats - Axis of rotation 
	 * \param angle Angle of rotation in degrees
	 */
	void setAngle(float Angle);

	/**
	 * Set Grid rotation.
	 * 
	 * \param rotation 4 float : axis and an angle
	 */
	void setRotation(glm::vec4 rotation);
	/**
	 * Get rotation axis and angle in radians.
	 * 
	 * \return 
	 */
	glm::vec4 getRotation(void);
	/**
	 * Sets the grid visibility.
	 *
	 * \param status boolean variable. If ture: Grids shown, if false: Grid is not visible
	 */
	void setVisible(bool status);
	/**
	 * Sets grid size. This is the distance between each line in both axis
	 */
	void setGridSize( unsigned int sizeINmm); 
	/**
	 * Returns the grid size.
	 * 
	 * \return gird size defined previously 
	 */
	unsigned int getGridSize(void) const;

	/**
	 * Create the Grid verticies.
	 * 
	 * \return pointer to the created grid
	 */
	std::shared_ptr<Transform>CreateGrid();
private:

	int sections_; //No of lines in both directions
	int gridSize_; //Distance between each line in mm. This will be affected by the scale
	glm::vec3 scale_; //Scale the whole grid - Be careful this affects the distance value.
	glm::vec3 centerPos_;//Center of the grid
	glm::vec4 gridRotation_; //(Axis, angle) 4 float values
	glm::vec4 gridColor_;

};

