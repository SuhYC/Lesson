# Join
데이터분석을 위해 두개 이상의 릴레이션을 결합하여 결과를 받아오는 SQL명령.<br/>
관계형 데이터베이스에서 DB정규화 작업이 이루어진 데이터에 대해 원하는 데이터조합을 받아오기 위해 사용한다.

## Inner Join
두 테이블에서 조건에 맞는 행만 반환.<br/>
즉 양쪽 테이블에 모두 존재하는 데이터만 포함한다.<br/>
교집합.

## Left Outer Join
왼쪽 테이블의 모든 행과, 오른쪽 테이블의 조건에 맞는 행을 반환한다.<br/>
오른쪽 테이블에 일치하는 행이 없다면, 해당 데이터를 Null로 표시하여 반환한다.

## Right Outer Join
왼쪽 테이블의 조건에 맞는 행과, 오른쪽 테이블의 모든 행을 반환한다.<br/>
왼쪽 테이블에 일치하는 행이 없다면, 해당 데이터를 Null로 표시하여 반환한다.

## Full Outer Join
양쪽 테이블의 모든 행을 반환한다. <br/>
각 테이블에 일치하는 행이 없다면, 해당 데이터를 Null로 표시하여 반환한다.

## Cross Join
두 테이블의 카티션 곱을 반환한다.
