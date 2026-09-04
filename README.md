# 🚇러쉬에잇 과제
C++를 사용해 주어진 지하철 노선 정보를 바탕으로 최단 경로를 탐색하는 프로그램을 구현했습니다.

## 🪄주요 기능
- 출발역/도착역 입력 시 최단 시간 이동 경로 탐색 및 결과 출력
- 존재하지 않는 역이나 동일한 출발역/도착역 입력 시 예외 처리
- 이동 경로 상 환승 구간 표시
- csv 파일로 노선 데이터 관리

## 💻실행 화면
<img width="999" height="449" alt="스크린샷 2026-09-05 005453" src="https://github.com/user-attachments/assets/8ead30f5-015e-4587-8a91-a68a09bcb3b2" />

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
- 테스트용으로 헤더에 두었던 노선 정보 배열을 유지보수를 고려해 `Station_Data.csv`로 분리했습니다.
- 탐색 로직(CNavigation)과 입출력(CStationConsole)이 서로 의존하지 않도록 역할을 분리했습니다.
- 요구 기능과 결과 출력 형태는 그대로 유지하면서 노선 구분이 쉽도록 텍스트 색상 변경 기능을 추가적으로 구현해봤습니다.

## 🔗참고 자료
- [C++ 다익스트라(Dijkstra) 알고리즘 개념 및 구현 (무방향 그래프)](https://devshovelinglife.tistory.com/557)
- [[C++/C#] CSV 파일 읽기](https://kukuta.tistory.com/216)
- [[C언어] 콘솔에 출력되는 텍스트 색상 변경](https://velog.io/@chez_bono/C-%EC%BD%98%EC%86%94%EC%97%90-%EC%B6%9C%EB%A0%A5%EB%90%98%EB%8A%94-%ED%85%8D%EC%8A%A4%ED%8A%B8-%EC%83%89%EC%83%81-%EB%B3%80%EA%B2%BD)
