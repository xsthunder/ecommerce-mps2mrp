# CPP solution

use c with classes

## class

### part
### question
// consist should need number.

### pesudo code
```cpp
//use stock
Name2stock name2stock;
buildName2stock(pstock ,name2stock);
//testBuildName2stock(name2stock);
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

