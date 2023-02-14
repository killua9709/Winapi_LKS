#pragma once
#include <string>
#include <vector>
#include <map>

struct WeaponInfo
{
	static std::map<std::string, WeaponInfo> Infos;

public:
	int Att;
	std::string Image;
};
