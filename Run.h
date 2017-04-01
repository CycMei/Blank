#ifndef RUN_H
#define RUN_H

#include<vector>
#include<ctime>
#include<iostream>
#include<cstdlib>
#include<exception>
#include<deque>
#include<ctime>

#include<cstdio>

#include<Windows.h>



class RNode {
private:
	unsigned int index;
	unsigned int RX;
	unsigned int RY;
	char str;
	bool isBalk;
	bool boolArrIsCall[5] = { false, false, false, false, false };
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
};

bool operator==(const RNode&,const RNode&);

class creatMap;
class RunPoint {
public:
	int NodeIndex;
	int preNodeinde;
	double Tbeg;
	double Tend;
	double disTime;
	bool isGo;
public:
	RunPoint(int);
	void RPGo(creatMap*);
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
