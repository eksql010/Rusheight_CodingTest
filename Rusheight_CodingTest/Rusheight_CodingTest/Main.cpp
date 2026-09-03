#include "Defines.h"
#include "Navigation.h"

int main()
{	
	CNavigation navigation;
	navigation.Initialize();

	string startStation, endStation;

	while (true)
	{
		cout << "출발역 : ";
		cin >> startStation;

		if (navigation.Find_Station(startStation).empty())
		{
			cout << "존재하지 않는 역입니다. 다시 입력해 주세요." << endl;
			continue;
		}

		cout << "도착역 : ";
		cin >> endStation;

		if (navigation.Find_Station(endStation).empty())
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
			// 최단 경로 탐색
			navigation.Find_ShortestPath(startStation, endStation);

			// 결과 출력
			cout << "[탐색 결과], " + startStation + " -> " + endStation << endl;

			vector<string> path = navigation.Get_Path();
			cout << "이동 경로 : ";
			for (int i = 0; i < path.size(); ++i)
			{
				cout << path[i];

				bool isLast = (i == path.size() - 1);
				bool isTransfer = !isLast && (path[i] == path[i + 1]);

				if (isTransfer)
				{
					cout << "(환승)";
					++i;
					isLast = (i == path.size() - 1);
				}
				
				if (!isLast)
					cout << " -> ";

			}
			cout << endl;

			int totalTime = navigation.Get_TotalTime();
			cout << "총 소요 시간 : " << totalTime / 60 << "분 " << totalTime % 60 << "초" << endl;
			break;
		}
	}

	return 0;
}