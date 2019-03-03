#include "Ringnode.h"

Ringnode::Ringnode()
{
	next = nullptr;
}

Ringnode::Ringnode(Ringnode * next, std::string desc, std::string data, int oldAge)
{
	this->next = next;
	this->desc = desc;
	this->data = data;
	this->oldAge = oldAge;
}

Ringnode::~Ringnode()
{
}

int Ringnode::getAge()
{
	return this->oldAge;
}

void Ringnode::setAge(int age)
{
	this->oldAge = age;
}

std::string Ringnode::getDesc()
{
	return this->desc;
}

void Ringnode::setDesc(std::string desc)
{
	this->desc = desc;
}

std::string Ringnode::getData()
{
	return this->data;
}

void Ringnode::setData(std::string data)
{
	this->data = data;
}



