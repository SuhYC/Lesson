# Paging
## 페이징
virtual memory는 보조기억장치의 스왑영역에 저장되며 주소를 page, offset으로 지정한다.<br/>
physical memory는 주기억장치에 저장되며 주소를 frame, offset으로 지정한다.<br/>
스왑영역의 데이터를 가져와 메모리에 적재하여 사용한다.<br/>
virtual memory의 임의의 데이터 (p,o)는 페이지테이블을 통해 physical memory의 (f,o)로 대응된다.

### Page Table
virtual memory와 physical memory를 연결하기 위한 테이블이다. <br/>
3개의 flag(valid, dirty, reference)가 존재한다. <br/>
#### valid
- 해당 주소가 유효함
#### dirty
- modified, 수정됨 (보조기억장치에 반영할 필요성이 있다.)
#### reference
- 참조가 되었는지 (사용했는지)

# Page Table Base Register (PTBR)
- 페이지테이블의 시작주소를 가리키는 레지스터이다.
# Translation Lookaside Buffer (TLB)
- 페이지테이블을 통한 접근은 주기억장치에 2번의 접근이 필요하다 <br/>
- 캐시를 사용하여 페이지테이블을 통한 접근보다 빠르다.
- 자주 쓰는 페이지와 그에 맞는 프레임 주소를 저장한다.
- 문맥교환시 TLB를 flush. 비운다.
