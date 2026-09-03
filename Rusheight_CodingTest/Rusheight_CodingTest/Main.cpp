#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <queue>
#include <string>
#include <utility>
#include <stack>
#include <ctime>

using namespace std;

#define INF 999999999
#define TRANSFER_TIME 180

struct StationInfo
{
	string	name;
	int		line;
};

int main()
{
	vector<StationInfo> stations =
	{
		{ "용산", 1 }, { "남영", 1 }, { "서울역", 1 }, { "시청", 1 }, { "종각", 1 }, { "종로3가", 1 }, { "종로5가", 1 }, { "동대문", 1 }, { "동묘앞", 1 }, { "신설동", 1 }, { "제기동", 1 }, { "청량리", 1 },
		{ "당산", 2 }, { "합정", 2 }, { "홍대입구", 2 }, { "신촌", 2 }, { "이대", 2 }, { "아현", 2 }, { "충정로", 2 }, { "시청", 2 }, { "입지로입구", 2 }, { "을지로3가", 2 }, { "을지로4가", 2 }, { "동대문역사문화공원", 2 }, { "신당", 2 }, { "상왕십리", 2 }, { "왕십리", 2 }, { "한양대", 2 },
		{ "경복궁", 3 }, { "안국", 3 }, { "종로3가", 3 }, { "을지로3가", 3 }, { "충무로", 3 }, { "동대입구", 3 }, { "약수", 3 }, { "금호", 3 }, { "옥수", 3 },
		{ "이촌", 4 }, { "신용산", 4 }, { "삼각지", 4 }, { "숙대입구", 4 }, { "서울역", 4 }, { "회현", 4 }, { "명동", 4 }, { "충무로", 4 }, { "동대문역사문화공원", 4 }, { "동대문", 4 }, { "혜화", 4 },
		{ "마포", 5 }, { "공덕", 5 }, { "애오개", 5 }, { "충정로", 5 }, { "서대문", 5 }, { "광화문", 5 }, { "종로3가", 5 }, { "을지로4가", 5 }, { "동대문역사문화공원", 5 }, { "청구", 5 }, { "신금호", 5 }, { "행당", 5 }, { "왕십리", 5 }, { "마장", 5 },
		{ "망원", 6 }, { "합정", 6 }, { "상수", 6 }, { "광흥창", 6 }, { "대흥", 6 }, { "공덕", 6 }, { "효창공원앞", 6 }, { "삼각지", 6 }, { "녹사평", 6 }, { "이태원", 6 }, { "한강진", 6 }, { "버티고개", 6 }, { "약수", 6 }, { "청구", 6 },
	};

	vector<int> transitTimes =
	{
		110, 120, 120, 100, 90, 90, 90, 80, 80, 90, 100,
		170, 100, 110, 90, 90, 90, 110, 90, 90, 80, 100, 100, 100, 90, 100,
		100, 90, 70, 80, 100, 90, 90, 90,
		100, 90, 100, 100, 90, 90, 80, 100, 90, 90,
		100, 110, 100, 90, 120, 100, 90, 90, 100, 100, 100, 100, 100,
		100, 100, 100, 100, 110, 100, 130, 110, 90, 100, 110, 90, 90,
	};
	
	unordered_map<string, vector<int>> mapping;					// 역명 -> 숫자 매핑 컨테이너
	vector<vector<pair<int, int>>> adjList(stations.size());	// 인접 리스트
	vector<int> minTime(stations.size(), INF);					// 최소시간 갱신할 배열
	priority_queue<pair<int, int>> pq;							// 최소시간 정렬할 우선순위큐
	vector<int> routeFrom(stations.size(), -1);					// 최소시간 경로를 저장할 배열
	string startStation, endStation;							// 입력 받을 변수

	for (int i = 0; i < stations.size(); ++i)
	{
		const string& stationName = stations[i].name;

		if (mapping.find(stationName) != mapping.end())
		{
			for (int transferNum : mapping[stationName])
			{
				adjList[i].push_back({ transferNum, TRANSFER_TIME });
				adjList[transferNum].push_back({ i, TRANSFER_TIME });
			}
		}

		mapping[stationName].push_back(i);
	}

	int timeIndex = 0;
	for (int i = 0; i < stations.size() - 1; ++i)
	{
		if (stations[i].line != stations[i + 1].line)
			continue;

		int time = transitTimes[timeIndex++];

		adjList[i].push_back({ i + 1, time });
		adjList[i + 1].push_back({ i, time });
	}

	while (true)
	{
		cout << "출발역 : ";
		cin >> startStation;

		if (mapping.find(startStation) == mapping.end())
		{
			cout << "존재하지 않는 역입니다. 다시 입력해 주세요." << endl;
			continue;
		}

		cout << "도착역 : ";
		cin >> endStation;

		if (mapping.find(endStation) == mapping.end())
		{
			cout << "존재하지 않는 역입니다. 다시 입력해 주세요." << endl;
			continue;
		}

		if (startStation == endStation)
		{
			cout << "출발역과 도착역이 같습니다. 다시 입력해 주세요." << endl;
			continue;
		}
		else
		{
			// 시작역 전체 시간 0 초기화 후 우선순위큐에 삽입
			for (int startStationNum : mapping[startStation])
			{
				minTime[startStationNum] = 0;
				pq.push({ 0, startStationNum });
			}

			// 최단 경로 탐색 (다익스트라)
			while (!pq.empty())
			{
				int curTime = -pq.top().first;
				int curStation = pq.top().second;
				pq.pop();

				for (int i = 0; i < adjList[curStation].size(); ++i)
				{
					int nextStation = adjList[curStation][i].first;
					int nextTime = curTime + adjList[curStation][i].second;

					if (nextTime < minTime[nextStation])
					{
						minTime[nextStation] = nextTime;
						pq.push({ -nextTime, nextStation });
						routeFrom[nextStation] = curStation;
					}
				}
			}

			int leastTimeEndStationNum = mapping[endStation][0];
			for (int endStationNum : mapping[endStation])
			{
				if (minTime[endStationNum] < minTime[leastTimeEndStationNum])
					leastTimeEndStationNum = endStationNum;
			}

			stack<int> temp;
			temp.push(leastTimeEndStationNum);

			for (int i = leastTimeEndStationNum; routeFrom[i] != -1; i = routeFrom[i])
				temp.push(routeFrom[i]);

			// 결과 출력
			cout << "[탐색 결과], " + startStation + " -> " + endStation << endl;

			cout << "이동 경로 : ";
			string prevStationName = stations[temp.top()].name;
			while (!temp.empty())
			{
				cout << stations[temp.top()].name;
				temp.pop();
				
				if (temp.empty())
					break;

				if (prevStationName == stations[temp.top()].name)
				{
					cout << "(환승)";
					temp.pop();
				}

				cout << " -> ";
				prevStationName = stations[temp.top()].name;
			}
			cout << endl;

			int totalTime = minTime[leastTimeEndStationNum];
			cout << "총 소요 시간 : " << totalTime / 60 << "분 " << totalTime % 60 << "초" << endl;

			break;
		}
	}

	return 0;
}