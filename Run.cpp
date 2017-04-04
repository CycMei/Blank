#include "Run.h"


#define RED          "\033[0;32;31m"

void printClean() {
	system("cls");
	//printf("\033[2J");
}

void MMSleep(double times) {
	Sleep(times);
}

//unsigned getHashKeyByXY(const unsigned &x, const unsigned &y) {
//	return (x + x * 10)*(y + y * 10);
//}



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
	this->setStrAndBalk(c, isBLank);
	//this->printNodeStr();
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

std::vector<std::vector<unsigned>> creatMap::findPath(const unsigned _index, const unsigned nodeIndex) {
	RNode rnn=this->getNodeNodeByIndex(nodeIndex);


	const unsigned _x = rnn.getNodeX(), _y = rnn.getNodeY();
	std::deque<RNode> deq;
	_map[_x][_y].setBoolArrByIndex(_index, true);
	deq.push_back(_map[_x][_y]);

	std::vector<std::vector<unsigned>> res = { { deq.front().getNodeIndex() } };
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

		deq.pop_front();
	}
	for (unsigned i = 0; i != _map.size(); ++i) {
		for (unsigned j = 0; j != _map[i].size(); ++j) {
			_map[i][j].setBoolArrByIndex(_index, false);
		}
	}
	return res;
}


int preAinde = 0;
int prerBinde = 0;
int preCinde = 0;
int preDinde = 0;
int preEinde = 0;

int creatMap::GoType(const unsigned type,const int nodeIndex) {
	const std::vector<std::vector<unsigned>> res=findPath(type, nodeIndex);
	if (res.size() == 0) {
		std::cout << "can not find path.. 1111111";
		return -1;
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
		return -10;
	}

	char c = ' ';
	if (type == 0) {
		c = 'A';
	}
	if (type == 1) {
		c = 'B';
	}
	if (type == 2) {
		c = 'C';
	}
	if (type == 3) {
		c = 'D';
	}
	if (type == 4) {
		c = 'E';
	}

	if (res[ai][0] == endIndex) {
		return -2;
	}

	const unsigned index = res[ai][1];
	this->getNodeNodeByIndex(index).printColorByStr(c, true);
	if (type == 0) {
		preAinde = index;
	}
	if (type == 1) {
		prerBinde = index;
	}
	if (type == 2) {
		preCinde = index;
	}
	if (type == 3) {
		preDinde = index;
	}
	if (type == 4) {
		preEinde = index;
	}
	return index;
}



void creatMap::Go() {

	_map[1][1].printColorByStr('A', true);
	this->showMap();

	class _RunPoint{
	public:
		int _Index;
		int _PreIndex;
		double _beg;
		double _end;
		double _dis;
		bool _isGo;
		double _typeTime;
		_RunPoint(int nodeIndex,int type){
			_Index=nodeIndex;
			_PreIndex=nodeIndex;
			_beg=clock();
			_end=clock();
			_dis=0.0;
			_isGo=false;
			_typeTime=(2.5-(type/2))*1000;
		}
		void initRP(){
			_end=clock();
			_dis=_end-_beg;
			if(_dis>=_typeTime){
				_end=_beg=clock();
				_dis=0.0;
			}
		}
	}

	//A
	_RunPoint Arp(startIndex);
	// int AIndex = startIndex;
	// preAinde = AIndex;
	// double Abeg = clock();
	// double Aend = clock();
	// double disA = 0.0;
	// bool AisGo = false;

	//B
	_RunPoint Brp(startIndex);
	// int BIndex = startIndex;
	// prerBinde = startIndex;
	// double Bbeg = clock();
	// double Bend = clock();
	// double disB = 0.0;
	// bool BisGo = false;

	//C
	_RunPoint Crp(startIndex);
	// int Cindex = startIndex;
	// preCinde = startIndex;
	// double Cbeg = clock();
	// double Cend = clock();
	// double disC = 0.0;
	// bool CisGo = false;

	//D
	_RunPoint Drp(startIndex);
	// int Dindex = startIndex;
	// preDinde = startIndex;
	// double Dbeg = clock();
	// double Dend = clock();
	// double disD = 0.0;
	// bool DisGo = false;

	//E
	_RunPoint Epr(startIndex);
	// int Eindex = startIndex;
	// preEinde = startIndex;
	// double Ebeg = clock();
	// double Eend = clock();
	// double disE = 0.0;
	// bool EisGo = false;

	while (true) {

		Aend = clock();
		disA = Aend - Abeg;
		if (disA >= 3.0 * 1000) {
			AisGo = true;
			this->getNodeNodeByIndex(preAinde).setStrAndBalk(' ', false);
			AIndex = this->GoType(0, AIndex);
			this->showMap();
			Abeg = Aend = clock();
			disA = 0.0;
		}


		Bend = clock();
		disB = Bend - Bbeg;
		if (disB >= 2.5 * 1000) {
			if (AisGo) {
				if (!BisGo) {
					_map[1][1].printColorByStr('B', true);
				}
				else {
					this->getNodeNodeByIndex(prerBinde).setStrAndBalk(' ', false);
					BIndex = this->GoType(1, BIndex);
				}
				BisGo = true;
				this->showMap();
			}
			Bend = Bbeg = clock();
			disB = 0.0;
		}

		Cend = clock();
		disC = Cend - Cbeg;
		if (disC >= 2.0 * 1000) {
			if (AisGo&&BisGo&&BIndex>startIndex) {
				if (!CisGo) {
					_map[1][1].printColorByStr('C', true);
				}
				else {
					this->getNodeNodeByIndex(preCinde).setStrAndBalk(' ', false);
					Cindex = this->GoType(2, Cindex);
				}
				CisGo = true;
				this->showMap();
			}
			Cend = Cbeg = clock();
			disC = 0.0;
		}

		Dend = clock();
		disD = Dend - Dbeg;
		if (disD >= 1.5 * 1000) {
			if (AisGo&&BisGo&&CisGo&&Cindex > startIndex) {
				if (!DisGo) {
					_map[1][1].printColorByStr('D', true);
				}
				else {
					this->getNodeNodeByIndex(preDinde).setStrAndBalk(' ', false);
					Dindex = this->GoType(3, Dindex);
				}
				DisGo = true;
				this->showMap();
			}
			Dend = Dbeg = clock();
			disD = 0.0;
		}


		Eend = clock();
		disE = Eend - Ebeg;
		if (disE >= 1.0 * 1000) {
			if (AisGo&&BisGo&&CisGo&&DisGo&&Dindex > startIndex) {
				if (!EisGo) {
					_map[1][1].printColorByStr('E', true);
				}
				else {
					this->getNodeNodeByIndex(preEinde).setStrAndBalk(' ', false);
					Eindex = this->GoType(4, Eindex);
				}
				EisGo = true;
				this->showMap();
			}

			Eend = Ebeg = clock();
			disE = 0.0;
		}


	}

	




	//bool BisDone = false;

	//while (true) {

	//	MMSleep(1.0 * 1000);
	//	if (!BisDone) {
	//		this->getNodeNodeByIndex(prerBinde).setStrAndBalk(' ', false);
	//		BIndex = this->GoType(1, BIndex);
	//		if (BIndex == -2) {
	//			BisDone = true;
	//			this->getNodeNodeByIndex(prerBinde).setStrAndBalk('B', false);
	//		}
	//		else {
	//			int tempBIndex = BIndex;
	//			if (BIndex < 0 && AIndex>0) {
	//				tempBIndex = tempBIndex;
	//				this->getNodeNodeByIndex(prerBinde).setStrAndBalk('B', true);
	//			}
	//			if (BIndex < 0) {
	//				std::cout << "bbb  < 0  " << std::endl;
	//				return;
	//			}
	//		}
	//		this->showMap();
	//	}

	//	this->getNodeNodeByIndex(preAinde).setStrAndBalk(' ', false);
	//	MMSleep(0.5 * 1000);
	//	int tempAIndex = AIndex;
	//	AIndex = this->GoType(0, AIndex);
	//	if (AIndex == -2) {
	//		return;
	//	}
	//	if (AIndex < 0 && BIndex>0) {
	//		AIndex = tempAIndex;
	//		this->getNodeNodeByIndex(preAinde).setStrAndBalk('A', true);
	//		continue;
	//	}
	//	this->showMap();
	//}
}






RunPoint::RunPoint(int node) {
	this->NodeIndex = node;
	this->preNodeinde = node;
	this->Tbeg = clock();
	this->Tend = clock();
	this->disTime = 0.0;
	this->isGo = false;
}

void RunPoint::RPGo(creatMap *mthis) {
	//Tend = clock();
	//disTime = Tend - Tend;
	//if (disTime >= 2.0 * 1000) {
	//	if (AisGo) {
	//		if (!BisGo) {
	//			_map[1][1].printColorByStr('B', true);
	//		}
	//		else {
	//			mthis->getNodeNodeByIndex(preNodeinde).setStrAndBalk(' ', false);
	//			NodeIndex = mthis->GoType(1, NodeIndex);
	//		}
	//		isGo = true;
	//		mthis->showMap();
	//	}
	//	Tend = Tend = clock();
	//	disTime = 0.0;
	//}
}
