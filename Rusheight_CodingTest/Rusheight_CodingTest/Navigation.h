#pragma once

#include "Defines.h"

class CNavigation
{
public:
	CNavigation();

public:
	void					Initialize();
	void					Find_ShortestPath(const string& startStationName, const string& endStationName);
	vector<int>				Find_Station(const string& stationName);

	vector<StationInfo>		Get_Path()			{ return m_Path; }
	int						Get_TotalTime()		{ return m_TotalTime; }

private:
	bool					Load_StationData(const string& filePath);
	void					Make_Graph();

private:
	unordered_map<string, vector<int>>	m_Mapping;
	vector<vector<pair<int, int>>>		m_AdjList;
	vector<StationInfo>					m_Path;
	int									m_TotalTime;

	vector<StationInfo>					m_Stations;
	vector<int>							m_TransitTimes;
};

