#include <hypothesis.h>

/*
	Precondition: length > 0
*/
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

/*
	Precondition: Length of both hypotheses are equal
*/
bool operator >=(Hypothesis a, Hypothesis b) {
	for (int i = 0; i < a.length; i++) {
		if ((a.els[i] != match_all && a.els[i] != match_none &&
			a.els[i] != b.els[i] && b.els[i] != match_none) || 
			(a.els[i] == match_none && b.els[i] != match_none)) {
			return false;
		}
	}
	return true;
}

bool operator >(Hypothesis a, Hypothesis b) {
	return (a >= b && !(a <= b));
}

bool operator <=(Hypothesis a, Hypothesis b) {
	for (int i = 0; i < a.length; i++) {
		if ((a.els[i] != match_all && a.els[i] != match_none &&
			a.els[i] != b.els[i] && b.els[i] != match_all) || 
			(a.els[i] == match_all && b.els[i] != match_all)) {
			return false;
		}
	}
	return true;
}

bool operator <(Hypothesis a, Hypothesis b) {
	return (a <= b && !(a >= b));
}