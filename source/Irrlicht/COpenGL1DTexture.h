#ifndef __C_OPEN_GL_1D_TEXTURE_H_INCLUDED__
#define __C_OPEN_GL_1D_TEXTURE_H_INCLUDED__

#include "IrrCompileConfig.h"
#include "COpenGLTexture.h"

#ifdef _IRR_COMPILE_WITH_OPENGL_

namespace irr
{
namespace video
{

//! OpenGL 1D texture.
class COpenGL1DTexture : public COpenGLFilterableTexture
{
public:
	//! constructor
	COpenGL1DTexture(GLenum internalFormat, const uint32_t* size, uint32_t mipmapLevels, const io::path& name="");

	//! Returns size of the texture.
	virtual E_DIMENSION_COUNT getDimensionality() const {return EDC_ONE;}

    virtual E_TEXTURE_TYPE getTextureType() const {return ETT_1D;}

	//! returns the opengl texture type
	virtual GLenum getOpenGLTextureType() const {return GL_TEXTURE_1D;}


    virtual bool updateSubRegion(const asset::E_FORMAT &inDataColorFormat, const void* data, const uint32_t* minimum, const uint32_t* maximum, int32_t mipmap=0, const uint32_t& unpackRowByteAlignment=0);
    virtual bool resize(const uint32_t* size, const uint32_t& mipLevels=0);
};


} // end namespace video
} // end namespace irr

#endif
#endif // _IRR_COMPILE_WITH_OPENGL_



