#include<cassert>
#include<list>
#include<cstdio>
#include<string>
#include<map>
#include<ctime>
#include<cstring>
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

class DependTree{
	private :
		DependTree *father = NULL;
		list< DependTree *> son;
		int stock = 0;
	public:
		string name = "";
		int wayToGet = 0;
		int consistNumber = 0;//number to take to consist father using this part
		double failRate = 0;

		//FIXME don't use following 2 attributes
		int stockWork = 0;
		int stockStoage = 0;

		int dateEalierTobuild = 0;
		int dateEalierToget = 0;
		int dateEalierTosupplier = 0;
		void build(FILE *p);
		void testBuild();
		void setWayToBuy(const string &);
		DependTree *locate(const string &);
		void print();
};
class MpsNode{

}
class Mps{
	string title[] = {

	}
	list<MpsNode*> table;

}

int main(){
	FILE * pmps = fopen("1mps.txt", "r");
	FILE * pbom = fopen("2bom.txt", "r");
	FILE * pstock = fopen("3stock.txt", "r");
	FILE * pconsist = fopen("4consist.txt", "r");
	FILE * poutput = fopen("5output.txt", "w+");
	assert( pmps && pbom && pstock && pconsist && poutput);

	Name2stock name2stock;
	buildName2stock(pstock ,name2stock);
	testBuildName2stock(name2stock);

	DependTree *dt = new DependTree();
	dt->build(pconsist);
	dt->testBuild();

	//clean up
	fclose(pmps); fclose(pbom); fclose(pstock); fclose(pconsist); fclose(poutput);
	return 0;
}
static const int BUILD = 0;
static const int BUY = 1;
static const int WAY_TO_GET_COUNT = 2;
static const char WAY_TO_GET[WAY_TO_GET_COUNT][10] { "生产","采购" };
const int charN = 100;
void DependTree::build(FILE *p){
	const int D = 10;
	char charname[20],chartmp[20], charwayToGet[20];
	if( NULL== this->father){
		for(int i = 0;i<D;i++)assert(1 == fscanf(p, "%s", chartmp));//skip title
	}
	assert( 9 == fscanf(p,"%s%s%d%lf%d%d%d%d%d", charname, charwayToGet,&this->consistNumber, &this->failRate,
			&this->stockWork, &this->stockStoage, &this->dateEalierTobuild, 
			&this->dateEalierToget, &this->dateEalierTosupplier) || 1);
	this->name = string(charname);
	this->setWayToBuy(charwayToGet);
	if( NULL == this->father){
		while( EOF != fscanf(p, "%s", charname) ){
			string nextFatherName(charname);
			DependTree * father = this->locate( nextFatherName );
			assert(father);
			DependTree *pson = new DependTree();
			pson->father = father;
			pson->build(p);
			(this->son).push_back( pson );
		}
	}
}
void DependTree::testBuild(){
	this->print();
	for(auto p:son){
		p->testBuild();
	}
}
void DependTree::print(){
	printf("fatherName %s name %s %s %d %lf %d %d %d %d %d",this->father?this->father->name.c_str():"NULL", name.c_str(), WAY_TO_GET[wayToGet],this->consistNumber, this->failRate,
			this->stockWork, this->stockStoage, this->dateEalierTobuild, 
			this->dateEalierToget, this->dateEalierTosupplier) ;
	puts("");
}
void DependTree::setWayToBuy(const string &tmp){
	for(int i =0 ;i< WAY_TO_GET_COUNT ;i++){
		//FIX ME use binary search to speed up
		if( tmp == WAY_TO_GET[i] ){
			this->wayToGet = i;
			return ;
		}
	}
	puts(tmp.c_str());
	assert(0);
}
DependTree* DependTree::locate( const string &nxtf ){
	if( this->name == nxtf )return this;
	DependTree *ans = NULL;
	for( auto dt : son){ if((ans = dt->locate(nxtf)))return ans; }
	return NULL;
}

void buildName2stock(FILE *p, Name2stock & name2stock ){
	char chartmp[charN];
	const int D = 4;
	for(int i =0 ;i<D;i++){ assert( 1 == fscanf(p,"%s", chartmp)); }
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

