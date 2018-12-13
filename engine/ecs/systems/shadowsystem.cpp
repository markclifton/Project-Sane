#include "shadowsystem.h"

#include "glm/matrix.hpp"

#include "ecs/components/cameracomponent.h"
#include "ecs/components/shadercomponent.h"
#include "ecs/components/texturecomponent.h"
#include "ecs/components/vertexcomponent.h"
#include "ecs/ecsmanager.h"
#include "ecs/entities/shadowentity.h"

namespace ecs
{
ShadowSystem::ShadowSystem()
{
    components_.push_back(CameraComponent::Type);
    components_.push_back(ShaderComponent::Type);
    components_.push_back(TextureComponent::Type);
}

void ShadowSystem::update(std::vector<COMP_TYPE> /*componentsToUse*/, float /*delta*/, void** component)
{
    auto baseComponent = reinterpret_cast<BaseComponent*>(*component);
    auto entity = reinterpret_cast<ShadowEntity*>(baseComponent->entityHandle);

    auto cameraComponent = reinterpret_cast<CameraComponent*>(entity->GetComponentByTypeAndIndex(CameraComponent::Type, 0));

    glm::mat4 pS, vS;
    cameraComponent->camera->Update();
    cameraComponent->camera->GetMatricies(pS, vS);
    pS = glm::ortho<float>(-10, 10, -10, 10, 1, 100);

    auto textureComponent = reinterpret_cast<TextureComponent*>(entity->GetComponentByTypeAndIndex(TextureComponent::Type, 0));
    textureComponent->texture->setAsRenderTarget();

    auto shaderComponent = reinterpret_cast<ShaderComponent*>(entity->GetComponentByTypeAndIndex(ShaderComponent::Type, 0));
    shaderComponent->shader->bind();
    shaderComponent->shader->setUniform("projection", pS);
    shaderComponent->shader->setUniform("view", vS);

    ecs::ECSManager::get().updateSystems({VertexComponent::Type});
}


}
