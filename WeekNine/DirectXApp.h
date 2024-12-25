#pragma once
#include "DirectXFramework.h"

class DirectXApp : public DirectXFramework
{
public:
	void CreateSceneGraph();
	void UpdateSceneGraph();
private: /*extra code*/
	float _rotationAngle;
	float _yOffset;
	bool _isGoingUp;


};

