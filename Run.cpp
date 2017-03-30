#include "Run.h"


RNode::RNode(unsigned index_, unsigned x, unsigned y, char c, bool bl) :index(index_),RX(x), RY(y), str(c), isBalk(bl) {}

void RNode::printNodeStr() {
	std::cout << this->str;
}

void RNode::setNodeStr(const char c) {
	this->str = c;
}

const bool RNode::getNodeBalk() const {
	return this->isBalk;
}

void RNode::setStrAndBalk(const char c, bool bl) {
	this->setNodeStr(c);
	this->setNOdeBalk(bl);
}

const unsigned int RNode::getNodeIndex() const {
	return this->index;
}

const unsigned RNode::getNodeX() const {
	return this->RX;
}

const unsigned RNode::getNodeY() const {
	return this->RY;
}

void RNode::setNOdeBalk(const bool bl) {
	this->isBalk = bl;
}


RNode getRN(unsigned index, unsigned x, unsigned y,char c, bool bl) {
	return RNode(index,x,y,c, bl);
}



bool operator==(const RNode &lhs, const RNode &rhs) {
	return lhs.getNodeIndex() == rhs.getNodeIndex();
}















creatMap::creatMap(unsigned int x, unsigned int y):_mapW(x),_mapH(y) {
	unsigned index = 0;
	for (unsigned i = 0; i != x; ++i) {
		_map.push_back({});
		for (unsigned j = 0; j != y; ++j) {
			_map[i].push_back(getRN(index++,i,j,' ',false));
		}
	}


	for (unsigned i = 0; i != _map.size(); ++i) {
		for (unsigned j = 0; j != _map[i].size(); ++j) {
			if (i == 0||i==_map.size()-1) {
				(_map[i][j].setStrAndBalk)('#', true);
				(_map[i][j].printNodeStr)();
			}
			else {
				if (j == 0 || j == _map[i].size() - 1) {
					(_map[i][j].setStrAndBalk)('#', true);
					(_map[i][j].printNodeStr)();
				}
				else {
					(_map[i][j].setStrAndBalk)(' ', false);
					(_map[i][j].printNodeStr)();
				}
			}
		}
		std::cout << std::endl;
	}
}


const bool creatMap::subSetRadomBalk(const std::vector<unsigned> &iVec,const unsigned &rdom) {

	for (unsigned i = 0; i != iVec.size(); ++i) {
		if (iVec[i] == rdom)
			return true;
	}
	return false;
}

const bool creatMap::subSetRadomRalkNode(const std::vector<RNode>&iVec, const RNode &value) {
	for (unsigned i = 0; i != iVec.size(); ++i) {
		if (iVec[i] == value)
			return true;
	}
	return false;
}

RNode creatMap::getNodeXYByIndex(const unsigned &index) const {
	for (unsigned int i = 0; i != _map.size(); ++i) {
		for (unsigned int j = 0; j != _map[i].size(); ++j) {
			if (_map[i][j].getNodeIndex() == index)
				return _map[i][j];
		}
	}
	std::cout << "cant not find x y" << std::endl;
	std::logic_error error("cant not find x y");
	throw error;
}


void creatMap::setRadomBalk() {
	std::vector<unsigned> iVec;
	for (unsigned int i = 0; i != _map.size(); ++i) {
		for (unsigned int j = 0; j != _map[i].size(); ++j) {
			if (_map[i][j].getNodeBalk())
				iVec.push_back(_map[i][j].getNodeIndex());
		}
	}
	std::cout << iVec.size() << std::endl;
	srand((unsigned int)time(0));
	unsigned int max = _mapW >= _mapH ? _mapW : _mapH;
	unsigned int index = 0;
	std::vector<RNode> resVec;
	while (true) {
		if (index == randomTotalNum) {
			break;
		}
		unsigned rdom =(rand()%(_mapW*_mapH));
		if (rdom > iVec[0] && rdom < iVec[iVec.size() - 1]) {
			bool bl = this->subSetRadomBalk(iVec, rdom);
			if (!bl) {
				RNode rn=this->getNodeXYByIndex(rdom);
				bl = this->subSetRadomRalkNode(resVec,rn);
				if (!bl) {
					std::cout << rn.getNodeIndex() << std::endl;
					resVec.push_back(rn);
					++index;
				}
			}
		}
	}

}


