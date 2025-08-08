# 도커파일
도커 이미지 빌드를 위한 스크립트.

## 예시
```Dockerfile
# 베이스 이미지 (우분투 22.04)
FROM ubuntu:22.04.3

# 필수 패키지 설치 (g++, make, 기타 필요한 툴)
RUN apt-get update && apt-get install -y g++ make && apt-get clean

# 작업 디렉토리 설정
WORKDIR /app

# 프로젝트 소스 복사 (윈도우에서 도커 빌드 컨텍스트에 소스 넣어야 함)
COPY . .

# Makefile로 빌드
RUN make

# 외부 노출 포트
EXPOSE 12345

# 실행 파일 지정 (Makefile 결과물이 server면 server.)
CMD ["./server"]
```

1. 작업디렉토리 : 도커 컨테이너 안에서 명령어들이 실행될 디렉토리.
2. ```COPY . .``` : 첫번째 점은 호스트의 현재 디렉토리 (소스 원본의 폴더), 두번째 점은 작업디렉토리로, 소스를 작업환경으로 복사한다는 의미.
3. ```EXPOSE 12345``` : 컨테이너의 포트 12345를 연다. (아직 포트포워딩된 상태는 아님.)

## 도커 이미지 빌드
wsl 터미널에
```bash
docker build -t my-epoll-server .
```
지정한 경로의 Dockerfile을 통해 도커 이미지를 만든다. <Br/>
. 이 경로가 되며, 이는 호스트의 소스원본폴더가 되겠지. <br/>
my-epoll-server가 도커이미지의 이름이 된다. <br/>

## 컨테이너 실행
wsl 터미널에
```bash
docker run -p 12345:12345 my-epoll-server
```
```-p 12345:12345``` 부분이 포트포워딩! (-p <HostPort>:<ContainerPort>)
