#include "pch.h"
#include "utils.h"

#include "groundhog_hooks.h"
#include "groundhog_offsets.h"
#include "halo3_hooks.h"
#include "halo3_offsets.h"
#include "halo4_hooks.h"
#include "halo4_offsets.h"
#include "haloreach_hooks.h"
#include "haloreach_offsets.h"
#include "main.h"

//Copy pasta from https://docs.microsoft.com/en-us/windows/win32/psapi/enumerating-all-modules-for-a-process
std::vector<std::string> get_current_modules()
{
	HMODULE hMods[1024];
	HANDLE hProcess = nullptr;
	DWORD cbNeeded;
	DWORD processID = GetCurrentProcessId();
	std::vector<std::string> modules;

	// Get a handle to the process.

	try {
		hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
			PROCESS_VM_READ,
			FALSE, processID);
	}
	catch (...) {
		std::cout << "ERROR: Could not open current process for some reason." << std::endl;
	}

	// Get a list of all the modules in this process.

	if (EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded))
	{
		for (unsigned int i = 0; i < (cbNeeded / sizeof(HMODULE)); i++)
		{
			CHAR szModName[260];

			// Get the module's filename

			if (GetModuleBaseNameA(hProcess, hMods[i], szModName,
				sizeof(szModName) / sizeof(TCHAR)))
			{
				//std::cout << szModName << std::endl;
				modules.emplace_back(szModName);
			}
		}
	}

	// Release the handle to the process.

	CloseHandle(hProcess);
	return modules;
}

void utils::check_for_game()
{

	std::cout << "Waiting for a game to be running." << std::endl;
	
	//TODO: This would be better rewritten with function hooks in mind.

	std::vector<std::string> runninggames;

	//Check if there is only one halo dll being used at the moment. then continue.
	while (runninggames.size() != 1)
	{
		// Get array of modules that mcc is currently using!
		std::vector<std::string> modules = get_current_modules();

		//Search array for halo game dlls. UGLY CODE INCOMING!

		for (std::string& module : modules) // access by reference to avoid copying
		{
			if (module == "haloreach.dll")
			{
				runninggames.emplace_back(module);
			}

			if (module == "halo1.dll")
			{
				runninggames.emplace_back(module);
			}

			if (module == "halo2.dll")
			{
				runninggames.emplace_back(module);
			}

			if (module == "groundhog.dll")
			{
				runninggames.emplace_back(module);
			}

			if (module == "halo3.dll")
			{
				runninggames.emplace_back(module);
			}

			if (module == "halo3odst.dll")
			{
				runninggames.emplace_back(module);
			}

			if (module == "halo4.dll")
			{
				runninggames.emplace_back(module);
			}
		}

		// Clear array if multiple games are found.
		if (runninggames.size() > 1)
		{
			runninggames.clear();
		}
	}

	if (runninggames[0] == "halo1.dll" || runninggames[0] == "halo2.dll")
	{
		std::wstring tmp;
		utils::string_to_wstring(tmp, runninggames[0]);

		MessageBox(GetConsoleWindow(), (tmp + L" is not supported at the moment. Sorry!").c_str(), L"Invalid Game!", MB_OK | MB_ICONERROR);

		main::kill_dll();
	}
	
	// Return string of running game.
	current_game = runninggames[0];
	utils::init_game(runninggames[0]);
}

//https://stackoverflow.com/a/8969776
int utils::string_to_wstring(std::wstring& ws, const std::string& s)
{
	std::wstring wsTmp(s.begin(), s.end());

	ws = wsTmp;

	return 0;
}

void utils::init_game(std::string game)
{
	//UGLY CODEEEEEEEEE

	if (game == "halo3.dll")
	{
		std::cout << "Initializing offsets for Halo 3!" << std::endl;
		halo3::offsets::init();
		halo3::hooks::init_hooks();
	}
	else if (game == "groundhog.dll")
	{
		std::cout << "Initializing offsets for H2AMP!" << std::endl;
		groundhog::offsets::init();
		groundhog::hooks::init_hooks();
	}
	else if (game == "halo4.dll")
	{
		std::cout << "Initializing offsets for Halo 4!" << std::endl;
		halo4::offsets::init();
		halo4::hooks::init_hooks();
	}
	else if (game == "haloreach.dll")
	{
		std::cout << "Initializing offsets for Halo Reach!" << std::endl;
		haloreach::offsets::init();
		haloreach::hooks::init_hooks();
	}
	else
	{
		std::wstring tmp;
		string_to_wstring(tmp, game);

		MessageBox(GetConsoleWindow(), (tmp + L" is invalid!").c_str(), L"utils::init_game", MB_OK | MB_ICONERROR);
	}
}