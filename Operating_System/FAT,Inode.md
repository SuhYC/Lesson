# FAT(File-Allocation-Table), Inode

## 파일할당테이블, 아이노드

해당 내용은 컴퓨터개론 수업에서 들었으나 갈래를 따지자면 OS에 포함되는것 같아 여기에 작성함.

운영체제가 보조기억장치에 데이터를 보관하는 방식이다. <br/>
먼저 어떤 방식을 사용하더라도 0번주소에는 컴퓨터의 구동을 위한 Boot데이터들이 들어있다. <br/>
현대의 컴퓨터는 그렇게 보이지 않게 운영체제가 잘 감싸고 있지만 <br/>
근본적인 방식은 결정론적 튜링머신과 크게 다르지 않다. 순서대로 지시문을 읽으며 진행하는 것이니 0번주소에는 반드시 부팅을 위한 데이터가 들어가야한다.

### File Allocation Table
MS-DOS, Windows 계열의 데이터 보관방식이다. <br/>
FAT에 데이터의 위치정보들이 저장되며 그 정보를 따라 이동하면 실질적인 데이터가 나온다. <br/>
linked allocation 방식의 발전된 형태로, 연결된 데이터의 포인터 중 하나가 문제가 발생했을때, 이후의 데이터가 모두 손실되는 단점을 해결했다.

### Inode
UNIX 계열의 데이터 보관방식이다. <br/>
파일이름과 실제데이터를 제외한 모든 메타데이터를 inode에 저장하여 따로 보관하며 <br/>
파일이름과 실제데이터는 데이터블록에 보관되어있다. 여기에서는 inode번호도 저장되어있다. <br/>
inode에 저장되는 데이터블록 주소는 1. ```direct pointer``` 2. ```single indirect pointer``` 3. ```double indirect pointer``` 4. ```triple indirect pointer```로 구성된다. <br/>
#### ```direct pointer```
직접 데이터 블록을 가리키는 주소다. 이는 4kB의 데이터블록에 대한 주소 하나다. 하나의 inode에 12개가 존재한다. <br/>

#### ```single indirect pointer```
```direct pointer```를 모아둔 블록을 가리키는 주소다. 주소포인터 하나가 4byte를 가지므로 4kB의 블록에는 1024개의 주소가 담겨있다. <br/>

#### ```double indirect pointer```
```single indirect pointer```를 모아둔 블록을 가리키는 주소다. 1024 * 1024개의 주소를 담고있다. 총 4GB의 데이터를 연결할 수 있다. <br/>

#### ```triple indirect pointer```
```double indirect pointer```를 모아둔 블록을 가리키는 주소다. 1024 * 1024 * 1024개의 주소를 담고 있으며 총 4TB의 데이터를 연결할 수 있다.
