// GraphicsCourseWork.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Window.h"
#include "Renderer.h"
#include <time.h>

#pragma comment(lib, "nclgl.lib")

int main() {
	srand((unsigned int)time(NULL));
	Window w("Kan Tang Course Work", 1920, 1080, true);
	if (!w.HasInitialised()) {
		return -1;
	}

	Renderer renderer(w);
	if (!renderer.HasInitialised()) {
		return -1;
	}

	double lastTime = w.GetTimer()->GetMS();
	int nbFrames = 0;
	renderer.setCurrentFPS(60);

	w.LockMouseToWindow(true);
	w.ShowOSPointer(false);
	bool polygonMode = false;
	while (w.UpdateWindow() && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)){
		double currentTime = w.GetTimer()->GetMS();
		nbFrames++;
		if (currentTime - lastTime > 1000)
		{
			renderer.setCurrentFPS(nbFrames);
			nbFrames = 0;
			lastTime = currentTime;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_M))
		{
			//enter the polygon mode
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_Q))
		{
			//toggle the weather, it's snow->rain->nothing->snow....
			renderer.toggleWeather();
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_H))
		{
			//toggle the more instuction menu
			renderer.toggleShowHelp();
		}
		//reset the whole scene
		if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_R))
			renderer.reset();

		
		float i = w.GetTimer()->GetTimedMS();
		//downwards is the speed control method for the scene
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_NUMPAD8))
			renderer.UpdateScene(i * 4);
		else if (Window::GetKeyboard()->KeyDown(KEYBOARD_NUMPAD6))
			renderer.UpdateScene(i * 8);
		else if (Window::GetKeyboard()->KeyDown(KEYBOARD_NUMPAD2))
			renderer.UpdateScene(i * -4);
		else if (Window::GetKeyboard()->KeyDown(KEYBOARD_NUMPAD4))
			renderer.UpdateScene(i * -8);
		else if (Window::GetKeyboard()->KeyDown(KEYBOARD_NUMPAD5))
			renderer.UpdateScene(0);
		else
			renderer.UpdateScene(i);
		renderer.RenderScene();
	}

	return 0;
}

