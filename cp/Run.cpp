#include "Run.h"


#define RED          "\033[0;32;31m"

void printClean() {
	system("cls");
}


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
	this->str = c;
	//this->setIsRealRalk(isBLank);
	this->isBalk = isBLank;
}

bool RNode::getIsRealBalk() const {
	return this->isRealBalk;
}

void RNode::setIsRealRalk(bool bl) {
	this->isRealBalk = bl;
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

std::vector<unsigned> creatMap::findPath(const unsigned _index, const unsigned nodeIndex,bool isReFind) {
	RNode rnn=this->getNodeNodeByIndex(nodeIndex);
	const unsigned _x = rnn.getNodeX(), _y = rnn.getNodeY();
	std::deque<RNode> deq;
	_map[_x][_y].setBoolArrByIndex(_index, true);
	deq.push_back(_map[_x][_y]);
	std::vector<std::vector<unsigned>> res = { { deq.front().getNodeIndex() } };


	if (isReFind) {

	}
	else {

	}

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

		if (!_map[x-1][y].getNodeBalk() && !_map[x-1][y].getBoolArrByIndex(_index)) {
			deq.push_back(_map[x-1][y]);
			_map[x-1][y].setBoolArrByIndex(_index, true);
			for (unsigned o = 0; o != res.size(); ++o) {
				if (res[o][res[o].size() - 1] == rn.getNodeIndex()) {
					std::vector<unsigned> iv;
					for (unsigned a = 0; a != res[o].size(); ++a) {
						iv.push_back(res[o][a]);
					}
					iv.push_back(_map[x-1][y].getNodeIndex());
					res.push_back({ iv });
					break;
				}
			}
		}


		if (!_map[x][y-1].getNodeBalk() && !_map[x][y-1].getBoolArrByIndex(_index)) {
			deq.push_back(_map[x][y-1]);
			_map[x][y-1].setBoolArrByIndex(_index, true);
			for (unsigned o = 0; o != res.size(); ++o) {
				if (res[o][res[o].size() - 1] == rn.getNodeIndex()) {
					std::vector<unsigned> iv;
					for (unsigned a = 0; a != res[o].size(); ++a) {
						iv.push_back(res[o][a]);
					}
					iv.push_back(_map[x][y-1].getNodeIndex());
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







	int ai = -1;

	for (unsigned i = 0; i != res.size(); ++i) {
		for (unsigned j = 0; j != res[i].size(); ++j) {
			if (_index >= 5) {
				if (res[i][j] == this->startIndex) {
					ai = i;
					break;
				}
			}
			else {
				if (res[i][j] == this->endIndex) {
					ai = i;
					break;
				}
			}

		}
	}

	if (ai <0) {
		std::cout << "can not find path..222222222222 ";
		std::vector<unsigned> cres;
		return cres;
	}

	return res[ai];
}


int creatMap::GoType(const unsigned type,const int nodeIndex) {
	//char c = ' ';
	//if (type == 0) {
	//	c = 'A';
	//}
	//if (type == 1) {
	//	c = 'B';
	//}
	//if (type == 2) {
	//	c = 'C';
	//}
	//if (type == 3) {
	//	c = 'D';
	//}
	//if (type == 4) {
	//	c = 'E';
	//}
	//if (type == 5) {
	//	c = 'a';
	//}
	//if (type == 6) {
	//	c = 'b';
	//}
	//if (type == 7) {
	//	c = 'c';
	//}
	//if (type == 8) {
	//	c = 'd';
	//}
	//if (type == 9) {
	//	c = 'e';
	//}

	//if (type >= 5) {
	//	if (res[ai][0] == startIndex) {
	//		//done 
	//		return -20;
	//	}
	//}
	//else {
	//	if (res[ai][0] == endIndex) {
	//		//done 
	//		return -20;
	//	}
	//}


	//const unsigned index = res[ai][1];
	//this->getNodeNodeByIndex(index).printColorByStr(c, true);
	//if (type == 0) {
	//	preAinde = index;
	//}
	//if (type == 1) {
	//	prerBinde = index;
	//}
	//if (type == 2) {
	//	preCinde = index;
	//}
	//if (type == 3) {
	//	preDinde = index;
	//}
	//if (type == 4) {
	//	preEinde = index;
	//}
	//if (type == 5) {
	//	preainde = index;
	//}
	//if (type == 6) {
	//	prebinde = index;
	//}
	//if (type == 7) {
	//	precinde = index;
	//}
	//if (type == 8) {
	//	predinde = index;
	//}
	//if (type == 9) {
	//	preeinde = index;
	//}
	//return index;
	return 0;
}



void creatMap::Go() {

	const std::vector<unsigned> leftres = this->findPath(0, startIndex);
	const std::vector<unsigned> rightres = this->findPath(5, endIndex);

	if (leftres.size() == 0 || rightres.size() == 0) {
		std::cout << "can not find path..." << std::endl;
		return;
	}


	this->getNodeNodeByIndex(startIndex).printColorByStr('A',false);
	//this->getNodeNodeByIndex(endIndex).printColorByStr('a', false);
	this->showMap();



	//A
	_RunPoint Arp(startIndex,0,leftres,this);

	//B
	_RunPoint Brp(startIndex,1, leftres, this);

	//C
	_RunPoint Crp(startIndex,2, leftres, this);

	//D
	_RunPoint Drp(startIndex,3, leftres, this);

	//E
	_RunPoint Erp(startIndex,4, leftres, this);
	 

	while (true) {

		Arp._end = clock();
		Arp._dis = Arp._end - Arp._beg;
		if (Arp._dis >= 3.0 * 1000 && !Arp._isDone) {
			this->getNodeNodeByIndex(Arp._PreIndex).setStrAndBalk(' ', false);
			Arp._Index = Arp.rpGoType();
			if (Arp._Index == -10) {
				if (!Arp._isGo) {
					std::cout << "AIndex == -10 " << std::endl;
					return;
				}
				else {
					this->getNodeNodeByIndex(Arp._PreIndex).setStrAndBalk('A', true);
					Arp._Index = Arp._PreIndex;
				}
			}
			if (Arp._Index == -20) {
				this->getNodeNodeByIndex(Arp._PreIndex).setStrAndBalk('A', false);
				Arp._isDone = true;
			}

			Arp._isGo = true;
			this->showMap();
			Arp._beg = Arp._end = clock();
			Arp._end = 0.0;
		}

		Brp._end = clock();
		Brp._dis = Brp._end - Brp._beg;
		if (Brp._dis >= 2.5 * 1000&&!Brp._isDone) {
			if (Arp._isGo) {
				if (!Brp._isGo) {
					_map[1][1].printColorByStr('B', false);
				}
				else {
					this->getNodeNodeByIndex(Brp._PreIndex).setStrAndBalk(' ', false);
					Brp._Index = Brp.rpGoType();
					if (Brp._Index == -10) {
						this->getNodeNodeByIndex(Brp._PreIndex).setStrAndBalk('B', true);
						Brp._Index = Brp._PreIndex;
					}
					if (Brp._Index == -20) {
						this->getNodeNodeByIndex(Brp._PreIndex).setStrAndBalk('B', false);
						Brp._isDone = true;
					}
					if (Brp._Index == -30) {
						std::vector<unsigned> tempB=this->findPath(Brp._type, Brp._PreIndex);
						if (tempB.size() == 0) {
							this->getNodeNodeByIndex(Brp._PreIndex).setStrAndBalk('B', true);
							Brp._Index = Brp._PreIndex;
						}
						else {
							Brp.rpGo(tempB);
							Brp._Index = Brp.rpGoType();
						}
					}
				}
				Brp._isGo = true;
				this->showMap();
			}
			Brp._beg = Brp._end = clock();
			Brp._dis = 0.0;
		}

		Crp._end = clock();
		Crp._dis = Crp._end - Crp._beg;
		if (Crp._dis >= 2.0 * 1000 && !Crp._isDone) {
			if (Arp._isGo&&Brp._isGo&&Brp._Index>startIndex) {
				if (!Crp._isGo) {
					_map[1][1].printColorByStr('C', false);
				}
				else {
					this->getNodeNodeByIndex(Crp._PreIndex).setStrAndBalk(' ', false);
					Crp._Index = Crp.rpGoType();
					if (Crp._Index == -10) {
						this->getNodeNodeByIndex(Crp._PreIndex).setStrAndBalk('C', true);
						Crp._Index = Crp._PreIndex;
					}
					if (Crp._Index == -20) {
						this->getNodeNodeByIndex(Crp._PreIndex).setStrAndBalk('C', false);
						Crp._isDone = true;
					}
					if (Crp._Index == -30) {
						std::vector<unsigned> tempC = this->findPath(Crp._type, Crp._PreIndex);
						if (tempC.size() == 0) {
							this->getNodeNodeByIndex(Crp._PreIndex).setStrAndBalk('C', true);
							Crp._Index = Crp._PreIndex;
						}
						else {
							Crp.rpGo(tempC);
							Crp._Index = Crp.rpGoType();
						}
					}
				}
				Crp._isGo = true;
				this->showMap();
			}
			Crp._end = Crp._beg = clock();
			Crp._dis = 0.0;
		}

		//Dend = clock();
		//disD = Dend - Dbeg;
		//if (disD >= 1.5 * 1000 &&!DisDone) {
		//	if (AisGo&&BisGo&&CisGo&&Cindex > startIndex) {
		//		if (!DisGo) {
		//			_map[1][1].printColorByStr('D', false);
		//		}
		//		else {
		//			this->getNodeNodeByIndex(preDinde).setStrAndBalk(' ', false);
		//			Dindex = this->GoType(3, Dindex);
		//			if (Dindex == -10) {
		//				this->getNodeNodeByIndex(preDinde).setStrAndBalk('D', true);
		//				Dindex = preDinde;
		//			}
		//			if (Dindex == -20) {
		//				this->getNodeNodeByIndex(preDinde).setStrAndBalk('D', false);
		//				DisDone = true;
		//			}
		//		}
		//		DisGo = true;
		//		this->showMap();
		//	}
		//	Dend = Dbeg = clock();
		//	disD = 0.0;
		//}


		//Eend = clock();
		//disE = Eend - Ebeg;
		//if (disE >= 1.0 * 1000  &&!EisDone) {
		//	if (AisGo&&BisGo&&CisGo&&DisGo&&Dindex > startIndex) {
		//		if (!EisGo) {
		//			_map[1][1].printColorByStr('E', false);
		//		}
		//		else {
		//			this->getNodeNodeByIndex(preEinde).setStrAndBalk(' ', false);
		//			Eindex = this->GoType(4, Eindex);
		//			if (Eindex == -10) {
		//				this->getNodeNodeByIndex(preEinde).setStrAndBalk('E', true);
		//				Eindex = preEinde;
		//			}
		//			if (Eindex == -20) {
		//				this->getNodeNodeByIndex(preEinde).setStrAndBalk('E', false);
		//				EisDone = true;
		//			}
		//		}
		//		EisGo = true;
		//		this->showMap();
		//	}
		//	Eend = Ebeg = clock();
		//	disE = 0.0;
		//}




		//if (AisDone&&BisDone&&CisDone&&DisDone&&EisDone) {
		//	std::cout << "all done " << std::endl;
		//	return;
		//}


	}
}

int _RunPoint::rpGoType() {
	char c = ' ';
	if (_type == 0) {
		c = 'A';
	}
	if (_type == 1) {
		c = 'B';
	}
	if (_type == 2) {
		c = 'C';
	}
	if (_type == 3) {
		c = 'D';
	}
	if (_type == 4) {
		c = 'E';
	}
	if (_type == 5) {
		c = 'a';
	}
	if (_type == 6) {
		c = 'b';
	}
	if (_type == 7) {
		c = 'c';
	}
	if (_type == 8) {
		c = 'd';
	}
	if (_type == 9) {
		c = 'e';
	}

	if (_type >= 5) {
		if (_pathVec[0] == _cmap->startIndex) {
			//done 
			return -20;
		}
	}
	else {
		if (_pathVec[0] == (_cmap->endIndex)) {
			//done 
			return -20;
		}
	}

	const unsigned index = _pathVec[1];
	if (_cmap->getNodeNodeByIndex(index).getNodeBalk()) {
		
		return -30;
	}
	else {
		(_cmap->getNodeNodeByIndex(index)).printColorByStr(c, true);
		_pathVec.erase(_pathVec.begin());
		this->_PreIndex = index;
		return index;
	}

}
