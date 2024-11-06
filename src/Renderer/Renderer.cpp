#include "Renderer.hpp"

#include <memory>

#include "Renderer/Shader.hpp"

#include "Tools/Debug.hpp"


Renderer::SceneData* Renderer::m_sceneData = new SceneData;


void Renderer::Init(const std::vector<std::string>& filePaths)
{
    ASSERT(m_sceneData, "The Scene Data Was Not Initialized!");

    m_sceneData->SceneShader = Shader::CreateShader(filePaths);
    m_sceneData->SceneShader->Bind();
}

void Renderer::StartScene(const Camera& camera)
{
    ASSERT(m_sceneData->SceneShader, "The Shader Program Was Not Inirialized");

    m_sceneData->ViewProjectionMatrix = camera.GetViewAndProjectionMatrix();
}

void Renderer::EndScene()
{

}