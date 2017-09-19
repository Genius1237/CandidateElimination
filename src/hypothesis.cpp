#include "hypothesis.h"
#include <fstream>
#include <sstream>

Hypothesis::Hypothesis() {
	;
}

Hypothesis::Hypothesis(int length, std::string initialize) {
	els = std::vector<std::string> (length, initialize);
}

Hypothesis::Hypothesis(const Hypothesis& h) {
	els = h.els;
}

Hypothesis::~Hypothesis() {
	;
}

bool Hypothesis::isSatisfy(std::initializer_list<std::string> els) {
	if ((this -> els).size() != els.size()) {
		return false;
	}
	Hypothesis h;
	h = std::vector<std::string> (els);
	return ((*this) >= h);
}

bool Hypothesis::isSatisfy(std::vector<std::string> els) {
	if ((this -> els).size() != els.size()) {
		return false;
	}
	Hypothesis h;
	h = els;
	return ((*this) >= h);
}

/*
	Precondition: 0 <= index < length
*/
std::string& Hypothesis::operator [](int index) {
	return els[index];
}

Hypothesis Hypothesis::operator =(std::initializer_list<std::string> els) {
	this -> els = std::vector<std::string> (els);
	return (*this);
}

Hypothesis Hypothesis::operator =(std::vector<std::string> els) {
	this -> els = els;
	return (*this);
}

/*
	Precondition: Length of both hypotheses are equal
*/
bool operator >=(const Hypothesis& a, const Hypothesis& b) {
	for (int i = 0; i < a.els.size(); i++) {
		if ((a.els[i] != match_all && a.els[i] != match_none &&
			a.els[i] != b.els[i] && b.els[i] != match_none) || 
			(a.els[i] == match_none && b.els[i] != match_none)) {
			return false;
		}
	}
	return true;
}

bool operator >(const Hypothesis& a, const Hypothesis& b) {
	return (a >= b && !(a <= b));
}

bool operator <=(const Hypothesis& a, const Hypothesis& b) {
	for (int i = 0; i < a.els.size(); i++) {
		if ((a.els[i] != match_all && a.els[i] != match_none &&
			a.els[i] != b.els[i] && b.els[i] != match_all) || 
			(a.els[i] == match_all && b.els[i] != match_all)) {
			return false;
		}
	}
	return true;
}

bool operator <(const Hypothesis& a, const Hypothesis& b) {
	return (a <= b && !(a >= b));
}

bool operator ==(const Hypothesis& a, const Hypothesis& b) {
	return (a <= b && (a >= b));
}

std::ostream& operator <<(std::ostream& out, const Hypothesis& h) {
	out << "<";
	for (int i = 0; i < h.els.size() - 1; i++) {
		out << h.els[i] << ",";
	}
	out << h.els[h.els.size() - 1] << ">";
	return out;
}



std::vector<std::vector<std::string>> readData(int n=18,std::string fileloc="../data/zoo.data"){
	//std::string fileloc="../data/zoo.data";
	std::ifstream fin(fileloc,std::ios::in);
	std::vector<std::vector<std::string>> data;
	while(!fin.eof()){
		std::string s;
		std::vector<std::string> att;

		fin>>s;

		std::stringstream str(s);
		
		for(int i=0;i<n;i++){
			std::string temp;
			std::getline(str,temp,',');
			att.push_back(temp);
		}

		/*
		for(auto i=boollist.begin();i!=boollist.end();i++){
			att[*i]=(att[*i]=="0"?"false":"true");
		}
		*/
		/*
		for(auto i=att.begin();i!=att.end();i++){
			std::cout<<*i<<",";
		}
		std::cout<<std::endl;
		*/
		data.push_back(att);
	}
	return data;
}