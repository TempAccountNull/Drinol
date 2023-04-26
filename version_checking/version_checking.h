#pragma once
class version_checking
{
public:
	static inline std::string COMPATIBLE_DRINOL_VERSION = "1.3073.0.0";
	static void validate();
	static void validate_game_dll(std::string filename);
};
