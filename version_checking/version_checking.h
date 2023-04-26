#pragma once
class version_checking
{
public:
	static void validate();
	static void validate_game_dll(std::string filename);
};
