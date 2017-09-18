#include "hypothesis.h"

/*
	Precondition: length > 0
*/
using std::cout;
Hypothesis::Hypothesis(int length) {
	els = new std::string [length];
	this -> length = length;
}

Hypothesis::~Hypothesis() {
	delete [] els;
}

/*
	Precondition: 0 <= index < length
*/
std::string& Hypothesis::operator [](int index) {
	return els[index];
}

bool Hypothesis::operator =(std::initializer_list<std::string> els) {
	if (length != els.size()) {
		return false;
	}
	int i = 0;
	for (auto el: els) {
		(this -> els)[i] = el;
		++i;
	}
	return true;
}

/*
	Precondition: Length of both hypotheses are equal
*/
bool operator >=(const Hypothesis& a, const Hypothesis& b) {
	for (int i = 0; i < a.length; i++) {
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
	for (int i = 0; i < a.length; i++) {
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

std::ostream& operator <<(std::ostream& out, const Hypothesis& h) {
	out << "<";
	for (int i = 0; i < h.length - 1; i++) {
		out << h.els[i] << ",";
	}
	out << h.els[h.length - 1] << ">";
	return out;
}