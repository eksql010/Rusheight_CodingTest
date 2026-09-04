#pragma once

#include "Defines.h"

class CStationConsole
{
public:
	CStationConsole();

public:
	string	Input_Station(const string& prompt);
	void	Output_Error(STATIONERROR error);
	void	Output_Result(const vector<StationInfo>& path, int totalTime);

private:
	string	Get_ColorCode(int r, int g, int b);
};