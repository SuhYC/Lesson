# 컴파일 과정

1. 전처리
 - #include, #define, #ifdef 같은 전처리 지시문을 처리.
 - 매크로 치환과 조건부 컴파일 처리도 이루어짐.
 - 결과물은 확장된 하나의 소스코드 파일 (전처리된 코드)
2. 컴파일
 - 전처리된 코드를 읽고 문법검사, 구문 분석, 의미 분석 진행.
 - 프로그램 구조를 이해하고, 내부표현(중간코드, 추상구문트리)을 만듬.
 - 어셈블리어 코드로 변환.
3. 어셈블리
 - 어셈블리코드를 바이너리코드인 기계어로 번역.
 - 결과물은 오브젝트파일(.o, .obj)
 - 아직 해결되지 않은 심볼(외부함수, 변수)참조가 있을 수 있다.
4. 링킹
 - 여러 오브젝트 파일과 라이브러리를 합쳐서 하나의 실행파일이나 라이브러리를 만듬.
 - 외부 참조를 해결하고 실제 메모리 주소를 결정.
 - 링커는 중복정의, 누락된 심볼 오류 검사.
 - 결과는 실행가능한 바이너리 파일 혹은 라이브러리 파일.
