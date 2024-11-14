#pragma once

#include "Renderer/Camera.hpp"
#include "Renderer/Shader.hpp"

#include "BagelMath.hpp"


class Renderer
{
private:
    struct SceneData
    {
        glm::mat4 ViewProjectionMatrix = glm::mat4(1.0f);
        glm::mat4 ModelMatrix = glm::mat4(1.0f);
        std::shared_ptr<Shader> SceneShader;
    };
    static SceneData* m_sceneData;

public:
    static void Init(const std::vector<std::string>& filePaths);

    static void StartScene(const Camera& camera);
    static void EndScene();

    static const SceneData& GetSceneData() { return *m_sceneData; }
};