#ifndef HYPOTHESIS_H_
#define HYPOTHESIS_H_

#include <string>
#include <iostream>

// static so that the variables are local to the compilation unit
static const std::string match_all = "\n";
static const std::string match_none = "\0";

class Hypothesis {
public:
  Hypothesis(int length);
  ~Hypothesis();
  
  std::string& operator [](int index);
  bool operator =(std::initializer_list<std::string> els);
  
  friend bool operator >=(const Hypothesis& a, const Hypothesis& b);
  friend bool operator >(const Hypothesis& a, const Hypothesis& b);
  friend bool operator <=(const Hypothesis& a, const Hypothesis& b);
  friend bool operator <(const Hypothesis& a, const Hypothesis& b);
  friend std::ostream& operator <<(std::ostream& out, const Hypothesis& h);

private:
  std::string *els;
  int length;
};

#endif