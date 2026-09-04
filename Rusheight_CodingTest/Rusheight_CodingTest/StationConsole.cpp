#include "StationConsole.h"

CStationConsole::CStationConsole()
{
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
}

string CStationConsole::Input_Station(const string& prompt)
{
    string input;

    cout << prompt;
    cin >> input;

    return input;
}

void CStationConsole::Output_Error(STATIONERROR error)
{
    switch (error)
    {
    case STATIONERROR::NOTFOUND:
        cout << "존재하지 않는 역입니다. 다시 입력해 주세요." << endl;
        break;
    case STATIONERROR::SAME:
        cout << "출발역과 도착역이 같습니다. 다시 입력해 주세요." << endl;
        break;
    }
}

void CStationConsole::Output_Result(const vector<StationInfo>& path, int totalTime)
{
	// 결과 출력
	cout << "[탐색 결과], " + path.front().name + " -> " + path.back().name << endl;

	cout << "이동 경로 : ";
	for (int i = 0; i < path.size(); ++i)
	{
		cout << path[i].name;

		bool isLast = (i == path.size() - 1);
		bool isTransfer = !isLast && (path[i].name == path[i + 1].name);

		if (isTransfer)
		{
			cout << "(환승)";
			++i;
			isLast = (i == path.size() - 1);
		}

		if (!isLast)
		{
			cout << " -> ";
		}
	}
	cout << endl;

	cout << "총 소요 시간 : " << totalTime / 60 << "분 " << totalTime % 60 << "초" << endl;

	system("pause");
}

WORD CStationConsole::Get_Color(int stationLine)
{
	// 이후 일부 폰트 색상 변경할 때 사용할 함수

    return WORD();
}
