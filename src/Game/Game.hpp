#include "ext/vector_float4.hpp"

#include "Renderer/_Renderer.hpp"
#include "App/Object.hpp"


class Game : public Object
{
private:
    Renderer renderer;
    glm::vec4 m_screenColor = {0.2f, 0.48f, 0.45f, 1.0f};


public:
    Game();
    virtual ~Game() = default;

    virtual void Start() override;
    virtual void Update(float deltaTime) override;
};