# 데이터 순차 조회
일반적으로 DB에 있는 데이터를 조회하는 과정에서 너무 많은 데이터를 조회하는 것은 DB 성능을 떨어뜨릴 수 있다. <br/>
이를 방지하기 위해 다수의 데이터를 가져올 때는 상위 몇개의 데이터만을 가져오게 되는데, <br/>
이 때 사용되는 MSSQL 명령어가 바로 ```OFFSET```과 ```FETCH```이다. <br/>
MYSQL에서는 ```LIMIT```과 ```OFFSET```을 사용할 수 있다.

## OFFSET N ROWS FETCH NEXT M ROWS ONLY; (MSSQL)
N개 행을 건너 뛴 후 M개 행만 가져온다. <br/>
예제 쿼리를 짠다면 다음과 같다. <br/>
```SQL
SELECT column1, column2
FROM table_name
ORDER BY column1 -- MSSQL의 경우는 ORDER BY절을 반드시 쓸 
OFFSET 40 ROWS FETCH NEXT 20 ROWS ONLY; --40개 행을 건너 뛰고 20개 행을 가져와!
```
보통 이러한 쿼리는 페이지를 구분하여 특정갯수씩을 가져오기 때문에 ```FETCH NEXT M```부분의 숫자 M은 고정이며 <br/>
```OFFSET N ROWS```부분의 숫자 N은 페이지번호k에 대해 N = k * M이 되는 N을 적는게 보편적이다. <br/>

## LIMIT N OFFSET M; (MYSQL)
N개 행을 건너 뛴 후 M개 행만 가져온다. <br/>
예제 쿼리를 짠다면 다음과 같다. <br/>
```SQL
SELECT column1, column2
FROM table_name
LIMIT 20 OFFSET 40; --40개 행을 건너 뛰고 20개 행을 가져와!
```

## ROW_NUMBER() (Oracle)
```ROW_NUMBER()```를 사용하여 특정 범위의 데이터를 가져올 수 있다. <br/>
```ROW_NUMBER()```는 윈도우 함수이기 때문에 ORDER BY가 필요하다. <br/>
예제 쿼리를 짠다면 다음과 같다. <br/>
```SQL
SELECT column1, column2
FROM (
    SELECT column1, column2, ROW_NUMBER() OVER (ORDER BY column1) AS rn
    FROM table_name
) 
WHERE rn BETWEEN 41 AND 60;
```
