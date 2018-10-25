#include "game.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#include "shaders/shader.h"
#include "utils/mousehandler.h"
#include "utils/timer.h"

Game::Game()
    : m_contextManager()
    , m_windowManager( std::make_unique<managers::WindowManager>())
    , m_camera(new Camera3D())
{
    m_camera->SetViewport(0, 0, 640, 480);

    m_windowManager->toggleVsync(false);
    m_windowManager->registerHandler(m_camera.get());

    setup();
}

Game::~Game()
{
    m_contextManager.reset();
    m_shaderManager.reset();
    m_textureManager.reset();
    m_windowManager = nullptr;
}

void Game::run()
{
    //TODO: REFACTOR ME, not every shader needs this information
    Shader* s = m_shaderManager.getShader("BasicShader");
    s->bind();
    s->enableAttribArray("position");
    s->enableAttribArray("color");
    s->enableAttribArray("uv");
    glEnableVertexAttribArray(3);
    glEnableVertexAttribArray(4);
    glEnableVertexAttribArray(5);
    glEnableVertexAttribArray(6);

    glm::mat4 p, v;
    m_camera->Update();
    m_camera->GetMatricies(p, v);
    s->setUniform("projection", p);

    utils::Timer timer;
    int ticks = 0;
    while( !m_windowManager->shouldClose() )
    {
        if( ticks++ > 10)
        {
            auto time = timer.reset();
            std::cerr << 1.0/(time/ticks) <<  " latency: " << time/ticks * 1000 <<  "ms \n";
            ticks = 0;
        }

        m_camera->Update();
        m_camera->GetMatricies(p, v);
        s->setUniform("view", v);

        m_contextManager.runContext();
        m_windowManager->refresh();
    }
}

void Game::setup()
{
    m_shaderManager.loadShader("BasicShader", "resources/shaders/basic.vs", "resources/shaders/basic.fs");

    if( !m_contextManager.addContext("BasicContext", std::make_unique<Context>(m_shaderManager, m_textureManager)) )
        std::cerr << "Failed to add context\n";
    if( !m_contextManager.setContext("BasicContext") )
        std::cerr << "Failed to set context\n";
}
