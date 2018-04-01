#include<cassert>
#include<algorithm>
#include<vector>
#include<list>
#include<cstdio>
#include<string>
#include<map>
#include<ctime>
#include<cstring>
using namespace std;
typedef int ItemNo ;
const int BUF_SIZE = 20;
const int SECOND_PER_DAY = 60*60*24;
void printTime(time_t t){
	struct tm * timeinfo ;
	timeinfo = localtime(&t);
	printf(" %d/%d/%d ",timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday);
}
void eatTitle(const int D,FILE *p){for(int i =0 ;i<D;i++)fscanf(p, "%*s");}
/*
 * ITEM 
 */
class ItemInfo{
	public :
		string name = "";
		ItemNo itemNo= 0;
		string wayToGet = "";
		int consistNumber = 0;//number to take to consist father using this part}
		double failRate = 0;
		int stockWork = 0;
		int stockStoage = 0;
		int stock = 0;
		int dateEalierTobuild = 0;
		int dateEalierToget = 0;
		int dateEalierTosupplier = 0;
};
map<ItemNo,ItemInfo*> infoItems;
ItemInfo *getItem(const int no){
	if( !infoItems.count(no) )infoItems[no] =new ItemInfo();
	return infoItems[no];
}
class Item{
	private :
		list<Item *> son;
	public :
		Item *father  = NULL;
		ItemNo itemNo = 0;
		void buildByConsist(FILE *);
		void buildByStock(FILE *);
		void buildByBOM(FILE *);
		void testBuild();
		void setWayToBuy(const string &);
		Item *locate(const int);
		ItemNo getNo(const string&);
		void print();
		void addMpsNode(int, time_t);
};
/*
 * ORDER
 */
class OrderNode{
	public :
		typedef unsigned long ul;
		ItemNo itemNo  = 0;
		int quantity = 0;
		int y = 0,m = 0, d = 0;
		time_t dateSecond = 0;
		void print();
		void setDate(int ,int ,int);
};
class Order{
	public :
		list<OrderNode *>table;
		void build(FILE *);
		void testBuild();
};
/*
 * MPS
 */
class MpsNode{
	public :
		ItemNo itemNo = 0;
		int quantity = 0;
		time_t dateSecondBegin;
		time_t dateSecondEnd;
		int useStockQuantity = 0;
		void printDebug();
		void print();
};
class Mps{
	public :
		string MPS_TITLE[7] = { "调配方式","物料号","物料名称","需求数量","日程下达日期	","日程完成日期	","备注" };
		void print();
		void build();
		void useStock();
		list<MpsNode*> table;
};
Item *items = new Item();
Order * order = new Order();
Mps *mps = new Mps();
/*
 * ORDER function
 */
void Order::build(FILE *p){
	const int D = 3;char charname[20];
	for(int i =0;i<D;i++)fscanf(p,"%s",charname);
	int quantity,y,m,d;
	while( EOF!= fscanf(p,"%s%d%d/%d/%d", charname, &quantity,&y,&m,&d )){
		OrderNode *on =  new OrderNode();
		on->quantity = quantity;
		on->itemNo = items->getNo(string(charname));
		on->y = y, on-> m = m, on->d = d;
		on->setDate(y,m,d);
		this->table.push_back(on);
	}
}
void OrderNode::setDate(int y,int m,int d){
	this->y = y,this->m = m, this-> d = d;
	struct tm *timeinfo;
	time_t t;
	time( &t);
	timeinfo=localtime(&t);
	timeinfo->tm_year = y - 1900;
	timeinfo->tm_mon = m - 1;
	timeinfo->tm_mday = d;
	this->dateSecond = mktime(timeinfo);
}
void OrderNode::print(){
	struct tm * timeinfo;
	timeinfo = localtime(&dateSecond);
	printf("%s %d %d/%d/%d time_t %lu %s",
			getItem(this->itemNo)->name.c_str(), quantity,
			y,m,d,
			dateSecond , asctime(timeinfo));
}
void Order::testBuild(){
	printf("Order::testBuild() table.size %lu\n",this->table.size());
	for(auto p:table)p->print();
}
/*
 * ITEM function
 */
void Item::buildByConsist(FILE * p){
	eatTitle(9,p);
	char fatherName[BUF_SIZE], name[BUF_SIZE];
	ItemNo fatherNo, itemNo;
	int consistNumber, dateEalierToget, dateEalierTosupplier;
	while(EOF !=  fscanf(p,"%*d%*s%d%s%d%s%d%d%d",
				&fatherNo, fatherName, &itemNo, name, &consistNumber, &dateEalierToget, &dateEalierTosupplier ) ){
		Item *tar = this->locate(fatherNo);
		ItemInfo *tmpInfo= getItem(itemNo);
		tmpInfo->name = string(name);
		tmpInfo->consistNumber = consistNumber;
		tmpInfo->dateEalierToget = dateEalierToget;
		tmpInfo->dateEalierTosupplier = dateEalierTosupplier;
		Item *tmp = new Item();
		tmp->itemNo = tmpInfo->itemNo = itemNo;
		if(!tar){
			ItemInfo *fa = getItem(fatherNo);
			fa->name = string(fatherName);
			fa->consistNumber = 1;
			fa->itemNo = fatherNo;
			this->itemNo = fatherNo;
			tar = this;
		}
		tar->son.push_back( tmp);
		tmp->father = tar;
	}
}
void Item::buildByStock(FILE *p){
	eatTitle(4, p);int a,sa,sb;
	while( EOF != fscanf(p,"%d%*s%d%d",&a, &sa,&sb)){
		ItemInfo * now = getItem(a);
		now->stockWork = sa;
		now->stockStoage = sb;
		now->stock = sa + sb;
	}
}
void Item::buildByBOM(FILE *p){
	eatTitle(6,p);int itemNo,dateEalierTobuild;
	char cwayToGet[BUF_SIZE];
	double failRate;
	while( EOF != fscanf(p, "%d%*s%*s%s%lf%d", &itemNo, cwayToGet, &failRate, &dateEalierTobuild ) ){
		ItemInfo * tmp = getItem(itemNo);
		tmp->wayToGet = string(cwayToGet);
		tmp->failRate = failRate;
		tmp->dateEalierTobuild = dateEalierTobuild; 
	}
}
Item * Item::locate(const int no){
	if( this->itemNo== no)return this;
	Item * ans;
	for(auto p:son){
		if( (ans = p->locate(no)) ) return ans;
	}
	return NULL;
}
ItemNo Item::getNo(const string &s){
	if( getItem(this->itemNo)->name== s)return this->itemNo;
	ItemNo  ans;
	for(auto p:son){
		if( (ans = p->getNo(s)) ) return ans;
	}
	return 0;
}
void Item::testBuild(){
	this->print();
	for(auto p:this->son)p->testBuild();
}
void Item::print(){
	ItemInfo * tmp = getItem(this->itemNo);
	//printf("%d ",this->father?this->father->itemNo:-1);
	printf("%s ",this->father?getItem(this->father->itemNo)->name.c_str():"NULL" );
	//printf("%d ",tmp->itemNo);
	printf("%s ",tmp->name.c_str() );
	printf("%s ",tmp->wayToGet.c_str() );
	printf("%d ",tmp->consistNumber);
	printf("%lf ",tmp->failRate);
	printf("%d ",tmp->stockWork);
	printf("%d ",tmp->stockStoage);
	printf("%d ",tmp->dateEalierTobuild);
	printf("%d ",tmp->dateEalierToget);
	printf("%d ",tmp->dateEalierTosupplier);
	putchar('\n');
}
void Item::addMpsNode(int quantity, time_t end){
	MpsNode *mn = new MpsNode();
	mn->itemNo = this->itemNo;
	mn->quantity = quantity;
	mn->dateSecondEnd = end;
	ItemInfo * itemInfo = getItem(this->itemNo);
	int day = (itemInfo ->dateEalierTobuild + itemInfo->dateEalierToget + itemInfo->dateEalierTosupplier);
	time_t begin = end - day*SECOND_PER_DAY;
	mn->dateSecondBegin = begin;
	mps->table.push_back(mn);
	for(auto x: son){
		ItemInfo *nxti = getItem(x->itemNo);
		int nxtq = nxti->consistNumber*quantity;
		nxtq = 0.5 + nxtq / (1.0 - nxti->failRate);
		x->addMpsNode(nxtq, begin);
	}
}
/*MPS function
 */
void Mps::print(){
	for(auto x:this->table)x->print();
	for(auto x:this->table)x->printDebug();
}
void MpsNode::printDebug(){
	ItemInfo * itemInfo= getItem(this->itemNo);
	printf("%d %s",itemInfo->itemNo, itemInfo->name.c_str());
	printf(" %d ",this->quantity);
	printTime( this->dateSecondBegin);
	printTime( this->dateSecondEnd);
	putchar('\n');
}
void MpsNode::print(){
}
void Mps::build(){
	for(auto on: order->table){
		Item* now ;
		assert(  (now = items->locate( on->itemNo)));
		now->addMpsNode( on->quantity , on->dateSecond);
	}
}
void Mps::useStock(){
	typedef  pair<time_t, MpsNode* > P;
	vector< P> v;
	for(auto x :this->table){
		v.push_back(P( x->dateSecondBegin, x));
	}
	sort( v.begin() ,v.end() );
	for(auto p : v){
		MpsNode*mn = p.second;
		ItemInfo * ii = getItem(mn->itemNo);
		if( !ii->stock ) continue;
		int a = min( mn->quantity, ii->stock );
		mn->quantity -= a;
		ii->stock -= a;

	}
}

int main(){
	FILE * pmps = fopen("1mps.txt", "r");
	FILE * pbom = fopen("2bom.txt", "r");
	FILE * pstock = fopen("3stock.txt", "r");              
	FILE * pconsist = fopen("4consist.txt", "r");
	FILE * poutput = fopen("5output.txt", "w+");
	assert( pmps && pbom && pstock && pconsist && poutput);
	items->buildByConsist(pconsist);
	items->buildByStock(pstock);
	items->buildByBOM(pbom);
	items->testBuild();

	order->build(pmps);
	order->testBuild();

	mps->build();
	mps->useStock();
	mps->print();
	return 0;
}
