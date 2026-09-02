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

int main()
{
	vector<string> stationNames =
	{
		"용산", "남영", "서울역", "시청", "종각", "종로3가", "종로5가", "동대문", "동묘앞", "신설동", "제기동", "청량리",
		//	"당산", "합정", "홍대입구", "신촌", "이대", "아현", "충정로", "입지로입구", "을지로3가", "을지로4가", "동대문역사문화공원", "신당", "상왕십리", "왕십리",
		//	"경복궁", "안국", "종로3가", "을지로3가", "충무로", "동대입구", "약수", "금호", "옥수",
		//	"이촌", "신용산", "삼각지", "숙대입구", "서울역", "회현", "명동", "충무로", "동대문역사문화공원", "동대문", "혜화",
		//	"마포", "공덕", "애오개", "충정로", "서대문", "광화문", "종로3가", "을지로4가", "동대문역사문화공원", "청구", "신금호", "행당", "왕십리", "마장",
		//	"망원", "합정", "상수", "광흥창", "대흥", "공덕", "효창공원앞", "삼각지", "녹사평", "이태원", "한강진", "버티고개", "약수", "청구",
	};

	vector<int> transitTimes =
	{
		110, 120, 120, 100, 90, 90, 90, 80, 80, 90, 100
	};
	
	unordered_map<string, int> um;										// 역명 -> 숫자 매핑 컨테이너
	vector<vector<pair<int, int>>> adjList(stationNames.size());		// 인접 노드 저장 행렬
	vector<int> minTime(stationNames.size(), INF);						// 최소시간 갱신할 배열
	priority_queue<pair<int, int>> pq;									// 최소시간 정렬할 우선순위큐
	vector<int> routeFrom(stationNames.size(), 0);						// 최소시간 경로를 저장할 배열

	for (int i = 0; i < stationNames.size(); ++i)
		um[stationNames[i]] = i;

	for (int i = 0; i < stationNames.size() - 1; ++i)
	{
		int from = um[stationNames[i]];
		int to = um[stationNames[i + 1]];
		int time = transitTimes[i];

		adjList[from].push_back({ to, time });
		adjList[to].push_back({ from, time });
	}

	string startStation, endStation;

	while (true)
	{
		cout << "출발역 : ";
		cin >> startStation;

		if (um.end() == um.find(startStation))
		{
			cout << "존재하지 않는 역입니다. 다시 입력해 주세요." << endl;
			continue;
		}

		cout << "도착역 : ";
		cin >> endStation;

		if (um.end() == um.find(endStation))
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
			int startNode = um[startStation];
			int endNode = um[endStation];

			minTime[startNode] = 0;			// 시작역 시간 0 초기화
			pq.push({ 0, startNode });

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

			cout << "[탐색 결과], " + startStation + " -> " + endStation << endl;

			stack<int> temp;
			temp.push(endNode);
			for (int i = endNode; i != startNode; i = routeFrom[i])
			{
				temp.push(routeFrom[i]);
			}

			cout << "이동 경로 : ";
			while (!temp.empty())
			{
				cout << stationNames[temp.top()];
				temp.pop();
				if (!temp.empty())
					cout << " -> ";
			}
			cout << endl;

			int totalTime = minTime[endNode];
			cout << "총 소요 시간 : " << totalTime / 60 << "분 " << totalTime % 60 << "초" << endl;
			break;
		}
	}

	return 0;
}