#pragma once

#include <atomic>
#include <chrono>
#include <filesystem>
#include <string>
#include <unordered_set>

namespace Movan
{
    extern bool                            g_is_editor_mode;
    extern std::unordered_set<std::string> g_editor_tick_component_types;

    class Engine
    {
        friend class Editor;

        static const float fps_alpha_s;

    public:
        void startEngine(const std::string& config_file_path);
        void shutdownEngine();

        void initialize();
        void clear();

        bool isQuit() const { return m_is_quit; }
        void run();
        bool tickOneFrame(float delta_time);

        int getFPS() const { return m_fps; }

    protected:
        void logicalTick(float delta_time);
        bool rendererTick();

        void calculateFPS(float delta_time);

        /**
         *  Each frame can only be called once
         */
        float calculateDeltaTime();

    protected:
        bool is_quit_{ false };

        std::chrono::steady_clock::time_point m_last_tick_time_point{ std::chrono::steady_clock::now() };

        float average_duration_{ 0.f };
        int   frame_count_{ 0 };
        int   fps_{ 0 };
    };
}