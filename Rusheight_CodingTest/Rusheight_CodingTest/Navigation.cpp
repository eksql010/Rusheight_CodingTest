#include "Navigation.h"

CNavigation::CNavigation()
{
	if (!Load_StationData("Data/Station_Data.csv"))
	{
		cout << "파일 로드 실패" << endl;
	}

	m_AdjList.resize(m_Stations.size());

	Make_Graph();
}

void CNavigation::Initialize()
{
	// 현재는 초기화 함수가 불필요한 것 같아서 해당 로직 생성자에 넣고 앱에서 호출 안 함

	m_AdjList.resize(m_Stations.size());

	Make_Graph();
}

void CNavigation::Find_ShortestPath(const string& startStationName, const string& endStationName)
{
	vector<int>	minTime(m_Stations.size(), INF);
	priority_queue<pair<int, int>> visitQueue;
	vector<int> routeFrom(m_Stations.size(), -1);

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
		m_Path.push_back(m_Stations[temp.top()]);
		temp.pop();
	}

	// 총 소요 시간 저장
	m_TotalTime = minTime[leastTimeEndStationNum];
}

vector<int> CNavigation::Find_Station(const string& stationName)
{
	auto iter = m_Mapping.find(stationName);

	if (iter == m_Mapping.end())
	{
		return vector<int>();
	}

	return iter->second;
}

bool CNavigation::Load_StationData(const string& filePath)
{
	ifstream file(filePath);

	if (!file.is_open())
	{
		return false;
	}

	string str;
	getline(file, str);

	while (getline(file, str))
	{
		if (str.empty())
		{
			continue;
		}

		stringstream stream(str);
		string line, name, time, r, g, b;
		getline(stream, line, ',');
		getline(stream, name, ',');
		getline(stream, time, ',');
		getline(stream, r, ',');
		getline(stream, g, ',');
		getline(stream, b, ',');

		StationInfo info = {};
		info.name = name;
		info.line = stoi(line);
		info.r = stoi(r);
		info.g = stoi(g);
		info.b = stoi(b);
		m_Stations.push_back(info);

		if (!time.empty() && time != "0")
		{
			m_TransitTimes.push_back(stoi(time));
		}
	}

	file.close();

	return true;
}

void CNavigation::Make_Graph()
{
	// 역 이름 -> 숫자로 매핑
	for (int i = 0; i < m_Stations.size(); ++i)
	{
		const string& stationName = m_Stations[i].name;

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
	for (int i = 0; i < m_Stations.size() - 1; ++i)
	{
		if (m_Stations[i].line != m_Stations[i + 1].line)
		{
			continue;
		}

		int time = m_TransitTimes[timeIndex++];

		m_AdjList[i].push_back({ i + 1, time });
		m_AdjList[i + 1].push_back({ i, time });
	}
}
