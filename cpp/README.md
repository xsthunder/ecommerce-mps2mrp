# CPP solution

use c with classes

## class

### part
### question
// consist should need number.

```cpp
class WAY_TO_GET{
	static const int BUILD = 0;
	static const int BUY = 1;
	static const char WAYTOGET[2][] = {
		"生产","采购"
	}
}
//use name to identify
////make map NAME -> number using BOM
//typedef map<string, int> Name2number;
//Name2number(FILE* bom){
//	//this func depends map, string
//	//name should not exceed 100 char
//	map<int, string>name2number 
//	char name[100];
//}
```


```cpp
class MpsNode{
	//this depend ctime
	private:
		int wayToGet;
		int number;
		int string;
		int numberNeed;
		int stockTaken;
		time_t miliTimeBegin;
		time_t miliTimeEnd;
		string print(){
		}
}
class Mps{
	//FIXME use MpsNode pointer to seedup
	private:
		list <MpsNode> mps;
	public:
		insert(MpsNode mn){
			mps.push(nm);
		}
}

```


```cpp
//build from stock
typedef map<int , int> Number2stock;
void buildNumber2stock(FILE *f,Number2stock &n2s){
}
```

```cpp
// build tree from BOM(first) and consist
typedef map<string,DependTree *>NameToDependTree;
NameToDependTree nameToDependTree;
class DependTree{
	private:
		DependTree * father;
		list<*DependTree> son;
		int stock ;
	public:
		string name;//this part name
		int number;//this part number
		int wayToGet;
		int consistNumber;
		double failRate;

		//FIXME duplicated with stock, don't use them
		int stockWork;
		int stockStorage;
		
		int dateEalierToBuild;
		int dateEalierToGet;
		int dateEalierTosupplier;

		void buildTree();//build this tree
		DependTree* locate(string)//find one of its part, making possible to build its part along
		void start(DependTree *father, Mps&mps);
		
};
```


1. generate material dependencies tree by bom

2. generate raw mps without consideration of stock

