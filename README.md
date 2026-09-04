# 🚇러쉬에잇 과제
C++를 사용해 주어진 지하철 노선 정보를 바탕으로 최단 경로를 탐색하는 프로그램을 만들었습니다.

## 🪄주요 기능
- 출발역/도착역 입력 시 최단 경로 및 총 소요 시간 출력
- 존재하지 않는 역 이름이나 동일한 출발/도착역 입력 시 재입력 요청
- 경로 상 환승 구간 표시
- csv 파일로 노선 데이터 관리

## 💻실행 화면
<img width="867" height="464" alt="image" src="https://github.com/user-attachments/assets/f15b2ccc-f093-4569-a33d-15dc036d53e9" />

## 📚기술 스택
- C++
- Visual Studio 2022
- Git / GitHub / Sourcetree
- 다익스트라 알고리즘

## 💡프로젝트 구조
입력 → 경로 탐색 → 결과 출력 흐름으로 동작합니다.

```cpp
void CStationApp::Execute()
{
	string startStation, endStation;
	Input_Stations(startStation, endStation);
	m_Navigation.Find_ShortestPath(startStation, endStation);
	m_Console.Output_Result(m_Navigation.Get_Path(), m_Navigation.Get_TotalTime());
}
```

| 클래스 | 역할 |
|---|---|
| CNavigation | 노선 데이터 로딩, 그래프 구성 및 최단 경로 탐색 (다익스트라 알고리즘) |
| CStationConsole | 콘솔 입출력, 에러 메시지 출력 |
| CStationApp | 전체 흐름 관리 |

## 💭고민한 점
- 유지보수를 고려해 테스트용으로 헤더에 두었던 역 데이터 배열을 `Station_Data.csv`로 분리했습니다.
- 탐색 로직(CNavigation)과 입출력(CStationConsole)이 서로 의존하지 않도록 역할을 분리했습니다.

## 🔗참고 자료
- [C++ 다익스트라(Dijkstra) 알고리즘 개념 및 구현 (무방향 그래프)](https://devshovelinglife.tistory.com/557)
- [[C++/C#] CSV 파일 읽기](https://kukuta.tistory.com/216)
