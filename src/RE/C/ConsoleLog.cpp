#include "RE/C/ConsoleLog.h"

namespace RE
{
	ConsoleLog* ConsoleLog::GetSingleton()
	{
		REL::Relocation<ConsoleLog**> singleton{ REL::ID(515064) };
		return *singleton;
	}

	bool ConsoleLog::IsConsoleMode()
	{
		struct TLSData
		{
			std::uint8_t unk000[0x600];  // 000
			bool         consoleMode;    // 600
		};

		REL::Relocation<std::uint32_t*> tlsIndex{ REL::ID(528600) };
		auto                            tlsData = reinterpret_cast<TLSData**>(__readgsqword(0x58));
		return tlsData[*tlsIndex]->consoleMode;
	}

	void ConsoleLog::Print(const char* a_fmt, ...)
	{
		std::va_list args;
		va_start(args, a_fmt);
		VPrint(a_fmt, args);
		va_end(args);
	}

	void ConsoleLog::VPrint(const char* a_fmt, std::va_list a_args)
	{
		using func_t = decltype(&ConsoleLog::Print);
		REL::Relocation<func_t> func{ REL::ID(50180) };
		func(this, a_fmt, a_args);
	}
}
