#include "Run.h"


#define RED          "\033[0;32;31m"

void printClean() {
	
	//system("reset");

	system("cls");
	//system("clear");

	//printf("\033 [K");


	//printf("\033c");
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
		//std::cout << "radom num big ......." << std::endl;
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
	//std::cout << "cant not find x y" << std::endl;
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
	//std::cout << iVec.size() << std::endl;
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
	//system("sleep 1");
	//printf("\033[20A");
	for (unsigned i = 0; i != _map.size(); ++i) {
		for (unsigned j = 0; j != _map[i].size(); ++j) {
			_map[i][j].printNodeStr();
		}
		std::cout << std::endl;
	}
	//printf("\033[0m");
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



	return res;
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

int isCanGo = 0;

int creatMap::GoType(const unsigned type,const int nodeIndex) {
	const std::vector<std::vector<unsigned>> res=findPath(type, nodeIndex);


	int ai = -1;

	for (unsigned i = 0; i != res.size(); ++i) {
		for (unsigned j = 0; j != res[i].size(); ++j) {
			if (type >= 5) {
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

	if (ai <0) {
		//std::cout << "can not find path..222222222222 ";
		if (isCanGo == 0)
			return -10;
		if (res.size() <= 1) {
			return -10;
		}
		else {
			unsigned tempIndex = 0;
			if (type >= 5) {
				tempIndex = endIndex;
			}
			else {
				tempIndex = startIndex;
			}
			
			unsigned tempI = 0;
			for (unsigned i = 0; i != res.size(); ++i) {
				if (type >= 5) {
					if (res[i][res[i].size() - 1] <= tempIndex) {
						tempIndex = res[i][res[i].size() - 1];
						tempI = i;
					}
				}
				else {
					if (res[i][res[i].size() - 1] >= tempIndex) {
						tempIndex = res[i][res[i].size() - 1];
						tempI = i;
					}
				}
	
			}

			unsigned index = 0;
			if (res[tempI].size() <= 1) {
				index = res[tempI][0];
			}
			else {
				index = res[tempI][1];
			}
			 
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
	}

	isCanGo++;

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

	this->getNodeNodeByIndex(startIndex).printColorByStr('A',false);
	this->getNodeNodeByIndex(endIndex).printColorByStr('a', false);
	this->showMap();



	//A
	 int AIndex = startIndex;
	 preAinde = AIndex;
	 double Abeg = clock();
	 double Aend = clock();
	 double disA = 0.0;
	 bool AisGo = false;
	 bool AisDone = false;

	//B
	 int BIndex = startIndex;
	 prerBinde = startIndex;
	 double Bbeg = clock();
	 double Bend = clock();
	 double disB = 0.0;
	 bool BisGo = false;
	 bool BisDone = false;

	//C
	 int Cindex = startIndex;
	 preCinde = startIndex;
	 double Cbeg = clock();
	 double Cend = clock();
	 double disC = 0.0;
	 bool CisGo = false;
	 bool CisDone = false;

	//D
	 int Dindex = startIndex;
	 preDinde = startIndex;
	 double Dbeg = clock();
	 double Dend = clock();
	 double disD = 0.0;
	 bool DisGo = false;
	 bool DisDone = false;

	//E
	 int Eindex = startIndex;
	 preEinde = startIndex;
	 double Ebeg = clock();
	 double Eend = clock();
	 double disE = 0.0;
	 bool EisGo = false;
	 bool EisDone = false;


	 //a
	 int aindex = endIndex;
	 preainde = aindex;
	 double abeg = clock();
	 double aend = clock();
	 double disa = 0.0;
	 bool aisGo = false;
	 bool aisDone = false;

	 //b
	 int bindex = endIndex;
	 prebinde = bindex;
	 double bbeg = clock();
	 double bend = clock();
	 double disb = 0.0;
	 bool bisGo = false;
	 bool bisDone = false;

	 //c
	 int cindex = endIndex;
	 precinde = cindex;
	 double cbeg = clock();
	 double cend = clock();
	 double disc = 0.0;
	 bool cisGo = false;
	 bool cisDone = false;

	 //d
	 int dindex = endIndex;
	 predinde = dindex;
	 double dbeg = clock();
	 double dend = clock();
	 double disd = 0.0;
	 bool disGo = false;
	 bool disDone = false;

	 //e
	 int eindex = endIndex;
	 preeinde = eindex;
	 double ebeg = clock();
	 double eend = clock();
	 double dise = 0.0;
	 double eisGo = false;
	 double eisDone = false;
	 

	while (true) {

		Aend = clock();
		disA = Aend - Abeg;
		if (disA >= 3.0 * 1000&& !AisDone) {
			this->getNodeNodeByIndex(preAinde).setStrAndBalk(' ', false);
			AIndex = this->GoType(0, AIndex);
			if (AIndex == -10) {
				if (!AisGo) {
					//std::cout << "AIndex == -10 " << std::endl;
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
				AIndex = endIndex;
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
					//std::cout << "aindex == -10 " << std::endl;
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
				aindex = startIndex;
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
						BIndex = startIndex;
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
		//				bindex = startIndex;
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
						Cindex = endIndex;
					}
				}
				CisGo = true;
				this->showMap();
			}
			Cend = Cbeg = clock();
			disC = 0.0;
		}


		//cend = clock();
		//disc = cend - cbeg;
		//if (disc >= 2.0 * 1000 && !cisDone) {
		//	if (aisGo  && bisGo && bindex<endIndex) {
		//		if (!cisGo) {
		//			this->getNodeNodeByIndex(endIndex).printColorByStr('c', false);
		//		}
		//		else {
		//			this->getNodeNodeByIndex(precinde).setStrAndBalk(' ', false);
		//			cindex = this->GoType(7, cindex);
		//			if (cindex == -10) {
		//				this->getNodeNodeByIndex(precinde).setStrAndBalk('c', true);
		//				cindex = precinde;
		//			}
		//			if (cindex == -20) {
		//				this->getNodeNodeByIndex(precinde).setStrAndBalk('c', false);
		//				cisDone = true;
		//				cindex = startIndex;
		//			}
		//		}
		//		cisGo = true;
		//		this->showMap();
		//	}
		//	cend = cbeg = clock();
		//	disc = 0.0;
		//}

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
						Dindex = endIndex;
					}
				}
				DisGo = true;
				this->showMap();
			}
			Dend = Dbeg = clock();
			disD = 0.0;
		}


		//dend = clock();
		//disd = dend - dbeg;
		//if (disd >= 1.5 * 1000 && !disDone) {
		//	if (aisGo  && bisGo && cisGo && cindex<endIndex) {
		//		if (!disGo) {
		//			this->getNodeNodeByIndex(endIndex).printColorByStr('d', false);
		//		}
		//		else {
		//			this->getNodeNodeByIndex(predinde).setStrAndBalk(' ', false);
		//			dindex = this->GoType(8, dindex);
		//			if (dindex == -10) {
		//				this->getNodeNodeByIndex(predinde).setStrAndBalk('d', true);
		//				dindex = predinde;
		//			}
		//			if (dindex == -20) {
		//				this->getNodeNodeByIndex(predinde).setStrAndBalk('d', false);
		//				disDone = true;
		//				dindex = startIndex;
		//			}
		//		}
		//		disGo = true;
		//		this->showMap();
		//	}
		//	dend = dbeg = clock();
		//	disd = 0.0;
		//}


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
						Eindex = endIndex;
					}
				}
				EisGo = true;
				this->showMap();
			}

			Eend = Ebeg = clock();
			disE = 0.0;
		}

		//eend = clock();
		//dise = eend - ebeg;
		//if (dise >= 1.0 * 1000 && !eisDone) {
		//	if (aisGo  && bisGo && cisGo && disGo && dindex<endIndex) {
		//		if (!eisGo) {
		//			this->getNodeNodeByIndex(endIndex).printColorByStr('e', false);
		//		}
		//		else {
		//			this->getNodeNodeByIndex(preeinde).setStrAndBalk(' ', false);
		//			eindex = this->GoType(9, eindex);
		//			if (eindex == -10) {
		//				this->getNodeNodeByIndex(preeinde).setStrAndBalk('e', true);
		//				eindex = preeinde;
		//			}
		//			if (eindex == -20) {
		//				this->getNodeNodeByIndex(preeinde).setStrAndBalk('e', false);
		//				eisDone = true;
		//				eindex = startIndex;
		//			}
		//		}
		//		eisGo = true;
		//		this->showMap();
		//	}
		//	eend = ebeg = clock();
		//	dise = 0.0;
		//}


		if (AisDone&&BisDone&&CisDone&&DisDone&&EisDone  &&aisDone &&bisDone && cisDone &&disDone &&eisDone) {
			//std::cout << "all done " << std::endl;
			return;
		}

	}
}


