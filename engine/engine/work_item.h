#pragma once
#include <functional>
#include <engine/renderer/vulkan/vulkan_inc.h>

namespace lotus
{
    class WorkerThread;
    class WorkItem
    {
    public:
        WorkItem(){}
        WorkItem(const WorkItem&) = delete;
        WorkItem(WorkItem&&) = default;
        WorkItem& operator=(const WorkItem&) = delete;
        WorkItem& operator=(WorkItem&&) = default;
        virtual void Process(WorkerThread*) = 0;
        virtual ~WorkItem() = default;

        float priority = 0;
        bool operator>(const WorkItem& o) const { return priority > o.priority; }

        struct GraphicsResources
        {
            vk::CommandBuffer primary;
            vk::CommandBuffer secondary;
            vk::CommandBuffer shadow;
            vk::CommandBuffer particle;
        } graphics {};

        struct ComputeResources
        {
            vk::CommandBuffer primary;
        } compute {};
    };

    class LambdaWorkItem : public WorkItem
    {
    public:
        LambdaWorkItem(std::function<void(WorkerThread*)> _function) : WorkItem(), function(std::move(_function)){}
        virtual void Process(WorkerThread* thread) override { function(thread); }
    private:
        std::function<void(WorkerThread*)> function;
    };

}
