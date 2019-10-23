#ifndef UNIFORMBUFFERBLOCK_H
#define UNIFORMBUFFERBLOCK_H
#include "framework.h"

class UniformBuffer
{
private:
	unsigned int m_rendererID;
	unsigned int m_slot;

public:
	UniformBuffer(const unsigned int& buffersize);
	UniformBuffer(const unsigned int& buffersize, unsigned int slot);

	void Bind();
	void UnBind();
	void UpdateBufferData(const void* databuffer, const unsigned int& buffersize);
	void UpdateBufferSubData(const unsigned int& offset, const unsigned int& buffersize, const void* databuffer);
	void BindBufferBase();
	void BindBufferRange(const unsigned int& offset, const unsigned int& size);

	inline const unsigned int GetUniformBufferSlot() const { return m_slot; }
};
#endif

