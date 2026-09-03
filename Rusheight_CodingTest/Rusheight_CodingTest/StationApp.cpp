#include "StationApp.h"

void CStationApp::Execute()
{
	string startStation, endStation;

	Input_Stations(startStation, endStation);
	m_Navigation.Find_ShortestPath(startStation, endStation);
	m_Console.Output_Result(m_Navigation.Get_Path(), m_Navigation.Get_TotalTime());
}

void CStationApp::Input_Stations(string& startStation, string& endStation)
{
	while (true)
	{
		startStation = m_Console.Input_Station("출발역 : ");

		if (m_Navigation.Find_Station(startStation).empty())
		{
			m_Console.Output_Error(STATIONERROR::NOTFOUND);
		}
		else
		{
			break;
		}
	}

	while (true)
	{
		endStation = m_Console.Input_Station("도착역 : ");

		if (m_Navigation.Find_Station(endStation).empty())
		{
			m_Console.Output_Error(STATIONERROR::NOTFOUND);
		}
		else if (startStation == endStation)
		{
			m_Console.Output_Error(STATIONERROR::SAME);
		}
		else
		{
			break;
		}
	}
}
