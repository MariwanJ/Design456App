
#include <../../src/fr_texture2d.h>
#include <../../vendor/stb_image/src/stb_image.h>

/** Default constructor */
Fr_Texture2D::Fr_Texture2D() {
	m_width = 0;
	m_height = 0;
	m_BPP = 0;
	m_LocalBuffer = NULL;
	m_RendererID = -1;
	active_ = false;
}
bool Fr_Texture2D::setup2DTexture(std::string& path, int width, int height, int bpp, int compno) {
	m_FilePath = path;
	m_width = width; 
	m_height = height;
	m_BPP = bpp;
	numComponents = compno;
	stbi_set_flip_vertically_on_load(1);
	m_LocalBuffer = stbi_load(path.c_str(), &m_width, &m_height, & m_BPP, numComponents);
	if (m_LocalBuffer == NULL){
		FRTK_CORE_ERROR("Cannot load Texture", path);
		active_ = false;
		return active_; //nothing to do here
	}
	glCheckFunc(glGenTextures(1, &m_RendererID));
	glCheckFunc(glBindTexture(GL_TEXTURE_2D, m_RendererID));
	glCheckFunc(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	glCheckFunc(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	glCheckFunc(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP));
	glCheckFunc(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP));
	glCheckFunc(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
	glCheckFunc(glBindTexture(GL_TEXTURE_2D, 0));
	
	if (m_LocalBuffer)
		free(m_LocalBuffer);
	active_ = true;
	return true;
}
Fr_Texture2D::~Fr_Texture2D()
{
	glDeleteTextures(1, &m_RendererID);
}

void Fr_Texture2D::Bind(unsigned int slot)
{
	active_ = true;
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

void Fr_Texture2D::Unbind()
{
	active_ = false;
	glBindTexture(GL_TEXTURE_2D, 0);

}
