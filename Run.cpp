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
	this->setStrAndBalk(c, isBLank);
	//this->printNodeStr();
	//if (c == 'A') {
	//	printf(RED+c);
	//}
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

std::vector<unsigned> creatMap::findPath(const unsigned _index, const unsigned nodeIndex) {
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


int preAinde = 0;
int prerBinde = 0;
int preCinde = 0;
int preDinde = 0;
int preEinde = 0;

int preainde = 0;
int prebinde = 0;
int precinde = 0;
int predinde = 0;
int preeinde = 0;

int creatMap::GoType(const unsigned type,const int nodeIndex) {
	const std::vector<unsigned> res=findPath(type, nodeIndex);








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
	if (type == 5) {
		c = 'a';
	}
	if (type == 6) {
		c = 'b';
	}
	if (type == 7) {
		c = 'c';
	}
	if (type == 8) {
		c = 'd';
	}
	if (type == 9) {
		c = 'e';
	}

	if (type >= 5) {
		if (res[ai][0] == startIndex) {
			//done 
			return -20;
		}
	}
	else {
		if (res[ai][0] == endIndex) {
			//done 
			return -20;
		}
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
	if (type == 5) {
		preainde = index;
	}
	if (type == 6) {
		prebinde = index;
	}
	if (type == 7) {
		precinde = index;
	}
	if (type == 8) {
		predinde = index;
	}
	if (type == 9) {
		preeinde = index;
	}
	return index;
}



void creatMap::Go() {

	const std::vector<unsigned> leftres = this->findPath(0, startIndex);
	const std::vector<unsigned> rightres = this->findPath(5, endIndex);

	if (leftres.size() == 0 || rightres.size() == 0) {
		std::cout << "can not find path..." << std::endl;
	}


	this->getNodeNodeByIndex(startIndex).printColorByStr('A',false);
	this->getNodeNodeByIndex(endIndex).printColorByStr('a', false);
	this->showMap();



	//A
	_RunPoint Arp(startIndex,0);

	 //int AIndex = startIndex;
	 //preAinde = AIndex;
	 //double Abeg = clock();
	 //double Aend = clock();
	 //double disA = 0.0;
	 //bool AisGo = false;
	 //bool AisDone = false;

	//B
	_RunPoint Brp(startIndex,1);
	 //int BIndex = startIndex;
	 //prerBinde = startIndex;
	 //double Bbeg = clock();
	 //double Bend = clock();
	 //double disB = 0.0;
	 //bool BisGo = false;
	 //bool BisDone = false;

	//C
	_RunPoint Crp(startIndex,2);
	 //int Cindex = startIndex;
	 //preCinde = startIndex;
	 //double Cbeg = clock();
	 //double Cend = clock();
	 //double disC = 0.0;
	 //bool CisGo = false;
	 //bool CisDone = false;

	//D
	_RunPoint Drp(startIndex,3);
	 //int Dindex = startIndex;
	 //preDinde = startIndex;
	 //double Dbeg = clock();
	 //double Dend = clock();
	 //double disD = 0.0;
	 //bool DisGo = false;
	 //bool DisDone = false;

	//E
	_RunPoint Erp(startIndex,4);

	 //int Eindex = startIndex;
	 //preEinde = startIndex;
	 //double Ebeg = clock();
	 //double Eend = clock();
	 //double disE = 0.0;
	 //bool EisGo = false;
	 //bool EisDone = false;


	 ////a
	 int aindex = endIndex;
	 preainde = aindex;
	 double abeg = clock();
	 double aend = clock();
	 double disa = 0.0;
	 bool aisGo = false;
	 bool aisDone = false;

	 ////b
	 //int bindex = endIndex;
	 //prebinde = bindex;
	 //double bbeg = clock();
	 //double bend = clock();
	 //double disb = 0.0;
	 //bool bisGo = false;
	 //bool bisDone = false;

	 ////c
	 //int cindex = endIndex;
	 //precinde = cindex;
	 //double cbeg = clock();
	 //double cend = clock();
	 //double disc = 0.0;
	 //bool cisGo = false;
	 //bool cisDone = false;

	 ////d
	 //int dindex = endIndex;
	 //predinde = dindex;
	 //double dbeg = clock();
	 //double dend = clock();
	 //double disd = 0.0;
	 //bool disGo = false;
	 //bool disDone = false;

	 ////e
	 //int eindex = endIndex;
	 //preeinde = eindex;
	 //double ebeg = clock();
	 //double eend = clock();
	 //double dise = 0.0;
	 //double eisGo = false;
	 //double eisDone = false;
	 

	while (true) {

		Arp.initRP();

		Aend = clock();
		disA = Aend - Abeg;
		if (disA >= 3.0 * 1000&& !AisDone) {
			this->getNodeNodeByIndex(preAinde).setStrAndBalk(' ', false);

			AIndex = this->GoType(0, AIndex);
			if (AIndex == -10) {
				if (!AisGo) {
					std::cout << "AIndex == -10 " << std::endl;
					return;
				}
				else {
					this->getNodeNodeByIndex(preAinde).setStrAndBalk('A', true);
					AIndex = preAinde;
				}
			}
			if (AIndex == -20) {
				this->getNodeNodeByIndex(preAinde).setStrAndBalk('A', false);
				AisDone = true;
			}
			AisGo = true;
			this->showMap();
			Abeg = Aend = clock();
			disA = 0.0;
		}

		aend = clock();
		disa = aend - abeg;
		if (disa >= 3.0 * 1000 && !aisDone) {
			this->getNodeNodeByIndex(preainde).setStrAndBalk(' ', false);
			aindex = this->GoType(5, aindex);
			if (aindex == -10) {
				if (!aisGo) {
					std::cout << "aindex == -10 " << std::endl;
					return;
				}
				else {
					this->getNodeNodeByIndex(preainde).setStrAndBalk('a', true);
					aindex = preainde;
				}
			}
			if (aindex == -20) {
				this->getNodeNodeByIndex(preainde).setStrAndBalk('a', false);
				aisDone = true;
			}
			aisGo = true;
			this->showMap();
			abeg = aend = clock();
			disa = 0.0;
		}


		Bend = clock();
		disB = Bend - Bbeg;
		if (disB >= 2.5 * 1000&&!BisDone) {
			if (AisGo) {
				if (!BisGo) {
					_map[1][1].printColorByStr('B', false);
				}
				else {
					this->getNodeNodeByIndex(prerBinde).setStrAndBalk(' ', false);
					BIndex = this->GoType(1, BIndex);
					if (BIndex == -10) {
						this->getNodeNodeByIndex(prerBinde).setStrAndBalk('B', true);
						BIndex = prerBinde;
					}
					if (BIndex == -20) {
						this->getNodeNodeByIndex(prerBinde).setStrAndBalk('B', false);
						BisDone = true;
					}
				}
				BisGo = true;
				this->showMap();
			}
			Bend = Bbeg = clock();
			disB = 0.0;
		}

		//bend = clock();
		//disb = bend - bbeg;
		//if (disb >= 2.5 * 1000 && !bisDone) {
		//	if (aisGo) {
		//		if (!bisGo) {
		//			this->getNodeNodeByIndex(endIndex).printColorByStr('b', false);
		//		}
		//		else {
		//			this->getNodeNodeByIndex(prebinde).setStrAndBalk(' ', false);
		//			bindex = this->GoType(6, bindex);
		//			if (bindex == -10) {
		//				this->getNodeNodeByIndex(prebinde).setStrAndBalk('b', true);
		//				bindex = prebinde;
		//			}
		//			if (bindex == -20) {
		//				this->getNodeNodeByIndex(prebinde).setStrAndBalk('b', false);
		//				bisDone = true;
		//			}
		//		}
		//		bisGo = true;
		//		this->showMap();
		//	}
		//	bend = bbeg = clock();
		//	disb = 0.0;
		//}

		Cend = clock();
		disC = Cend - Cbeg;
		if (disC >= 2.0 * 1000 &&!CisDone) {
			if (AisGo&&BisGo&&BIndex>startIndex) {
				if (!CisGo) {
					_map[1][1].printColorByStr('C', false);
				}
				else {
					this->getNodeNodeByIndex(preCinde).setStrAndBalk(' ', false);
					Cindex = this->GoType(2, Cindex);
					if (Cindex == -10) {
						this->getNodeNodeByIndex(preCinde).setStrAndBalk('C', true);
						Cindex = preCinde;
					}
					if (Cindex == -20) {
						this->getNodeNodeByIndex(preCinde).setStrAndBalk('C', false);
						CisDone = true;
					}
				}
				CisGo = true;
				this->showMap();
			}
			Cend = Cbeg = clock();
			disC = 0.0;
		}

		Dend = clock();
		disD = Dend - Dbeg;
		if (disD >= 1.5 * 1000 &&!DisDone) {
			if (AisGo&&BisGo&&CisGo&&Cindex > startIndex) {
				if (!DisGo) {
					_map[1][1].printColorByStr('D', false);
				}
				else {
					this->getNodeNodeByIndex(preDinde).setStrAndBalk(' ', false);
					Dindex = this->GoType(3, Dindex);
					if (Dindex == -10) {
						this->getNodeNodeByIndex(preDinde).setStrAndBalk('D', true);
						Dindex = preDinde;
					}
					if (Dindex == -20) {
						this->getNodeNodeByIndex(preDinde).setStrAndBalk('D', false);
						DisDone = true;
					}
				}
				DisGo = true;
				this->showMap();
			}
			Dend = Dbeg = clock();
			disD = 0.0;
		}


		Eend = clock();
		disE = Eend - Ebeg;
		if (disE >= 1.0 * 1000  &&!EisDone) {
			if (AisGo&&BisGo&&CisGo&&DisGo&&Dindex > startIndex) {
				if (!EisGo) {
					_map[1][1].printColorByStr('E', false);
				}
				else {
					this->getNodeNodeByIndex(preEinde).setStrAndBalk(' ', false);
					Eindex = this->GoType(4, Eindex);
					if (Eindex == -10) {
						this->getNodeNodeByIndex(preEinde).setStrAndBalk('E', true);
						Eindex = preEinde;
					}
					if (Eindex == -20) {
						this->getNodeNodeByIndex(preEinde).setStrAndBalk('E', false);
						EisDone = true;
					}
				}
				EisGo = true;
				this->showMap();
			}

			Eend = Ebeg = clock();
			disE = 0.0;
		}




		if (AisDone&&BisDone&&CisDone&&DisDone&&EisDone) {
			std::cout << "all done " << std::endl;
			return;
		}


	}
}






//RunPoint::RunPoint(int node) {
//	this->NodeIndex = node;
//	this->preNodeinde = node;
//	this->Tbeg = clock();
//	this->Tend = clock();
//	this->disTime = 0.0;
//	this->isGo = false;
//}
//
//void RunPoint::RPGo(creatMap *mthis) {
//	//Tend = clock();
//	//disTime = Tend - Tend;
//	//if (disTime >= 2.0 * 1000) {
//	//	if (AisGo) {
//	//		if (!BisGo) {
//	//			_map[1][1].printColorByStr('B', true);
//	//		}
//	//		else {
//	//			mthis->getNodeNodeByIndex(preNodeinde).setStrAndBalk(' ', false);
//	//			NodeIndex = mthis->GoType(1, NodeIndex);
//	//		}
//	//		isGo = true;
//	//		mthis->showMap();
//	//	}
//	//	Tend = Tend = clock();
//	//	disTime = 0.0;
//	//}
//}
