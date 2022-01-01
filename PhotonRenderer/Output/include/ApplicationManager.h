#pragma once
#include <GLFW\glfw3.h>
#include <iostream>
class ApplicationManager
{
public:
	void AppInit();
	static ApplicationManager* instance()
	{
		static ApplicationManager* INSTANCE;
		return INSTANCE;
	}
	
};

