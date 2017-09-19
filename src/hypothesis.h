#ifndef HYPOTHESIS_H_
#define HYPOTHESIS_H_

#include <string>
#include <iostream>
#include <vector>

// static so that the variables are local to the compilation unit
static const std::string match_all = "?";
static const std::string match_none = "#";

class Hypothesis {
public:
  Hypothesis(int length);
  Hypothesis(int length, std::string initialize);
  Hypothesis(const Hypothesis& h);
  ~Hypothesis();
  
  bool isSatisfy(std::initializer_list<std::string> els);
  bool isSatisfy(std::vector<std::string> els);
  
  std::string& operator [](int index);
  bool operator =(std::initializer_list<std::string> els);
  bool operator =(std::vector<std::string> els);
  
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