#include <iostream>
#include <vector>
#include <queue>

#define MAX 100
#define INF 1000000000

using namespace std;

int n = 20;  // 정점 수
int capacity[MAX][MAX]; // 용량 배열
int flow[MAX][MAX]; // 현재 유량 배열
int visited[MAX]; // 현재 정점 방문 여부
int result; // 최대 유량 


vector<int> adj[MAX];


void maxFlow(int source, int sink) {

    while (1) {

        // 현재 정점 방문 여부 배열을 -1 로 초기화
        fill(visited, visited + MAX, -1);

        // queue 생성 후, source push
        queue<int> q;
        q.push(source);

        // source 에서 sink 로 최단으로 도달하는 경로 찾기
        while (!q.empty()) {

            // queue 의 front 에 위치한 정점 추출
            int start = q.front();
            q.pop();

            // queue 의 front 에 위치한 정점과 인접한 정점 탐색
            for (int i = 0; i < adj[start].size(); i++) {

                // 인접 정점
                int end = adj[start][i];

                // 인접 정점이, 잔여 용량이 남아있는지 확인하고, 방문하지 않았는지 확인
                if (capacity[start][end] - flow[start][end] > 0 && visited[end] == -1) {
                    // 인접 정점으로부터 연결된 경로들을 확인하기 위해, 인접 정점을 queue 에 삽입
                    q.push(end);
                    
                    visited[end] = start;
                    // 인접 정점이 도착지일 경우, 하나의 증가 경로를 찾았으므로, 더 이상 탐색하지 않고 종료
                    if (end == sink) break;
                }
            }
        }

        // sink 까지의 경로를 못 찾았다면, 더 이상의 증가 경로가 없음
        if (visited[sink] == -1) break;

        // 연결된 경로들을 도착지점부터 반대로 모두 확인하며, 최소 유량을 탐색
        int f = INF;
        for (int i = sink; i != source; i = visited[i]) {
            // min(최소유량, 용량(이전노드, 현재노드) - 유량(이전노드, 현재노드))
            f = min(f, capacity[visited[i]][i] - flow[visited[i]][i]);
        }

        // 증가 경로는 유량 증가, 역 방향 경로는 유량 감소
        for (int i = sink; i != source; i = visited[i]) {
            // 유량(이전노드, 현재노드) += f
            flow[visited[i]][i] += f;
            // 유량(현재노드, 이전노드) -= f
            flow[i][visited[i]] -= f;
        }

        // 최대 유랑 추가
        result += f;
    }
}

int main() {



    adj[1].push_back(2); // 간선 추가
    adj[2].push_back(1); // 역간선 추가
    capacity[1][2] = 4; // 용량 추가

    adj[1].push_back(3);
    adj[3].push_back(1);
    capacity[1][3] = 12;

    adj[2].push_back(3);
    adj[3].push_back(2);
    capacity[2][3] = 4;

    adj[2].push_back(4);
    adj[4].push_back(2);
    capacity[2][4] = 8;

   
   
    adj[3].push_back(4);
    adj[4].push_back(3);
    capacity[3][4] = 4;

    

    
    maxFlow(1, 4);// 1~4인 정점을 그래프에 추가

    
    printf("최대 유량 : %d\n", result);
}
