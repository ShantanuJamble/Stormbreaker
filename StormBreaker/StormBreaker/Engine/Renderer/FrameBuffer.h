#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H
#include "Log.h"
#include "framework.h"

struct FrameBufferData
{
	uint32_t Width, Height;
	// FramebufferFormat Format = 
	uint32_t Samples = 1;

	bool SwapChainTarget = false;
};

class FrameBuffer
{
private:
	uint32_t m_RendererID;
	uint32_t m_ColorAttachment, m_DepthAttachment;
	FrameBufferData m_fbData;

public:
	FrameBuffer(const FrameBufferData& fbData);
	~FrameBuffer();

	void Invalidate();

	void Bind() ;
	void Unbind() ;

	uint32_t GetColorAttachmentRendererID() const  { return m_ColorAttachment; }

	const FrameBufferData& GetSpecification() const  { return m_fbData; }
};


#endif FRAME_BUFFER_H