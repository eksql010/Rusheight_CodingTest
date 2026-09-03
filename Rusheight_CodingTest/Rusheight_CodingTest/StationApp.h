#pragma once

#include "Navigation.h"
#include "StationConsole.h"

class CStationApp
{
public:
	void				Execute();

private:
	void				Input_Stations(string& startStation, string& endStation);

private:
	CNavigation			m_Navigation;
	CStationConsole		m_Console;
};

