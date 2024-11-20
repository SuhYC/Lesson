# 사용자 지정 빌드 도구
gRPC를 Visual Studio환경에서 C++프로젝트에 사용하기 위해서는 일련의 과정이 필요하다. <br/>
1. ```.proto```파일을 작성 또는 수정한다.
2. ```.proto```파일을 컴파일한다.
3. ```$(InputName).pb.h```, ```$(InputName).pb.cc```, ```$(InputName).grpc.pb.h```, ```$(InputName).grpc.pb.cc``` 파일을 프로젝트에 포함한다.
4. 추가 포함 디렉토리 설정을 한다.
5. C++ Project를 컴파일한다.

이 때, ```.proto```파일은 수정할 때마다 새로 컴파일을 해야하는데, 이는 생각보다 귀찮으므로 VS2022환경에서 컴파일 자동화를 해두는 것이 좋다.

# ```.proto``` 컴파일 자동화
1. 프로젝트에 ```.proto```파일을 생성 또는 불러온다.
2. 해당 파일을 우클릭하여 속성페이지로 들어간다.
3. 일반(General) 탭에서 항목 형식(Item Type)을 사용자 지정 빌드 도구(Custom Build Tool)로 설정한다.
4. 좌측 구성 속성의 사용자 지정 빌드 도구 탭이 생겼다면 해당 탭에서 명령줄(Command Line) 항목에 다음 문구를 입력한다.
```
protoc -I=$(ProjectDir) --grpc_out=$(ProjectDir) --plugin=protoc-gen-grpc=<path_to_grpc_cpp_plugin> $(InputPath)
protoc -I=$(ProjectDir) --cpp_out=$(ProjectDir) $(InputPath)
```
(좌측 탭에 메뉴가 나타나지 않는다면 적용시킨 후 다시 속성창을 연다.) <br/>
5. 출력(Output) 항목에 다음 문구를 입력한다.
```
$(ProjectDir)$(InputName).grpc.pb.cc
$(ProjectDir)$(InputName).grpc.pb.h
$(ProjectDir)$(InputName).pb.cc
$(ProjectDir)$(InputName).pb.h
```
6. 적용한다.
