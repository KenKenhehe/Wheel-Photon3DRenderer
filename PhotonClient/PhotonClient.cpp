// PhotonClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "photonRenderer.h"
#include "RenderScene.h"

using namespace Photon;

int main(int argc, char* argv[])
{
	PhotonConfig config;
	config.title = "test";
	config.width = 1000;
	config.height = 1000;
	config.current_app_path = argv[0];
	std::cout << config.current_app_path << std::endl;
	RenderScene rs;

	PhotonApplication* app = new PhotonApplication(rs, config);
	delete app;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
