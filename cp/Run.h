#ifndef RUN_H
#define RUN_H

#include<vector>
#include<ctime>
#include<iostream>
#include<cstdlib>
#include<stdexcept>
#include<deque>
#include<ctime>

#include<cstdio>



class RNode {
private:
	unsigned int index;
	unsigned int RX;
	unsigned int RY;
	char str;
	bool isBalk;
	bool boolArrIsCall[10] = { false, false, false, false, false,false,false,false,false,false };
	bool isRealBalk = false;
	void setNodeStr(const char c);
	void setNOdeBalk(const bool bl);
public:
	RNode(unsigned, unsigned, unsigned, char, bool);
	void printNodeStr();
	const bool getNodeBalk() const;
	void setStrAndBalk(const char c,bool bl);
	const unsigned int getNodeIndex() const;
	const unsigned getNodeX() const;
	const unsigned getNodeY() const;
	void setBoolArrByIndex(const unsigned &index,bool bl);
	bool getBoolArrByIndex(const unsigned &index) const;
	void printColorByStr(const char c,bool);
	bool getIsRealBalk() const;
	void setIsRealRalk(bool bl);
};

bool operator==(const RNode&,const RNode&);

class _RunPoint{
private:
	std::vector<unsigned> _pathVec;
public:
	int _Index;
	int _PreIndex;
	double _beg;
	double _end;
	double _dis;
	bool _isGo;
	bool _isDone;
	double _typeTime;
	_RunPoint(int nodeIndex,int type,std::vector<unsigned> pathV){
		_pathVec = pathV;
		_Index=nodeIndex;
		_PreIndex=nodeIndex;
		_beg=clock();
		_end=clock();
		_dis=0.0;
		_isGo=false;
		_isDone = false;
		_typeTime=(2.5-(type/2))*1000;
	}
	bool initRP(){
		_end=clock();
		_dis=_end-_beg;
		if(_dis>=_typeTime){
			_end=_beg=clock();
			_dis=0.0;
			return true;
		}
		return false;
	}
};

class creatMap {
private:
	unsigned startIndex;
	unsigned endIndex;
	const unsigned _mapX;
	const unsigned _mapY;
	std::vector<std::vector<RNode>> _map;
	const unsigned randomTotalNum;
	const bool subSetRadomBalk(const std::vector<unsigned>&,const unsigned&);
	const bool subSetRadomRalkNode(const std::vector<RNode>&, const RNode&);
	const std::vector<RNode> setRadomBalk();
	std::vector<std::vector<unsigned>> findPath(const unsigned, const unsigned);
public:
	creatMap(const unsigned,const unsigned,const unsigned);
	int GoType(const unsigned, const int);
	RNode &getNodeNodeByIndex(const unsigned&);


	void showMap();
	void Go();
};



#endif // !ONE_H
