#pragma once
#include <string>
class Ringnode {
	friend class Ringpuffer;
private:
	int oldAge;
	std::string desc;
	std::string data;
	Ringnode* next;

public:
	Ringnode();
	Ringnode(Ringnode* next, std::string desc, std::string data, int oldAge);
	~Ringnode();

	int getAge();
	void setAge(int age);

	std::string getDesc();
	void setDesc(std::string desc);

	std::string getData();
	void setData(std::string data);

	





};