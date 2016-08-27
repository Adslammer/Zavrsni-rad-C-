#include<iostream>
#include<fstream>
#include<windows.h>
#include<math.h>
#include<string>

using namespace std;

#define MAXINT (int)((pow(2,31)-1)/2-1)
#define MAX 100

unsigned int matrica[MAX][MAX];

struct cvor {
    unsigned udaljenost[MAX];
    unsigned preko[MAX];
} usmjeritelj[MAX];

void izracunaj_sljedeci_cvor (int n) {
    int i,j,k,br;
    do {
        br=0;
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                for(k=0;k<n;k++)
                    if(usmjeritelj[i].udaljenost[j]>matrica[i][k]+usmjeritelj[k].udaljenost[j]) {
                        usmjeritelj[i].udaljenost[j]=matrica[i][k]+usmjeritelj[k].udaljenost[j];
                        usmjeritelj[i].preko[j]=k;
                        br++;
                    }
    } while (br!=0);
}

void algoritam (int i,int o,int n,string str) {
    int j,k,suma=0,br=0;
    ofstream izlaz ("rezultati.txt");
    izlaz << "Put kroz mrezu od izvora do odredista za " << str << " nacin rada je:" << endl;
    izlaz << i << " ";
    while (i!=o) {
        br++;
        if (str=="DIN" && br==1) {
            for (j=0;j<n;j++)
                for (k=0;k<n;k++)
                    if (j!=k) {
                        usmjeritelj[i].udaljenost[j]=matrica[i][j];
                        usmjeritelj[i].preko[j]=j;
                        if ((j==6 || k==6) && matrica[j][k]<20) {
                            matrica[j][k]+=3;
                            usmjeritelj[i].udaljenost[j]=matrica[i][j];
                        }
                        if ((j==3 || k==3) && matrica[j][k]>2 && matrica[j][k]<20) {
                            matrica[j][k]-=2;
                            usmjeritelj[i].udaljenost[j]=matrica[i][j];
                        }
                        else if ((j==3 || k==3) && matrica[j][k]==2) {
                            matrica[j][k]-=1;
                            usmjeritelj[i].udaljenost[j]=matrica[i][j];
                        }
                    }
        }
        if (str=="NEW" && br==1) {
            for (j=0;j<n;j++)
                if (j==3) {
                    usmjeritelj[j].udaljenost[10]=matrica[j][10]=1;
                    usmjeritelj[j].preko[10]=10;
                    usmjeritelj[10].udaljenost[j]=matrica[10][j]=1;
                    usmjeritelj[10].preko[j]=j;
                }
                else if (j==6) {
                    usmjeritelj[j].udaljenost[10]=matrica[j][10]=2;
                    usmjeritelj[j].preko[10]=10;
                    usmjeritelj[10].udaljenost[j]=matrica[10][j]=2;
                    usmjeritelj[10].preko[j]=j;
                }
                else if (j==7) {
                    usmjeritelj[j].udaljenost[10]=matrica[j][10]=2;
                    usmjeritelj[j].preko[10]=10;
                    usmjeritelj[10].udaljenost[j]=matrica[10][j]=2;
                    usmjeritelj[10].preko[j]=j;
                }
                else if (j==10) {
                    usmjeritelj[j].udaljenost[10]=matrica[j][10]=0;
                    usmjeritelj[10].preko[j]=j;
                }
                else {
                    usmjeritelj[j].udaljenost[10]=matrica[j][10]=MAXINT;
                    usmjeritelj[j].preko[10]=10;
                    usmjeritelj[10].udaljenost[j]=matrica[10][j]=MAXINT;
                    usmjeritelj[10].preko[j]=j;
                }
            n++;
        }
        if (str=="DEL" && br==1)
            for (j=0;j<n;j++) {
                usmjeritelj[j].udaljenost[6]=matrica[j][6]=usmjeritelj[6].udaljenost[j]=matrica[6][j]=MAXINT;
                usmjeritelj[6].preko[j]=usmjeritelj[j].preko[6]=6;
            }
        izracunaj_sljedeci_cvor (n);
        j=usmjeritelj[i].preko[o];
        suma+=usmjeritelj[i].udaljenost[j];
        i=j;
        izlaz << i << " ";
    }
    izlaz << endl << "Udaljenost do odredista je " << suma << endl;
}

int main() {
    int a,b,c,n,i,j,izvor,odrediste,br;
    string str;
	SYSTEMTIME vrijeme1, vrijeme2;
	WORD trajanjems;

    for (i=0;i<MAX;i++)
        for (j=0;j<MAX;j++) {
            usmjeritelj[i].udaljenost[j]=MAXINT;
            usmjeritelj[i].preko[j]=j;
        }
    memset(matrica, MAXINT, sizeof(matrica));
    ifstream ulaz ("primjer2.txt"); //probati i primjer.txt i primjer2.txt
    ulaz >> n >> br;
    for (i=0;i<n;i++) {
        matrica[i][i]=0;
        usmjeritelj[i].udaljenost[i]=0;
        usmjeritelj[i].preko[i]=i;
    }
    for (i=0;i<br;i++) {
        ulaz >> a >> b >> c;
        matrica[a][b] = c;
        usmjeritelj[a].udaljenost[b]=c;
        usmjeritelj[a].preko[b]=b;
    }
    cout << "Unesite izvor i odrediste: ";
    cin >> izvor >> odrediste;
    cout << "Unesite STAT za staticku mrezu, DIN za dinamicku, \nNEW za novi cvor u mrezi ili DEL za ispadanje jednog cvora iz mreze: ";
    cin >> str;

	GetSystemTime(&vrijeme1);

    algoritam(izvor,odrediste,n,str);

	GetSystemTime(&vrijeme2);
	trajanjems = 1000 * (vrijeme2.wSecond - vrijeme1.wSecond) +
                 vrijeme2.wMilliseconds - vrijeme1.wMilliseconds;
    cout << "trajanje algoritma: " << trajanjems << "ms" << endl;
    return 0;
}
