# MultiThreadProject

## 프로젝트 설명
이 프로젝트는 C언어로 작성된 작성된 3개의 윈도우 간의 데이터 통신 및 멀티쓰레딩 실습 프로젝트입니다. 각 윈도우는 서로 다른 좌표의 공을 표현하며, 이 공의 좌표는 각 윈도우간에 실시간으로 전송되어 동기화됩니다.
## 사용 기술
### 개발 언어 및 플랫폼
- **C**
  - 메인 애플리케이션 로직 및 윈도우 메시지 처리에 사용
- **Win32 API**
  - 윈도우 애플리케이션 개발을 위한 API.
## 실행 화면
![운영체제 영상](https://github.com/sunkk8482/MultiThreadProject/assets/86597542/d9afa260-301b-4fbb-a5ce-f9910d308a9e)
## 주요 기능
- **다중 윈도우 관리**: 세 개의 윈도우를 생성하고 각 윈도우 간의 통신을 통해 공의 좌표를 전송합니다.
- **멀티쓰레딩**: 각 윈도우는 독립적인 쓰레드로 실행되며, 동시성 문제를 해결합니다
- **실시간 데이터 통신**: 각 윈도우의 공의 좌표를 실시간으로 전송하고 동기화 합니다.
