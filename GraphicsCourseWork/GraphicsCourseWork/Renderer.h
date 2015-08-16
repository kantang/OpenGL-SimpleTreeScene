#pragma once
#include "stdafx.h"
#include "OGLRenderer.h"
#include "Camera.h"
#include "TextMesh.h"
#include "tree.h"
#include "HeightMap.h"
#include "OBJMesh.h"
#include <thread>

#define NUMBER_OF_TREES 6
#define NUMBER_OF_WEATHER_NODES 50
#define SHADOWSIZE 2048 * 8
#define POST_PASSES 10
#define LIGHTNUM 8


class Renderer :
	public OGLRenderer
{
public:
	Renderer(Window &parent);
	virtual ~Renderer(void);

	void toggleFPS() { showFPS = !showFPS; };

	virtual void RenderScene();
	virtual void UpdateScene(float msec);

	/*
	Draws the passed in line of text, at the passed in position. Can have an optional font size, and
	whether to draw it in orthographic or perspective mode.
	*/
	void DrawText(const std::string &text, const Vector3 &position, const float size = 10.0f, const bool perspective = false);

	//set the current fps for the scene renderer
	void setCurrentFPS(const int& val){ currentFPS = val; };

	//toggle show help
	void toggleShowHelp(){ showHelp = true; };

	//toggle weather, change from rain to snow to no weather at all.
	void toggleWeather();

	//reset the scene
	void reset();

protected:
	//generate all the shaders needed for the class
	bool GenerateAllShaders();

	//use to generate shadow buffer for the  
	bool GenerateShadowBuffer();
	//use to generate buffer for blurring post processing
	bool GenerateBlurBuffer();

	//use to generate all the trees on the terrain and particles on the flowers
	bool GenerateTreesAndParticles();

	//generate all the point lights for the defered rendering
	bool GeneratePointLights();

	//generate all the FBO for the defered rendering
	bool GenerateDeferedFBO();

	//method used to draw the water
	void DrawWater();
	//method used to draw the skybox
	void DrawSkybox();
	//method used to draw the shadow scene
	void DrawShadowScene();
	//method used to draw the combined scene
	//this combines shadow scene and normal scene
	//into a normal scene with shadow effect
	void DrawCombinedScene();
	//Draw a scene node and every children node
	void DrawNode(SceneNode *n);
	//the root node of the terrain, and the trees

	SceneNode* root;
	//stores all the trees inside
	Tree *trees;
	//stores all the attribute needed for creating a tree
	tree_attribute attr[NUMBER_OF_TREES];
	//the quad for water
	Mesh* quad;
	//the quad for the blur post processing
	Mesh *blurQuad;
	//the quad for the defered rendering
	Mesh *deferedQuad;
	//the mesh for the point light
	OBJMesh* sphere;

	//something which is important to particle emitter?
	void SetShaderParticleSize(float f);

	//everything related to snow effect
	GLuint snowTex;
	void CreateSnow();

	//everything related to rain effect
	GLuint rainTex;
	void CreateRain();

	//present the scene after post process
	void PresentScene();
	//modify the scene with blur effect
	//the scene is stored in a buffer object
	void DrawPostProcess();

	//current fps of the scene
	int currentFPS;
	//basic font for the text on the screen
	Font* basicFont;
	//show the fps or not
	bool showFPS;

	//the frame buffer object to store the scene before post processing
	GLuint bufferFBO;
	//the frame buffer object to store the processing procedures for it
	GLuint processFBO;
	//the texture buffer used for the blurring post processing
	GLuint bufferColourTex[2];
	//the depth buffer texture.
	GLuint bufferDepthTex;
	//the shadow buffer texture.
	GLuint shadowTex;
	//the shadow frame object.
	GLuint shadowFBO;

	//the frame buffer object and textures for the defered rendering
	GLuint deferedBufferFBO;
	GLuint deferedBufferColourTex;
	GLuint bufferNormalTex;
	GLuint deferedBufferDepthTex;

	GLuint pointLightFBO;
	GLuint lightEmissiveTex;
	GLuint lightSpecularTex;

	//all this, seen GenerateAllShaders();
	Shader* shadowShader;
	Shader* blurShader;
	Shader* reflectShader;
	Shader* skyboxShader;
	Shader* normalShader;
	Shader* particleShader;
	Shader* snowShader;
	Shader* textureShader;
	//the shader used for bumpmap and such
	Shader* sceneShader;
	//the shader to draw point light
	Shader* pointlightShader;
	//the shader to draw combined scene
	Shader* combineShader;

	//store the height map
	HeightMap* heightMap;

	//the camera been using
	Camera* camera;
	//the light been using
	Light* light;
	//the lights for defered rendering
	Light *pointLights;
	//the angle of the light when moving
	float angle;

	//the texture int for the particle
	GLuint particleTexture;
	//the texture int for the cube map
	GLuint cubeMap;
	//the rotate degree for the water.
	float waterRotate;
	//the rotation for the light
	float rotation;

	//the root scene node for the particle
	SceneNode* particleRoot;
	//the scene node array for the flower particles.
	SceneNode* flowerParticles;
	//number of flower particles.
	int numberOfFlowerPartricles;

	//all the snow partile node, the first element of the array is the root
	SceneNode *snowParticleNode;
	//all the rain partile node, the first element of the array is the root
	SceneNode *rainParticleNode;

	//get the string for the memory used for the trees
	string getMemoryUsedForTrees();

	//if blurring is up
	bool togglePostProcessOn;
	//if help is shown
	bool showHelp;
	//if particles are intialized
	bool particleInitialized;
	//if snowing
	bool snow;
	//if raining
	bool rain;
	//if showingDeferedRendering
	bool toggleDeferedRenderingOn;

	//Draw the point lights
	void DrawPointLights();
	//combine the buffers together
	void CombineBuffers();
	//generate the screen used for defered rendering
	void GenerateScreenTexture(GLuint &into, bool depth = false);
	
};

