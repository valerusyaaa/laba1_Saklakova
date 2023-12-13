#include "Truba.h"

Truba::Truba()
{
	lenght = 100;
	name = "Unknown";
}

Truba::~Truba() // освобождаем ресурсы
{

}

std::string Truba::GetName() const
{
	return name;
}

void Truba::SetName(std::string new_name)
{
	name = new_name;
}
