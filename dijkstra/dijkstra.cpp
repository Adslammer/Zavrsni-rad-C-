#include<queue>
#include<iostream>
#include<fstream>
#include<math.h>
#include<windows.h>
#include<list>

using namespace std;

#define MAXINT (int)(pow(2,31)-1)
#define MAX 100

int matrica[MAX][MAX];
int n;
int udaljenost[MAX];
int otac[MAX];
bool obilazak[MAX];

void dijkstra(int izvor){
  priority_queue<pair<int,int> > queue;
  pair <int,int> cvor;
  int i, j;

  for (i=0;i<n;i++) {
    udaljenost[i] = MAXINT;
    otac[i] = -1;
    obilazak[i] = false;
  }
  udaljenost[izvor] = 0;
  queue.push(pair <int,int> (udaljenost[izvor], izvor));

  while(!queue.empty()) {
    while (!queue.empty()) {
        cvor = queue.top();
        queue.pop();
    }
    i = cvor.second;
    if (!obilazak[i]) {
      obilazak[i] = true;
      for (j=0;j<n;j++)
        if (!obilazak[j] && matrica[i][j] > 0 && udaljenost[i] + matrica[i][j] < udaljenost[j]) {
          udaljenost[j] = udaljenost[i] + matrica[i][j];
          otac[j] = i;
          queue.push(pair <int,int>(udaljenost[j], j));
        }
    }
  }
}

void getPath(int odrediste) {
  ofstream izlaz ("rezultati.txt");
  izlaz << "Udaljenost do odredista je " << udaljenost[odrediste] << endl;
  izlaz << "Put kroz mrezu od izvora do odredista je:" << endl;
  list<int> lista;
  lista.push_front(odrediste);
  while (otac[odrediste]!= -1) {
      lista.push_front(otac[odrediste]);
      odrediste = otac[odrediste];
  }
  list<int>::iterator it;
  for (it = lista.begin(); it != lista.end(); it++) {
      izlaz << *it << " ";
  }
  izlaz << endl;
}

int main(){
   int i,o,a, b, c, br;
   SYSTEMTIME vrijeme1, vrijeme2;
   WORD trajanjems;
   ifstream ulaz ("primjer2.txt"); //probati i primjer.txt i primjer2.txt
   memset(matrica, 0, sizeof(matrica));
   ulaz >> n >> br;
   for (int i=0; i<br; i++) {
     ulaz >> a >> b >> c;
     matrica[a][b] = c;
   }
   for (int i=0;i<n;i++) {
      for (int j=0;j<n;j++)
         printf("%d ", matrica[i][j]);
      printf("\n");
   }
   printf("\n");
   cout << "unesite izvor i odrediste: ";
   cin >> i >> o;
   GetSystemTime(&vrijeme1);
   dijkstra(i);
   getPath(o);
   GetSystemTime(&vrijeme2);
   trajanjems = 1000 * (vrijeme2.wSecond - vrijeme1.wSecond) +
                vrijeme2.wMilliseconds - vrijeme1.wMilliseconds;
   cout << "trajanje algoritma: " << trajanjems << "ms" << endl;
   return 0;
}
