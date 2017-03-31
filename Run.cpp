#include "Run.h"


#define RED          "\033[0;32;31m"

void printClean() {
	system("cls");
	//printf("\033[2J");
}

//unsigned getHashKeyByXY(const unsigned &x, const unsigned &y) {
//	return (x + x * 10)*(y + y * 10);
//}

enum StrEnum {
	A = 'A',
	B = 'B',
	C = 'C',
	D = 'D',
	E = 'E'
};


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

void RNode::setBoolArrByIndex(const unsigned &index,bool bl) {
	this->boolArrIsCall[index] = bl;
}

bool RNode::getBoolArrByIndex(const unsigned &index) const {
	return this->boolArrIsCall[index];
}

void RNode::printColorByStr(const char c,bool isBLank) {
	this->setStrAndBalk(c, isBalk);
	this->printNodeStr();
	//if (c == 'A') {
	//	printf(RED+c);
	//}
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















creatMap::creatMap(const unsigned x, const unsigned y,const unsigned radNum):_mapX(x),_mapY(y), randomTotalNum(radNum)
{
	startIndex = 1 + _mapY;
	endIndex = (_mapY - 2) + (_mapX - 2)*_mapY;
	unsigned maxRandom=2 * _mapY + (_mapX - 2) * 2 - 2;
	if (radNum > maxRandom) {
		std::cout << "radom num big ......." << std::endl;
		return;
	}

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
			}
			else {
				if (j == 0 || j == _map[i].size() - 1) {
					(_map[i][j].setStrAndBalk)('#', true);
				}
				else {
					(_map[i][j].setStrAndBalk)(' ', false);
				}
			}
		}
		std::cout << std::endl;
	}
	this->setRadomBalk();
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

RNode &creatMap::getNodeNodeByIndex(const unsigned &index) {
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


const std::vector<RNode> creatMap::setRadomBalk() {
	std::vector<unsigned> iVec;
	for (unsigned int i = 0; i != _map.size(); ++i) {
		for (unsigned int j = 0; j != _map[i].size(); ++j) {
			if (_map[i][j].getNodeBalk())
				iVec.push_back(_map[i][j].getNodeIndex());
		}
	}
	std::cout << iVec.size() << std::endl;
	srand((unsigned int)time(0));
	unsigned int max = _mapX >= _mapY ? _mapX : _mapY;
	unsigned int index = 0;
	std::vector<RNode> resVec;
	while (true) {
		if (index == randomTotalNum) {
			break;
		}
		unsigned rdom =(rand()%(_mapX*_mapY));
		if (rdom > startIndex && rdom < endIndex) {
			bool bl = this->subSetRadomBalk(iVec, rdom);
			if (!bl) {
				RNode &rn=this->getNodeNodeByIndex(rdom);
				bl = this->subSetRadomRalkNode(resVec,rn);
				if (!bl) {
					//std::cout << rn.getNodeIndex() << std::endl;
					rn.setStrAndBalk('#',true);
					resVec.push_back(rn);
					++index;
				}
			}
		}
	}

	return resVec;

}



void creatMap::showMap() {
	printClean();
	for (unsigned i = 0; i != _map.size(); ++i) {
		for (unsigned j = 0; j != _map[i].size(); ++j) {
			_map[i][j].printNodeStr();
		}
		std::cout << std::endl;
	}

}

std::vector<std::vector<unsigned>> creatMap::findPath() {
	const unsigned _x = 1, _y = 1;
	std::deque<RNode> deq;
	const unsigned _index = 0;
	_map[_x][_y].setBoolArrByIndex(_index, true);
	deq.push_back(_map[_x][_y]);

	std::vector<std::vector<unsigned>> res = { { startIndex } };
	while (!deq.empty()) {
		const RNode &rn = deq.front();
		const unsigned x = rn.getNodeX();
		const unsigned y = rn.getNodeY();
		if (x + 1 >= _mapX || y + 1 >= _mapY)
			break;
		if (!_map[x + 1][y].getNodeBalk() && !_map[x + 1][y].getBoolArrByIndex(_index)) {
			deq.push_back(_map[x+1][y]);
			_map[x + 1][y].setBoolArrByIndex(_index, true);
			for (unsigned o = 0; o != res.size(); ++o) {
				if (res[o][res[o].size() - 1] == rn.getNodeIndex()) {
					std::vector<unsigned> iv;
					for (unsigned a = 0; a != res[o].size(); ++a) {
						iv.push_back(res[o][a]);
					}
					iv.push_back(_map[x + 1][y].getNodeIndex());
					res.push_back({ iv});
					break;
				}
			}
		}
		if (!_map[x][y+1].getNodeBalk() && !_map[x][y+1].getBoolArrByIndex(_index)) {
			deq.push_back(_map[x][y+1]);
			_map[x][y + 1].setBoolArrByIndex(_index, true);
			for (unsigned o = 0; o != res.size(); ++o) {
				if (res[o][res[o].size() - 1] == rn.getNodeIndex()) {
					std::vector<unsigned> iv;
					for (unsigned a = 0; a != res[o].size(); ++a) {
						iv.push_back(res[o][a]);
					}
					iv.push_back(_map[x][y+1].getNodeIndex());
					res.push_back({ iv });
					break;
				}
			}
		}
		deq.pop_front();
	}
	for (unsigned i = 0; i != _map.size(); ++i) {
		for (unsigned j = 0; j != _map[i].size(); ++j) {
			_map[i][j].setBoolArrByIndex(_index, false);
		}
	}
	return res;
}


std::vector<unsigned> creatMap::GoType(const unsigned type) {
	//if (type == 0) {
	//	_map[1][1].setStrAndBalk('A', true);
	//}
	//if (type == 1) {
	//	_map[1][1].setStrAndBalk('B', true);
	//}
	showMap();
	std::vector<std::vector<unsigned>> res=findPath();
	if (res.size() <= 1) {
		std::cout << "can not find path.. 1111111";
		//return;
	}

	int ai = -1;
	
	for (unsigned i = 0; i != res.size(); ++i) {
		for (unsigned j = 0; j != res[i].size(); ++j) {
			if (res[i][j] == this->endIndex) {
				ai = i;
				break;
			}
		}
	}

	if (ai <0 ) {
		std::cout << "can not find path..222222222222 ";
		//return;
	}

	return res[ai];

	//for (unsigned a = 0; a != res[ai].size(); ++a) {
	//	const unsigned index = res[ai][a];
	//	//this->getNodeNodeByIndex(index).printColorByStr('A',true);
	//	//this->showMap();
	//	//Sleep(2.5 * 1000);
	//	//this->getNodeNodeByIndex(index).setStrAndBalk(' ',false);
	//}
}

void creatMap::subGoType(unsigned index,unsigned &resultIndex) {

	std::vector<unsigned> res=this->GoType(0);
	unsigned CCindex = res[index];
	resultIndex = CCindex;
	this->getNodeNodeByIndex(CCindex).printColorByStr('A', true);
	this->showMap();
}

void creatMap::Go() {	

	std::clock_t star_tiem = clock();
	std::clock_t end_time = 0;
	double dis_time = 0.0;


	unsigned Aindex = 0;
	unsigned AresultIndex = 0;
	this->subGoType(Aindex, AresultIndex);

	unsigned Bindex = 0;
	unsigned BresultIndex = 0;


	while (true) {
		end_time = clock();
		dis_time = end_time - star_tiem;

		if (dis_time == 2 * 1000) {

			this->getNodeNodeByIndex(AresultIndex).setStrAndBalk(' ', false);
			this->subGoType(++Aindex, AresultIndex);

			dis_time = 0.0;
			star_tiem = clock();
		}

		if (dis_time == 2.5 * 1000) {
			//this->subGoType(Bindex, AresultIndex);
		}

	}

	//GoType(0);
	//for (unsigned i = 1; i != 5; ++i) {
	//	Sleep(0.5 * 1000);
	//	GoType(i);
	//	break;
	//}
}



