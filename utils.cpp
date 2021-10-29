#include "pch.h"
#include "utils.h"

//Copy pasta from https://docs.microsoft.com/en-us/windows/win32/psapi/enumerating-all-modules-for-a-process
std::vector<std::string> get_current_modules()
{
	HMODULE hMods[1024];
	HANDLE hProcess = nullptr;
	DWORD cbNeeded;
	unsigned int i;
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
		for (i = 0; i < (cbNeeded / sizeof(HMODULE)); i++)
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
	std::vector<std::string> runninggames;

	std::cout << "Checking for a running game inside MCC......" << std::endl;

	// Get array of modules that mcc is currently using!

	while (runninggames.size() != 1)
	{
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

		if (runninggames.size() > 1)
		{
			runninggames.clear();
		}
	}

	//Check if there is only one halo dll being used at the moment. then continue.
	std::cout << runninggames[0] << " is running!" << std::endl;
}