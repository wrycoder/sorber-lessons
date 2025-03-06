
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <ostream>

class person {
public:
  person(std::string newname) {
    name = newname;
  }

  friend std::ostream & operator<< (std::ostream &out, const person &p) {
    out << p.name;
    return out;
  }

  bool operator== (const person & p) {
    return this->name == p.name;
  }

private:
  std::string name;
};

int main()
{
  person p1("Jacob"), p2("Eliza"), p3("Barb");
  std::vector<person> vp;
  vp.push_back(p1);
  vp.push_back(p2);
  vp.push_back(p3);

  std::vector<person>::const_iterator it =
                        std::find( vp.begin(), vp.end(), p1);

  if (it != vp.end()) {
    std::cout << "Person found! " << *it << '\n';
  } else {
    std::cout << "Person not found.\n";
  }

}
