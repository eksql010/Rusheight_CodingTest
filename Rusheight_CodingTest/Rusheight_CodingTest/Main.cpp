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

#pragma region TEST_CODE
	/*
	const int nodeCount = 7; // 노드의 개수
	vector<pair<int, int>> adjList[nodeCount]; // 그래프
	
	int edgeCount = 7;
	
	for (int i = 0; i < edgeCount; ++i)
	{
		int from, to, weight;
		cin >> from >> to >> weight;
		adjList[from].push_back({ to, weight });
		adjList[to].push_back({ from, weight });
	}
	
	adjList[1] = { { 2, 2 }, { 4, 1 } };
	adjList[2] = { { 1, 2 }, { 3, 3 }, { 4, 2 } };
	adjList[3] = { { 2, 3 }, { 6, 5 } };
	adjList[4] = { { 1, 1 }, { 2, 2 }, { 5, 1 } };
	adjList[5] = { { 4, 1 }, { 6, 2 } };
	adjList[6] = { { 3, 5 }, { 5, 2 } };
	*/
#pragma endregion

	srand(static_cast<unsigned int>(time(0)));

	vector<vector<pair<int, int>>> adjList(nodeCount + 1);		// 인접 노드 저장 행렬
	vector<int> minDist(nodeCount, INF);						// 최단거리 갱신할 배열
	priority_queue<pair<int, int>> pq;							// 최단거리 정렬할 우선순위큐
	vector<int> routeFrom(nodeCount, 0);						// 최단거리 경로를 저장할 배열

	int nodeCount, edgeCount, startNode, endNode;				// 입력 받을 변수

	cout << "노드 개수 : ";
	cin >> nodeCount;
	cout << "간선 개수 : ";
	cin >> edgeCount;

	for (int i = 0; i < edgeCount; ++i)
	{
		int from = rand() % nodeCount + 1;
		int to = rand() % nodeCount + 1;
		while (to == from) to = rand() % nodeCount + 1;			// 자기 자신으로 가는 간선 방지

		int dist = rand() % 9 + 1;								// 거리(가중치) 1~9 랜덤

		adjList[from].push_back({ to, dist });
		adjList[to].push_back({ from, dist });

		cout << from << " - " << to << " (거리: " << dist << ")" << endl;
	}

	cout << "출발 노드 : ";
	cin >> startNode;
	cout << "도착 노드 : ";
	cin >> endNode;

	minDist[startNode] = 0;					// 시작 노드 거리 0 초기화
	pq.push({ 0, startNode });

	while (!pq.empty())
	{
		int curDist = -pq.top().first;		// 현재 방문한 정점의 거리
		int curNode = pq.top().second;		// 정점의 인덱스
		pq.pop();							// 꺼내기

		for (int i = 0; i < adjList[curNode].size(); ++i)
		{
			int nextNode = adjList[curNode][i].first;				// 인접 정점 번호
			int nextDist = curDist + adjList[curNode][i].second;	// 인접 정점까지 거리

			if (nextDist < minDist[nextNode])
			{
				minDist[nextNode] = nextDist;
				pq.push({ -nextDist, nextNode });
				routeFrom[nextNode] = curNode;
			}
		}
	}

	cout << "[탐색 결과], ";
	cout << startNode;
	cout << " -> ";
	cout << endNode << endl;

	stack<int> temp;
	temp.push(endNode);
	for (int i = endNode; i != startNode; i = routeFrom[i])
	{
		temp.push(routeFrom[i]);
	}

	cout << "이동 경로 : ";
	while (!temp.empty())
	{
		cout << temp.top();
		temp.pop();
		if (!temp.empty()) 
			cout << " -> ";
	}
	cout << endl;

	cout << "총 이동 거리 : " << minDist[endNode] << endl;

#pragma region TEST_CODE
	/*
	unordered_set<string> stations =
	{
		// 1호선
		"용산", "남영", "서울역", "시청", "종각", "종로3가", "종로5가", "동대문", "동묘앞", "신설동", "제기동", "청량리",
		// 2호선
		"당산", "합정", "홍대입구", "신촌", "이대", "아현", "충정로", "입지로입구", "을지로3가", "을지로4가", "동대문역사문화공원", "신당", "상왕십리", "왕십리",
		// 3호선
		"경복궁", "안국", "종로3가", "을지로3가", "충무로", "동대입구", "약수", "금호", "옥수",
		// 4호선
		"이촌", "신용산", "삼각지", "숙대입구", "서울역", "회현", "명동", "충무로", "동대문역사문화공원", "동대문", "혜화",
		// 5호선
		"마포", "공덕", "애오개", "충정로", "서대문", "광화문", "종로3가", "을지로4가", "동대문역사문화공원", "청구", "신금호", "행당", "왕십리", "마장",
		// 6호선
		"망원", "합정", "상수", "광흥창", "대흥", "공덕", "효창공원앞", "삼각지", "녹사평", "이태원", "한강진", "버티고개", "약수", "청구",
	};
	
	string startStation = "";
	string endStation = "";
	
	while (true)
	{
		cout << "출발 역 : ";
		cin >> startStation;
	
		if (stations.end() == stations.find(startStation))
		{
			cout << "존재하지 않는 역입니다. 다시 입력해 주세요." << endl;
			continue;
		}
	
		cout << "도착 역 : ";
		cin >> endStation;
	
		if (stations.end() == Stations.find(endStation))
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
			cout << "[탐색 결과], " + startStation + " -> " + endStation << endl;
			cout << "이동경로 : " << endl;
			cout << "총 소요 시간 : " << endl;
			break;
		}
	}
	*/
#pragma endregion

	return 0;
}