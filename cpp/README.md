# CPP solution

use c with classes

## class
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
		time_t dateSecondBegin = 0;
		time_t dateSecondEnd = 0;
		int useStockQuantity = 0;
		void print();
};
const int MPS_TITLE_COUNT = 7;
class Mps{
	public :
		string MPS_TITLE[MPS_TITLE_COUNT] = {"调配方式","物料号","物料名称","需求数量","日程下达日期","日程完成日期","使用库存" };
		void print();
		void build();
		void useStock();
		list<MpsNode*> table;
};
```
