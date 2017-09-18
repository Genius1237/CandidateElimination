#ifndef HYPOTHESIS_H_
#define HYPOTHESIS_H_

#include <string>

// static so that the variables are local to the compilation unit
static const std::string match_all = "\n";
static const std::string match_none = "\0";

class Hypothesis {
public:
  Hypothesis(int length);
  ~Hypothesis();
  std::string& operator [](int index);
  friend bool operator >=(Hypothesis a, Hypothesis b);
  friend bool operator >(Hypothesis a, Hypothesis b);
  friend bool operator <=(Hypothesis a, Hypothesis b);
  friend bool operator <(Hypothesis a, Hypothesis b);
private:
  std::string *els;
  int length;
};

#endif