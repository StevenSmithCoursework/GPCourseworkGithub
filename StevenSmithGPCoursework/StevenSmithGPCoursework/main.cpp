#include <iostream>
#include <GL\glew.h>
#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"
#include "camera.h"

#undef main
#define WIDTH 800
#define HEIGHT 600


int main()
{
	//Creates the display
	Display display(WIDTH, HEIGHT, "GPCoursework-Steven Smith");
	
	//Creates the meshes
	Mesh mesh("..//res//spaceship.obj");
	Mesh mesh2("..//res//planet.obj");
	Mesh mesh3("..//res//moon.obj");
	//Creates the shader programs
	Shader shader("..//res//basicShader");
	Shader shader2("..//res//basicShader");
	Shader shader3("..//res//basicShader");
	//Creates the textures
	Texture texture("..//res//spaceship.png");
	Texture texture2("..//res//planet.png");
	Texture texture3("..//res//moon.png");
	//Creates the camera
	Camera camera(glm::vec3(0, 0, -20), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f);
	//Creates the transforms for the objects
	Transform transform;
	Transform transform2;
	Transform transform3;

	//Used to manipulate the transforms 
	float counter = 0.0f;

	while (!display.IsClosed())
	{
		//Clears display
		display.Clear(1.0f, 1.0f, 1.0f, 1.0f);

		//Saves the counter in different ways to give different effects
		float sinCounter = sinf(counter);
		float cosCounter = cosf(counter);

		//Set transform of first object
		transform.GetPos().y = sinCounter;
		transform.SetScale(glm::vec3(0.5, 0.5, 0.5));
		transform.GetRot().y = 180.0;

		//Set transform of second object
		transform2.GetPos() = (glm::vec3(-25, -10, 150));
		transform2.SetScale(glm::vec3(0.5, 0.5, 0.5));
		transform2.GetRot().y = counter * 0.03;

		//Set transform of third object
		transform3.GetPos() = (glm::vec3(35, 0, 180));
		transform3.SetScale(glm::vec3(0.2, 0.2, 0.2));
		transform3.GetPos().y = (cosCounter + 30);

		//Render the first object
		shader.BindShader();
		shader.Update(transform, camera);
		texture.BindTexture(0);
		mesh.DrawMesh();

		//Render the second object
		shader2.BindShader();
		shader2.Update(transform2, camera);
		texture2.BindTexture(0);
		mesh2.DrawMesh();

		//Render the third object
		shader3.BindShader();
		shader3.Update(transform3, camera);
		texture3.BindTexture(0);
		mesh3.DrawMesh();

		//Swap the display buffers and increase the counter every frame
		display.SwapBuffers();
		counter += 0.01f;
	}

	//Used as main must return an int value
	return 0;
}