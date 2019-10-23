#include "UniformBuffer.h"
#include "Log.h"


UniformBuffer::UniformBuffer(const unsigned int& buffersize)
	:m_rendererID(0), m_slot(0)
{
	glGenBuffers(1, &m_rendererID);
	this->Bind();
	glBufferData(GL_UNIFORM_BUFFER, buffersize, NULL, GL_STATIC_DRAW);
	this->UnBind();
}

UniformBuffer::UniformBuffer(const unsigned int& buffersize, unsigned int slot)
	:m_rendererID(0),m_slot(slot)
{
	glGenBuffers(1, &m_rendererID);
	this->Bind();
	glBufferData(GL_UNIFORM_BUFFER, buffersize, NULL, GL_STATIC_DRAW);
	this->UnBind();
}

void UniformBuffer::Bind()
{
	glBindBuffer(GL_UNIFORM_BUFFER, m_rendererID);
}

void UniformBuffer::UnBind()
{
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

/**
* This methods can be used to push all the data from a void* to the uniform block.
* The data will start at 0 and will go on till specified size.
* for details - http://docs.gl/gl4/glBufferData
*/

void UniformBuffer::UpdateBufferData(const void* databuffer, const unsigned int& buffersize)
{
	this->Bind();
	glBufferData(GL_UNIFORM_BUFFER, buffersize, databuffer, GL_STATIC_DRAW);
	this->UnBind();
}

/*
*  This method can be used to change some of the data from a block.
*  Inputs: offset(what index the data should start in block),
*		   buffersize(size of datablock)
*           databuffer(void* to data)
*  http://docs.gl/gl4/glBufferSubData
*/
void UniformBuffer::UpdateBufferSubData(const unsigned int& offset, const unsigned int& buffersize, const void* databuffer)
{

	SB_ENGINE_INFO("{0}",reinterpret_cast<uintptr_t>(databuffer));
	this->Bind();
	glBufferSubData(GL_UNIFORM_BUFFER, offset, buffersize, databuffer);
	this->UnBind();
}

/*
* This methods is used to bind the base of uniform block to the specified slot or GPU binding.
* http://docs.gl/gl4/glBindBufferBase
*/

void UniformBuffer::BindBufferBase()
{
	glBindBufferBase(GL_UNIFORM_BUFFER, m_slot, m_rendererID);
}

/*
* This methods is used to bind the uniform block to the specified slot or GPU binding starting from the
* offset provided and extending to the specified size.
* http://docs.gl/gl4/glBindBufferRange
*/
void UniformBuffer::BindBufferRange(const unsigned int& offset, const unsigned int& size)
{
	glBindBufferRange(GL_UNIFORM_BUFFER, m_slot, m_rendererID, offset, size);
}
