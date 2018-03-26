#include<cassert>
#include<cstdio>
#include<string>
#include<map>
#include<ctime>
/**
1mps.txt
2bom.txt
3stock.txt
4consist.txt
5output.txt
ls.cc
main.cpp
README.md
**/
using namespace std;
typedef map<string, int> Name2stock;
void buildName2stock(FILE*, Name2stock&);
void testBuildName2stock(Name2stock &);
int main(){
	FILE * pmps = fopen("1mps.txt", "r");
	FILE * pbom = fopen("2bom.txt", "r");
	FILE * pstock = fopen("3stock.txt", "r");
	FILE * pconsist = fopen("4consist.txt", "r");
	FILE * poutput = fopen("5output.txt", "w+");
	assert( pmps && pbom && pstock && pconsist && poutput);
	char c[300];
	while(EOF != fscanf(pstock, "%s",c ) ){
			puts(c);
	}
	fclose(pmps);
	fclose(pbom);
	fclose(pstock);
	fclose(pconsist);
	fclose(poutput);
	return 0;
	Name2stock name2stock;
	buildName2stock(pstock ,name2stock);
	testBuildName2stock(name2stock);
	return 0;
}
static const int BUILD = 0;
static const int BUY = 1;
static const char WAY_TO_GET[2][10]{ "生产","采购" };
const int charN = 100;

void buildName2stock(FILE *p, Name2stock & name2stock ){
	char chartmp[charN];
	const int D = 4;
	string title[D];
	for(int i =0 ;i<D;i++){
		fscanf(p,"%s", chartmp);
		title[i] = string(chartmp);
		puts(chartmp);
	}
	//for(int i = 0;i<D;i++)puts(title[i].c_str());
	int a,sa,sb;
	while( EOF != fscanf(p,"%d%s%d%d",&a,chartmp, &sa,&sb)){
		string s(chartmp);
		name2stock[s] = sa  + sb;
	}
}
void testBuildName2stock(Name2stock &ns){
	puts("testBuildName2stock vvv");
	printf("name2stock size is %lu\n",ns.size());
	for(auto p:ns){
		printf("%s %d\n",p.first.c_str(), p.second);
	}
	puts("^^^^ testBuildName2stock ");
}

