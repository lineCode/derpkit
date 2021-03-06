#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "window.hpp"
#include "render/impl.hpp"
#include "gen/shaderdefs.hpp"

#include <derpkit/render/rendertarget.hpp>
#include <derpkit/render/texture.hpp>
#include <derpkit/render/shader.hpp>
#include <derpkit/render/utils.hpp>
#include <derpkit/render/draw.hpp>

#include <SDL/SDL.h>
#include <GL/glew.h>

namespace derpkit {

using namespace render;

Window::Window(int width, int height) : m_size(width, height),  m_running(true) {
	// Initialize SDL

	if ( SDL_Init(SDL_INIT_VIDEO) != 0 ){
		printf("Failed to initalize SDL: %s\n", SDL_GetError());
		abort();
	}

	SDL_SetVideoMode(1280, 720, 0, SDL_OPENGL|SDL_DOUBLEBUF);
	SDL_WM_SetCaption("derpKit Test", NULL);

	// Load glew
	GLenum ret;
	if ( (ret=glewInit()) != GLEW_OK ){
		printf("Failed to initialize GLEW: %s\n", glewGetErrorString(ret));
		abort();
	}
	mat3 inv_mat =  mat3(1.f,  0.f, 0.f,
	                     0.f, -1.f, 0.f,
	                     0.f,  0.f, 1.f);

	m_screenortho = inv_mat * render::ortho(render::ivec2(width, height));

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT); // We have a inverted ortho
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	render::impl::initialize(); // TMP, move to library init
}

Window::~Window() {
	render::impl::cleanup(); // TMP, move to library cleanup
	SDL_Quit();
}

void Window::update() {
	SDL_Event event;
	while ( SDL_PollEvent(&event) ){
		switch ( event.type ){
		case SDL_QUIT:
			m_running = false;
			break;

		case SDL_KEYDOWN:
			if ( event.key.keysym.sym == SDLK_q && event.key.keysym.mod & KMOD_CTRL ){
				m_running = false;
			}
		}
	}

	SDL_GL_SwapBuffers();
}

void Window::blit(const render::RenderTarget* rt) {
	Shader::get(Shader_texture)->bind();
	Shader::set_projection(m_screenortho);
	render::impl::bind_vertex_array();
	Draw::rect(box(0, 0, m_size.x, m_size.y), *rt->texture());
}

}
