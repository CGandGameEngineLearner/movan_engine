#pragma once

#include "../../../../ThirdParty/spdlog/include/spdlog/spdlog.h"

#include <cstdint>
#include <stdexcept>

namespace Movan
{
	class LogSystem final
	{
	public:
		enum class LogLevel:uint8_t
		{
			debug,
			info,
			warn,
			error,
			fatal
		};

	public:
		LogSystem();
		~LogSystem();

        template<typename... TARGS>
        void log(LogLevel level, TARGS&&... args)
        {
            switch (level)
            {
            case LogLevel::debug:
                logger_->debug(std::forward<TARGS>(args)...);
                break;
            case LogLevel::info:
                logger_->info(std::forward<TARGS>(args)...);
                break;
            case LogLevel::warn:
                logger_->warn(std::forward<TARGS>(args)...);
                break;
            case LogLevel::error:
                logger_->error(std::forward<TARGS>(args)...);
                break;
            case LogLevel::fatal:
                logger_->critical(std::forward<TARGS>(args)...);
                fatalCallback(std::forward<TARGS>(args)...);
                break;
            default:
                break;
            }
        }

        template<typename... TARGS>
        void fatalCallback(TARGS&&... args)
        {
            const std::string format_str = fmt::format(std::forward<TARGS>(args)...);
            throw std::runtime_error(format_str);
        }

    private:
        std::shared_ptr<spdlog::logger> logger_;
	};
}// namespace Movan