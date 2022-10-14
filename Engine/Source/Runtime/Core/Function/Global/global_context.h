#pragma once

#include <memory>
#include <string>

namespace Movan
{
    class LogSystem;
    class InputSystem;
    class PhysicsSystem;
    class PhysicsManager;
    class FileSystem;
    class AssetManager;
    class ConfigManager;
    class WorldManager;
    class RenderSystem;
    class WindowSystem;
    class ParticleManager;

    struct EngineInitParams;

    /// Manage the lifetime and creation/destruction order of all global system
    class RuntimeGlobalContext
    {
    public:
        // create all global systems and initialize these systems
        void startSystems(const std::string& config_file_path);
        // destroy all global systems
        void shutdownSystems();

    public:
        std::shared_ptr<LogSystem>       logger_system_;
        std::shared_ptr<InputSystem>     input_system_;
        std::shared_ptr<FileSystem>      file_system_;
        std::shared_ptr<AssetManager>    asset_manager_;
        std::shared_ptr<ConfigManager>   config_manager_;
        std::shared_ptr<WorldManager>    world_manager_;
        std::shared_ptr<PhysicsSystem>   legacy_physics_system_;
        std::shared_ptr<PhysicsManager>  physics_manager_;
        std::shared_ptr<WindowSystem>    window_system_;
        std::shared_ptr<RenderSystem>    render_system_;
        std::shared_ptr<ParticleManager> particle_manager_;
    };

    extern RuntimeGlobalContext runtime_global_context_g;
    
}// namespace Movan