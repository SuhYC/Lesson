# Scheduling Algorithm

## FCFS (First Come First Served)

먼저 들어온 작업을 먼저 처리하는 방식
구현 자체는 매우 간단하다. 큐를 통해 처리한다.
오래걸리는 작업이 후순위 작업들을 길게 대기시킬 수 있다는 단점이 있다.

## SJF (Shortest Job First)

가장 짧은 시간이 걸리는 작업을 먼저 처리하는 방식.
대기시간이 가장 짧게 구성되는 이상적인 Scheduling이라고 볼 수도 있지만
작업이 계속 들어온다면 소외되는 작업이 존재할 수 있다는 단점이 있다.

## Round Robin

각 작업이 가진 우선순위에 따라 시간을 분배하여 수행하는 방식.
시간 내에 해결하지 못한 작업은 다시 Scheduling Queue에 넣으며 회전시킨다.
시간분배가 중요하다.
시간이 너무 길게 주어지면 FCFS와 다를바 없고
시간이 너무 짧게 주어지면 문맥교환 비용이 커지게 된다.

## Priority Scheduling

각 작업이 가진 우선순위에 따라 처리하되, 시간 제한을 두지는 않는다는 점이 RR과 다르고
낮은 우선순위로 인해 소외되는 작업이 발생할 수 있으므로 Aging을 통해 오랜 대기시간을 가진 작업의 우선순위를 올리는 방법이 존재한다.
