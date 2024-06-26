# Deadlock
## 교착상태

프로세스가 자원을 얻지 못해 진행할 수 없는 상태로
둘 이상의 실행흐름이 한정된 자원을 두고 경쟁할 때 발생할 수 있다.

교착상태의 발생 조건은
## 1. 상호배제 (Mutual Exclusion)
 - 임계구역에 접근할 수 있는 실행흐름은 한번에 하나씩이다.
## 2. 점유대기 (Hold and Wait)
 - 이미 자원 하나 이상을 점유한 상태로 다른 실행흐름이 사용하고있는 자원에 접근하기 위해 대기하고 있는 실행흐름이 있어야한다.
## 3. 비선점 (No Preemption)
 - 다른 실행흐름이 점유하고 있는 자원은 강제로 뺏을 수 없다.
## 4. 순환대기 (Circular Wait)
 - 실행흐름들이 필요한 자원을 가지고 있는 실행흐름들로 순환할 수 있어야한다. (n개의 실행흐름 중 pk는 pk+1의 자원을, pn은 p0의 자원을 기다리는 경우)

위 4가지 조건을 모두 만족하여야 교착상태가 발생한다.
이 얘기는 반대로 4가지 조건 중 하나를 해제하게 되면 교착상태가 풀린다는 말이 된다.
