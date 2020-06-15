#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(const FrameBufferData& spec)
	: m_fbData(spec)
{
	Invalidate();
}

FrameBuffer::~FrameBuffer()
{
	glDeleteFramebuffers(1, &m_RendererID);
}

void FrameBuffer::Invalidate()
{
	glCreateFramebuffers(1, &m_RendererID);
	glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

	glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttachment);
	glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_fbData.Width, m_fbData.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);

	glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthAttachment);
	glBindTexture(GL_TEXTURE_2D, m_DepthAttachment);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_fbData.Width, m_fbData.Height);
	// glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_fbData.Width, m_fbData.Height, 0,
	// 	GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachment, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		SB_ENGINE_ERROR("Framebuffer is incomplete!");
	else
		SB_ENGINE_INFO("Framebuffer is Complete!");
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
}

void FrameBuffer::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

