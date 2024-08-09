# Philosophers

1965년 Edsger Dijkstra에 의해 만들어진 [식사하는 철학자](https://en.wikipedia.org/wiki/Dining_philosophers_problem) 문제 풀이

동기화 및 상호 배제를 통해 교착상태(Deadlock)와 기아(Starvation)을 피하는게 목적이다.
- `./philo` 디렉터리는 스레드(Thread)와 뮤텍스(Mutex)를 활용
- `./philo_bonus` 디렉터리는 프로세스(Process)와 세마포어(Semaphore)를 활용

## 교착상태(Deadlock)
다른 프로세스가 점유하고 있는 자원을 서로 기다릴 때 무한 대기에 빠지는 상황

### 발생 조건
아래의 조건을 모두 만족하면 교착 상태가 발생한다.
1. 상호 배제(Mutual Exclusion): 한 번에 하나의 프로세스만 자원을 사용한다.
2. 점유 대기(Hold and Wait): 자원을 가진 상태로 다른 프로세스의 자원을 점유하기 위해 대기한다.
3. 비선점(Non Preemptive): 이미 할당된 자원을 강제로 뺏을 수 없다.
4. 환형대기(Circle wait): 대기 프로세스의 집합이 순환 형태로 대기하고 있다.

### 해결 방법
1. 예방(Prevention): 발생 조건을 만족하지 않게 예방함으로써 교착상태를 방지한다.
2. 회피(Avoidance): 발생 조건을 배제하지 않고 교착상태가 발생할 때 적절히 회피한다.
3. 회복(Recovery): 교착 상태가 발생할 경우 찾아내어 회복한다.
4. 무시(Ignore): 교착 상태 해결을 위한 오버헤드가 큰 경우 무시한다. 

## Usage
```sh
$./philo
Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosophers_must_eat]

# (bonus) 프로세스 확인
$ ps -ef | grep philo

# (bonus) PSXSEM(POSIX Semaphore) 확인
$ lsof | grep PSXSEM
```

## 철학자 생존 조건(?)
- 모든 경우, `time_to_die` > `time_to_eat` + `time_to_sleep`
  - 짝수일 때, `time_to_die` > `time_to_eat` * 2 + a
  - 홀수일 때, `time_to_die` > `time_to_eat` * 3 + a

```sh
$ ./philo 1 800 200 200   # starvation
$ ./philo 5 800 200 200   # infinity
$ ./philo 5 800 200 200 7 # eating >= 35

$ ./philo 4 410 200 200   # infinity
$ ./philo 4 310 200 100   # starvation

$ ./philo 3 310 103 103   # ininity
$ ./philo 3 310 104 104   # starvation
$ ./philo 4 420 242 240   # starvation
```

# 참고자료
- https://wiki.sei.cmu.edu/confluence/pages/viewpage.action?pageId=87151970
