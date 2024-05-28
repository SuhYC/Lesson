# Data Communication Time
## 정보 전달 시간

어떠한 데이터가 특정장치로부터 다른장치로 이동하는데 걸리는 시간.

### Propagation Delay
전파시간. 물리적으로 전기신호가 이동하는 데에 걸리는 시간이다.

$d : LengthOfPhysicalLink$   
$s : PropagationSpeed (\approx 2 * 10^8 m / sec)$   
$Propagation Delay : d / s $

전기신호의 이동시간은 광속이며, 구리선에서의 이동속도는 일반적으로 $0.59c \leq v \leq 0.77c$   
당연히도 전기신호가 전달되는 시간이며 실제 전자의 이동속도는 그보다 현저히 느리다.

### Transmission Time
이동시간. 계층간 이동하는 데에 걸리는 시간이다.

$L : PacketLength$   
$R : LinkBandWidth$   
$TransmissionDelay : L / R$

### Queueing Delay
대기시간. 큐에서 대기하는 데에 걸리는 시간이다.   
라우터의 처리능력과 혼잡한 정도에 달려있음.

$R : LinkBandWidth$   
$L : PacketLength$   
$a : AveragePacketArrivalRate$

La/R이 1인 경우 한도가 가득참, 0인 경우 들어온 데이터 없음.   
1에 가까워질수록 딜레이가 어마어마하게 길어진다.

### Processing Time
처리시간. 노드에서 처리하는 데에 걸리는 시간이다.   
에러비트를 확인하고 출력링크를 결정.   
$Typically < msec$
