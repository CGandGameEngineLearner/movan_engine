#pragma once
#include <chrono>
#include <string>
#include <unordered_set>


export module MovanEngine;


namespace Movan
{
    enum class EOperationalMode
    {
        None,
        Edit,
        Run
    };
    extern EOperationalMode g_operation_mode;
    extern std::unordered_set<std::string> g_editor_tick_component_types;

    export class MovanEngine
    {
        friend class MovanEditor;

    public:
        void startEngine(const std::string& config_file_path);
        void shutdownEngine();

        void initialize();
        void clear();

        bool isQuit() const { return _is_quit; }
        void run();
        bool tickOneFrame(float delta_time);

        int getFPS() const { return _fps; }

    protected:
        void logicalTick(float delta_time);
        bool rendererTick(float delta_time);

        void calculateFPS(float delta_time);

        /**
         * 每帧调用一次
         *
         * Each frame can only be called once
         */
        float calculateDeltaTime();


        bool _is_quit {false};

        std::chrono::steady_clock::time_point m_last_tick_time_point {std::chrono::steady_clock::now()};

        float _average_duration {0.0f};

        /**
         * 帧数累计\n
         * 使用long long 而不是 int的原因：
         * 如果每秒60帧 那么约9942.05小时后会溢出
         * 但是作为人工智能仿真训练环境时，
         * 可能会以高帧率、长时间运行，不用long long容易溢出\n
         * \n
         *  Frame count accumulation\n
         * Reason for using long long instead of int:
         * If the frame rate is 60 frames per second, it will overflow after approximately 9942.05 hours.
         * However, as an AI simulation training environment,
         * it may run at a high frame rate for extended periods, and using int can easily cause overflow.
         */
        long long   _frame_count {0};
        int   _fps{0};
    };
} // namespace Movan