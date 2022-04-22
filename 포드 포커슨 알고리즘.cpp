#include <iostream>
#include <vector>
#include <queue>

#define MAX 100
#define INF 1000000000

using namespace std;

int n = 20;  // ���� ��
int capacity[MAX][MAX]; // �뷮 �迭
int flow[MAX][MAX]; // ���� ���� �迭
int visited[MAX]; // ���� ���� �湮 ����
int result; // �ִ� ���� ���

// �� ������ ��� �������κ��� �湮�Ǿ����� ����ϴ� �迭
vector<int> adj[MAX];

// �ִ� ���� ���
void maxFlow(int source, int sink) {

    while (1) {

        // ���� ���� �湮 ���� �迭�� -1 �� �ʱ�ȭ
        fill(visited, visited + MAX, -1);

        // queue ���� ��, source push
        queue<int> q;
        q.push(source);

        // source ���� sink �� �ִ����� �����ϴ� ��� ã��
        while (!q.empty()) {

            // queue �� front �� ��ġ�� ���� ����
            int start = q.front();
            q.pop();

            // queue �� front �� ��ġ�� ������ ������ ���� Ž��
            for (int i = 0; i < adj[start].size(); i++) {

                // ���� ����
                int end = adj[start][i];

                // ���� ������, �ܿ� �뷮�� �����ִ��� Ȯ���ϰ�, �湮���� �ʾҴ��� Ȯ��
                if (capacity[start][end] - flow[start][end] > 0 && visited[end] == -1) {
                    // ���� �������κ��� ����� ��ε��� Ȯ���ϱ� ����, ���� ������ queue �� ����
                    q.push(end);
                    // ���� ������ ��� �������κ��� ����Ǿ��ִ��� ���
                    visited[end] = start;
                    // ���� ������ �������� ���, �ϳ��� ���� ��θ� ã�����Ƿ�, �� �̻� Ž������ �ʰ� ����
                    if (end == sink) break;
                }
            }
        }

        // sink ������ ��θ� �� ã�Ҵٸ�, �� �̻��� ���� ��ΰ� ����
        if (visited[sink] == -1) break;

        // ����� ��ε��� ������������ �ݴ�� ��� Ȯ���ϸ�, �ּ� ������ Ž��
        int f = INF;
        for (int i = sink; i != source; i = visited[i]) {
            // min(�ּ�����, �뷮(�������, ������) - ����(�������, ������))
            f = min(f, capacity[visited[i]][i] - flow[visited[i]][i]);
        }

        // ���� ��δ� ���� ����, �� ���� ��δ� ���� ����
        for (int i = sink; i != source; i = visited[i]) {
            // ����(�������, ������) += f
            flow[visited[i]][i] += f;
            // ����(������, �������) -= f
            flow[i][visited[i]] -= f;
        }

        // �ִ� ���� �߰�
        result += f;
    }
}

int main() {



    adj[1].push_back(2); // ���� �߰�
    adj[2].push_back(1); // ������ �߰�
    capacity[1][2] = 4; // �뷮 �߰�

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

    

    
    maxFlow(1, 4);

    
    printf("�ִ� ���� : %d\n", result);
}