#include "StationConsole.h"

const string RESET = "\33[0m";

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
		cout << Get_ColorCode(255, 128, 128);
        cout << "존재하지 않는 역입니다. 다시 입력해 주세요." << endl;
		cout << RESET;
		break;
    case STATIONERROR::SAME:
		cout << Get_ColorCode(255, 128, 128);
		cout << "출발역과 도착역이 같습니다. 다시 입력해 주세요." << endl;
		cout << RESET;
		break;
    }
}

void CStationConsole::Output_Result(const vector<StationInfo>& path, int totalTime)
{
	// 결과 출력
	cout << "[탐색 결과], ";
	cout << Get_ColorCode(path.front().r, path.front().g, path.front().b) << path.front().name << RESET;
	cout << " -> ";
	cout << Get_ColorCode(path.back().r, path.back().g, path.back().b) << path.back().name << RESET;
	cout << endl;

	cout << "이동 경로 : ";
	for (int i = 0; i < path.size(); ++i)
	{
		cout << Get_ColorCode(path[i].r, path[i].g, path[i].b) << path[i].name << RESET;

		bool isLast = (i == path.size() - 1);
		bool isTransfer = !isLast && (path[i].name == path[i + 1].name);

		if (isTransfer)
		{
			cout << Get_ColorCode(path[i + 1].r, path[i + 1].g, path[i + 1].b) << "(환승)" << RESET;
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

string CStationConsole::Get_ColorCode(int r, int g, int b)
{
	return "\33[38;2;" + to_string(r) + ";" + to_string(g) + ";" + to_string(b) + "m";
}
