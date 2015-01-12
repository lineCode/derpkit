#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <derpkit/render/texture.hpp>

#include "impl.hpp"

namespace derpkit {
namespace render {

Texture::Texture() : m_unit(-1) {
	m_impl = impl::empty_texture();
}

Texture::Texture(const std::string& path) : m_unit(-1) {
	m_impl = impl::load_texture(path);
}

Texture::~Texture() {
	impl::free_texture(m_impl);
}

void Texture::upload(unsigned char* pixels, ivec2 size, TextureFormat format, int unpack_alignment){
	impl::texture_upload(m_impl, pixels, size, format, unpack_alignment);
}


void Texture::bind(int unit) {
	impl::bind_texture(m_impl, unit);
	m_unit = unit;
}
void Texture::unbind() {
	if(m_unit < 0) return;
	impl::unbind_texture(m_unit);
}

}
}
