#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include "framework.h"
#include <vector>
#include "OpenGLErrorHandler.h"
class IndexBuffer
{
private:
	unsigned int m_renderBufferId;
	size_t m_Count;
	void SetupIndexBuffer(const unsigned int* indices);

public:

	IndexBuffer(const unsigned int*, size_t);
	IndexBuffer(const std::vector<unsigned int>& indices, size_t count);
	~IndexBuffer();
	
	inline unsigned int GetCount() const { return m_Count; }

	void Bind() const;
	void Unbind() const;
};

#endif // !1
