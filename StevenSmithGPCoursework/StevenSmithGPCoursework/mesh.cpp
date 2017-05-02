#include "mesh.h"
#include "obj_loader.h"
#include <vector>

Mesh::Mesh(const std::string& fileName)
{
	//Uses functions from "obj_loader.h" to load a model
	IndexedModel model = OBJModel(fileName).ToIndexedModel();
	InitMesh(model);
}

Mesh::Mesh(Vert* verts, unsigned int numVerts, unsigned int* indices, unsigned int numIndices)
{
	//Creates a model
	IndexedModel model;

	//Adds the position, texture coordinates and normals to the model
	for (unsigned int i = 0; i < numVerts; i++)
	{
		model.positions.push_back(*verts[i].GetPosition());
		model.texCoords.push_back(*verts[i].GetTexCoord());
		model.normals.push_back(*verts[i].GetNormal());
	}

	//Adds the indices to the model
	for (unsigned int i = 0; i < numIndices; i++)
	{
		model.indices.push_back(indices[i]);
	}

	//Sends the model information to be initialised
	InitMesh(model);
}


Mesh::~Mesh()
{
	//Deletes the VAO as a vertex array
	glDeleteVertexArrays(1, &m_vertArrayObject);
}

void Mesh::InitMesh(const IndexedModel& model)
{
	//saves the amount of indices in a mesh for a model
	m_drawCount = model.indices.size();

	//Creates the space needed for the vertex array and binds the VAO as a vertex array
	glGenVertexArrays(1, &m_vertArrayObject);
	glBindVertexArray(m_vertArrayObject);

	//Allocates buffers for writing data to
	glGenBuffers(NUM_BUFFERS, m_vertArrayBuffers);
	//Any OpenGL function that will affect a buffer now affects the VAB
	glBindBuffer(GL_ARRAY_BUFFER, m_vertArrayBuffers[POSITION_VB]);
	//Takes data and writes it to the GPU
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);

	//Tells openGL how to access the data and where the attributes are within the buffer
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertArrayBuffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glGenBuffers(NUM_BUFFERS, m_vertArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertArrayBuffers[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(model.normals[0]), &model.normals[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertArrayBuffers[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);

	//Stops the VAO being affected by vertex array functions
	glBindVertexArray(0);
}

//Takes the mesh and draws it with the GPU
void Mesh::DrawMesh()
{
	glBindVertexArray(m_vertArrayObject);

	//Tells OpenGL how to draw the array
	glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}
