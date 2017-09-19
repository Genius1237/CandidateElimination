#include "hypothesis.h"

/*
	Precondition: length > 0
*/
Hypothesis::Hypothesis(int length) {
	els = new std::string [length];
	this -> length = length;
}

Hypothesis::Hypothesis(int length, std::string initialize) {
	els = new std::string [length];
	this -> length = length;
	for (int i = 0; i < length; i++) {
		els[i] = initialize;
	}	
}

Hypothesis::Hypothesis(const Hypothesis& h) {
	delete [] els;
	els = new std::string [h.length];
	length = h.length;
	for (int i = 0; i < h.length; i++) {
		els[i] = h.els[i];
	}
}

Hypothesis::~Hypothesis() {
	delete [] els;
}

bool Hypothesis::isSatisfy(std::initializer_list<std::string> els) {
	if (length != els.size()) {
		return false;
	}
	Hypothesis h(length);
	h = els;
	return ((*this) >= h);
}

bool Hypothesis::isSatisfy(std::vector<std::string> els) {
	if (length != els.size()) {
		return false;
	}
	Hypothesis h(length);
	h = els;
	return ((*this) >= h);
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

bool Hypothesis::operator =(std::vector<std::string> els) {
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