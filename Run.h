#ifndef RUN_H
#define RUN_H

#include<vector>
#include<ctime>
#include<iostream>
#include<cstdlib>
#include<exception>



class RNode {
private:
	unsigned int index;
	unsigned int RX;
	unsigned int RY;
	char str;
	bool isBalk;
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
};

bool operator==(const RNode&,const RNode&);


class creatMap {
private:
	unsigned int _mapW;
	unsigned int _mapH;
	std::vector<std::vector<RNode>> _map;
	unsigned int randomTotalNum = 8;
	const bool subSetRadomBalk(const std::vector<unsigned>&,const unsigned&);
	const bool subSetRadomRalkNode(const std::vector<RNode>&, const RNode&);
	RNode getNodeXYByIndex(const unsigned&) const;
	void setRadomBalk();
public:
	creatMap(unsigned int,unsigned int);
};

class Run {

};

#endif // !ONE_H
