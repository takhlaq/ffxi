#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "entity.h"
#include "engine/renderer/memory.h"
#include "engine/renderer/vulkan/renderer.h"

//i love windows
#undef near
#undef far

namespace lotus
{
    class Engine;
    class Input;

    class Camera : public Entity
    {
    public:
        explicit Camera(Engine*);
        ~Camera();
        void Init(const std::shared_ptr<Camera>& sp);
        glm::mat4& getViewMatrix() { return camera_data.view; }
        glm::mat4& getProjMatrix() { return camera_data.proj; }

        void setPos(glm::vec3);
        void setPerspective(float radians, float aspect, float near_clip, float far_clip);
        float getNearClip() { return near_clip; }
        float getFarClip() { return far_clip; }
        void move(float forward_offset, float right_offset);
        void look(float rot_x_offset, float rot_y_offset);
        float getRotX() const { return rot_x; }
        float getRotY() const { return rot_y; }

        glm::vec3 getRotationVector() { return camera_rot; }

        struct CameraData
        {
            glm::mat4 proj{};
            glm::mat4 view{};
            glm::mat4 proj_inverse{};
            glm::mat4 view_inverse{};
            glm::vec4 eye_pos;
        } camera_data;

        std::unique_ptr<Buffer> view_proj_ubo;
        uint8_t* view_proj_mapped{ nullptr };

        struct UBOFS
        {
            glm::vec4 cascade_splits;
            glm::mat4 cascade_view_proj[Renderer::shadowmap_cascades];
            glm::mat4 inverse_view;
        } cascade_data {};

        struct Frustum
        {
            glm::vec4 left;
            glm::vec4 right;
            glm::vec4 top;
            glm::vec4 bottom;
            glm::vec4 near;
            glm::vec4 far;
        } frustum {};

        std::unique_ptr<Buffer> cascade_data_ubo;
        uint8_t* cascade_data_mapped{ nullptr };

    protected:
        virtual void tick(time_point time, duration delta) override;
        virtual void render(Engine* engine, std::shared_ptr<Entity>& sp) override;

        float rot_x{ -glm::pi<float>() };
        float rot_y{ 0.f };
        float near_clip{ 0.f };
        float far_clip{ 0.f };
        glm::vec3 camera_rot{};

        float nh{};
        float nw{};
        float fh{};
        float fw{};

        bool update{ false };
    };
}
