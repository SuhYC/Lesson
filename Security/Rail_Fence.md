# Rail Fence
## 레일 펜스 기법

전치 암호 기법 중 하나.   
깊이에 대해 교차하여 n줄로 나누고 각각 만들어진 텍스트를 잇는다.   

    meet me after the toga party
    0101 01 01010 101 0101 01010

    0 : mematrhtgpry
    1 : etefeteoaat

    result : mematrhtgpryetefeteoaat

동일 문자가 출현하는 주기의 문제점이 있다.

## 행순서로 쓰고 열순서로 판독하기
n*m행렬로 평문을 구성한다.   
key를 1~m까지의 숫자를 임의순서로 적은 것을 사용한다. (ex. 4 3 1 2 5 6 7)   

    평문 : attack postponed until two am xyz
    
    1234567 
    attackp 
    ostpone 
    duntilt 
    woamxyz 
    
    암호문 : APTM TTNA AODW TSUO COIX KNLY PETZ

## 이중전위
행과 열 모두 키를 부여하고 전치한다.
