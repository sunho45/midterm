# 포드 풀커슨 알고리즘


## 포드 풀커슨 알고리즘이란?

Source(시작점)에서 Sink(도착점)으로  얼마나 많은 유량을 동시에 보낼 수 있는지 계산하는 문제에서 해답을 구하는 것을 도와준다. 시작점에서 도착점까지의 최대 유량을 구할떄 주어진 정점을 탐색하는 경우 DFS를 써 탐색한다.

### 네트워크 유량의 특징

1) 각 간선에 흐르는 유량은 각 간선의 용량을 넘을 수 없다.

![image](https://user-images.githubusercontent.com/100903674/164578818-0783e885-02fa-4b5d-abe2-2c83e7d9464b.png)

예를 들어 A지점과  B지점을 잇는 간선의 용량이 8이라면 8을 넘는 유량은 들어올 수 없다.

2) 유량의 보존
![image](https://user-images.githubusercontent.com/100903674/164579861-0ae7b09d-e747-42b1-8d2b-5ab02ed20460.png)

위의 그래프는 A-B-C에서 A-B의 간선의 용량은 8 B-C 간의 간선의 용량은 3이다. A에서 C로 보낼수 있는 유량은 8같지만 1의 법칙에 따라  B-C간의 간선에서의
유량이 최대 3이므로 그 이상의 유량을 넣을 순 없다. 따라서 B-C의 간선에 흐르는 유량은 3이다. 데이터의 변형없이 보내기 위해서 시작점에서 들어오는 유량과 도착점에서 들어오는 유량은 같아야 하므로 A-B의 간선의 유량은 3 따라서 A-C간에 흐르는 유량은 3


3) 유량의 대칭

간선 A-B  가 있고, A-B의 capacity가 8이 라면, B-A 라는 가상의 간선이 있고, 해당 간선의 용량은 0 이라고 가정하는 것. 이때 해당 간선의 용량이 0 즉 이므로 논리값에 큰 영향을 주지는않는다. 이때 간선의 유량 F(A,B)=-F(B,A)  공식이 성립한다.
![image](https://user-images.githubusercontent.com/100903674/165745128-0237bfb1-a6b8-429b-a90a-41c507603979.png)






### 포드 풀커슨 알고리즘의 작동방식

1)Source(시작점)에서  Sink(도착점)까지는의 여유용량이 있는 경로를 DFS알고리즘을 통해 찾는다. 


2) 찾아낸 경로에서 최대 유량을 찾는다. 이때 최대 유량은 찾은 경로의 남은 용량의 최솟값이다.

3) 찾아낸 경로에서 최대 유량을 흘려 보낸다.

4) 여유용량이 있는 경로를 찾는 것을 실패할때까지 위의 과정을 반복해준다.

ex) 다음과 같이 유량이 주어진 그래프가 있다고 가정해보자.
![image](https://user-images.githubusercontent.com/100903674/165752494-542147aa-705e-4536-a81b-a309fa10ea6a.png)

A가 1의 위치 B가 4의 위치 C가 2의 위치  D가 3의 위치라 가정




DFS를 통해 A-C-D-B 를 먼저 탐색하게 되면
![image](https://user-images.githubusercontent.com/100903674/164612935-4e6957f9-0ade-4b27-8130-625a572df5fd.png)

최대 유량은 4가 된다. 하지만 유량의 대칭을 통해 좀더 많은 유량을 뽑아낼 수 있다. (F(C,D)= C에서 D로의 유량 F(D,C)= D에서 C로의 유량) 
F(C,D)=-F(D,C)임을 이용하여 F(D,C)의 유량은 -4임을 알수 있다. 


D-C 간선의 용량은 실제하지 않으므로 0이다. 이는 허수이므로 논리값에 커다란 영향을 끼치지 않는다.

간선 하나당 (용량-흐르고 있는 유량)만큼 데이터를 추가할 수 있다.
따라서 0-(-4)=4만큼 추가할 수 있다.

그러므로 A-D-C-B경로로 가게 하면 

![image](https://user-images.githubusercontent.com/100903674/164725374-aa293af8-9437-4931-b4cd-be931a2c1626.png)


결과적으로 (C,D)의 유량과 (D,C)의 유량이 상쇄되어 

![image](https://user-images.githubusercontent.com/100903674/164725446-854acf63-e498-411c-aa48-b62bff66db0c.png)


된다 여유용량이 있는 경로가 더이상 없으니 프로그램의 연산을 종료시켜준다.

따라서 A(Source)에서 B(Sink)까지 가는데에 최대 유량은 8인것을 알 수 있다.


## 실행결과
업로드된 코드르를 넣고 실행하면
![image](https://user-images.githubusercontent.com/100903674/164619759-1d22d5d4-fe84-4a4b-bca2-07591aaa9ea1.png)

정상적으로 출력되는 것을 확인 할 수 있다.




## 포드 풀커슨 알고리즘의 시간 복잡도

최대 유량을 F라 한다면 각 증가 경로 당 유량이 최소1이다. 그러므로 증가경로의 최대 개수는 F가 된다. 
하나의 증가 경로를 찾는데 방문하는 정점과 간선은 최대로 계산할시 각각 V,E개이다. 따라서 최대 유량을 얻어내는데 필요한 시간 복잡도는 검사하는데 필요한 시간 |V|+|E|에 최대유랑 F 를곱한
O((|E|+|V|)F)이다. .

## 포드 풀커슨은 완전한 알고리즘인가?

포드 풀커슨 알고리즘, 최악의 경우엔 원하는 결과값을 구하기 위해 수많은 연산횟수를 거쳐야만 한다.



ex)
![image](https://user-images.githubusercontent.com/100903674/164723339-3f4f137a-09ec-4c18-9964-70be862e9496.png)



다음과 같이 그래프가 주어졌을때 A->C->D->B 로 DFS를 통해 결정했다면

![image](https://user-images.githubusercontent.com/100903674/164725998-f96fe928-1daf-45e8-b890-3a12df4218e9.png)


여유용량이 경로 A->D->C->B 로 DFS를 통해 결정했다면

![image](https://user-images.githubusercontent.com/100903674/164726432-ea764eb2-92de-4766-abbe-48e6ab1f4a61.png)



  다시 A->C->D->B 로 DFS를 통해 결정했다면

![image](https://user-images.githubusercontent.com/100903674/164727052-184d4979-4b7a-420a-8271-b6f73a231a8d.png)

다시 A->D->C->B 로 DFS를 통해 결정했다면

![image](https://user-images.githubusercontent.com/100903674/164727318-0fbddc26-a318-41ac-8295-75ddfe949da0.png)





최종적으로

![image](https://user-images.githubusercontent.com/100903674/164727696-cc7e4add-381e-498d-80bc-cce7ccddcb7f.png)
특정 그래프에 대하여 다음과 같이 만들기 위해 포드 풀커슨 알고리즘은 N이 크면 클수록 수많은 연산횟수를 거쳐야 한다.

DFS 알고리즘을 기반으로 한 포드 풀커슨 알고리즘의 약점을 보완하기 위해 추후에

BFS 알고리즘을 기반으로한 에드몬드 카프 알고리즘이 나왔다. 
위와 같은 그래프는 BFS일떄 더 효과적인데,
A->C->B를 먼저 탐색하고
![image](https://user-images.githubusercontent.com/100903674/165741916-6a30e573-1ad5-431a-85bf-eaf467468d2c.png)


A->D->B 를 탐색하면


![image](https://user-images.githubusercontent.com/100903674/165742088-d82ff3b5-b46b-416a-86d3-549b3261698b.png)



이후 여유용량이 있는 경로가 더이상 없으므로 연산 


최대 유량이 2N임을 DFS 탐색을 통해서는 연산과정의 횟수가 최대유량에 의해 영향을 받는 반면 BFS를 통해서는 최대 유량과는  두번의 과정을 통해 구해낼수 있다.

다만 최대유량이 한없이 작은 경우에는 포드 풀커슨 알고리즘이 더 효율적이다.




