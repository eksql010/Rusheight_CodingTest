#include "Navigation.h"

CNavigation::CNavigation()
{
	m_AdjList.resize(stations.size());

	Make_Graph();
}

void CNavigation::Initialize()
{
	// 현재는 초기화 함수가 불필요한 것 같아서 해당 로직 생성자에 넣고 앱에서 호출 안 함

	m_AdjList.resize(stations.size());

	Make_Graph();
}

void CNavigation::Find_ShortestPath(const string& startStationName, const string& endStationName)
{
	vector<int>	minTime(stations.size(), INF);
	priority_queue<pair<int, int>> visitQueue;
	vector<int> routeFrom(stations.size(), -1);

	// 출발역 모두 이동 시간 0 초기화, 우선순위큐에 삽입
	for (int startStationNum : m_Mapping[startStationName])
	{
		minTime[startStationNum] = 0;
		visitQueue.push({ 0, startStationNum });
	}

	// 최단 경로 탐색 (다익스트라)
	while (!visitQueue.empty())
	{
		int curTime = -visitQueue.top().first;
		int curStation = visitQueue.top().second;
		visitQueue.pop();

		for (int i = 0; i < m_AdjList[curStation].size(); ++i)
		{
			int nextStation = m_AdjList[curStation][i].first;
			int nextTime = curTime + m_AdjList[curStation][i].second;

			if (nextTime < minTime[nextStation])
			{
				minTime[nextStation] = nextTime;
				visitQueue.push({ -nextTime, nextStation });
				routeFrom[nextStation] = curStation;
			}
		}
	}

	// 최단 경로 도착역 갱신
	int leastTimeEndStationNum = m_Mapping[endStationName][0];
	for (int endStationNum : m_Mapping[endStationName])
	{
		if (minTime[endStationNum] < minTime[leastTimeEndStationNum])
		{
			leastTimeEndStationNum = endStationNum;
		}
	}

	// 이동 경로 역추적
	stack<int> temp;
	temp.push(leastTimeEndStationNum);
	for (int i = leastTimeEndStationNum; routeFrom[i] != -1; i = routeFrom[i])
	{
		temp.push(routeFrom[i]);
	}

	// 이동 경로 정방향, 노선 정보로 저장
	while (!temp.empty())
	{
		m_Path.push_back(stations[temp.top()]);
		temp.pop();
	}

	// 총 소요 시간 저장
	m_TotalTime = minTime[leastTimeEndStationNum];
}

vector<int> CNavigation::Find_Station(const string& stationName)
{
	auto iter = m_Mapping.find(stationName);

	if (iter == m_Mapping.end())
		return vector<int>();

	return iter->second;
}

void CNavigation::Make_Graph()
{
	// 역 이름 -> 숫자로 매핑
	for (int i = 0; i < stations.size(); ++i)
	{
		const string& stationName = stations[i].name;

		// 환승역이면 환승역끼리 환승시간으로 연결
		if (m_Mapping.find(stationName) != m_Mapping.end())
		{
			for (int transferNum : m_Mapping[stationName])
			{
				m_AdjList[i].push_back({ transferNum, TRANSFER_TIME });
				m_AdjList[transferNum].push_back({ i, TRANSFER_TIME });
			}
		}

		m_Mapping[stationName].push_back(i);
	}

	// 노선 연결
	int timeIndex = 0;
	for (int i = 0; i < stations.size() - 1; ++i)
	{
		if (stations[i].line != stations[i + 1].line)
			continue;

		int time = transitTimes[timeIndex++];

		m_AdjList[i].push_back({ i + 1, time });
		m_AdjList[i + 1].push_back({ i, time });
	}
}
