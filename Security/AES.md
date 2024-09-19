# AES (Rijndael Algorithm)

대칭키 암호화. <br/>
key expansion으로 암호화키로부터 서브키 ki를 얻어내고, 4가지의 함수를 통해 평문을 암호화한다. <br/>

## 함수

### SubBytes
1바이트씩 구분하여 각각의 데이터를 치환한다. <br/>
S-box라는 치환테이블에서 각각의 데이터가 어떤 데이터로 변환되는지 확인할 수 있다.

    unsigned char after = Sbox[before];

4비트의 row, 4비트의 column으로 테이블을 검색한다고 설명되는 글이 많으나, 어차피 1바이트 기준으로 검색하는 것과 큰 차이가 없다.

### ShiftRows
AES128 기준, 16바이트의 데이터를 4*4 크기의 1바이트로 이루어진 행렬로 보고 섞는다.

    0x00 0x01 0x02 0x03      0x00 0x01 0x02 0x03 // 그대로
    0x04 0x05 0x06 0x07      0x05 0x06 0x07 0x04 // 왼쪽으로 1칸
    0x08 0x09 0x0a 0x0b  ->  0x0a 0x0b 0x08 0x09 // 왼쪽으로 2칸
    0x0c 0x0d 0x0e 0x0f      0x0f 0x0c 0x0d 0x0e // 오른쪽으로 1칸

이 과정을 통해 1block의 크기를 소분해서 처리한것과 다른 결과를 만든다. (위 기준으로 4바이트마다 다른 연산이 들어간다.)

### MixColumns
input a에 대해 output r은 다음과 같은 행렬곱으로 생성된다.

    r0   2 3 1 1 | a0
    r1   1 2 3 1 | a1
    r2 = 1 1 2 3 | a2
    r3   3 1 1 2 | a3

복호화 과정에서 쓰이는 행렬은 다르다.

    14 11 13 9
    9 14 11 13
    13 9 14 11
    11 13 9 14


### AddRoundKey
KeyExpansion을 통해 나온 서브키를 데이터에 xor한다.<br/>
AES-128기준 4words로 이루어진 128비트의 라운드키를 xor한다.

### KeyExpansion
AES-128 기준, 암호화키의 길이는 128비트이며, 이를 4word로 생각하고 구성한다. (1word == 4bytes) <br/>
```w(0)~w(4)```는 암호화키를 그대로 쓴다.<br/>
(AES-192, AES256에서는 ```0~4```가 아닌 ```0~6```, ```0~8```이다. word의 크기는 그대로지만 키의 길이가 192, 256이기 때문)<br/>
```w(4k) = w(4(k-1)) xor RotWord(SubWord(w(4k-1))) xor Rcon(k)``` <br/>
그외의 w(i)에 대해서는 w(i-4) xor w(i-1)이다. <br/>
AES-256에서는 별도로 w(8k+4)에서 변칙으로 다른 공식을 적용한다.

### RotWord
4bytes의 word를 byte단위로 한칸 민다.

    RotWord([0x00, 0x01, 0x02, 0x03]) == [0x01, 0x02, 0x03, 0x00]

### SubWord
SubBytes를 수행한다. Sbox테이블로 치환하면 된다.

### Rcon (Round Constant)
Key Expansion에 사용되는 상수. <br/>
0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36...


### 전체 과정
1. KeyExpansion을 통해 Subkey 생성
2. AddRoundKey (0 Round)
3. SubBytes, ShiftRows, MixColumns, AddRoundKey (1~N-1Round) // AES-128 : N == 10
4. SubBytes, ShiftRows, AddRoundKey (N Round)
