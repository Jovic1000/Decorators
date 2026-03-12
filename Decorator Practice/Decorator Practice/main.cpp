#include <iostream>

class IHealth
{
public:

	virtual void Add() = 0;
	virtual ~IHealth() {};

private:
};

class HealthBase : public IHealth
{
public:

	void Add() override
	{
		std::cout << "Base\n";
	}

	HealthBase(IHealth* health) : m_health(health)
	{
	}

	virtual ~HealthBase()
	{
		std::cout << "Deleted Base" << std::endl;
		if (m_health)
		{
			delete m_health;
		}
	}

protected:

	IHealth* m_health;
};

class PlayerHealthDecorator : public HealthBase
{
public:

	void Add() override
	{
		m_healthValue += 50;
		std::cout << "Health\n";

		m_health->Add();
	}

	PlayerHealthDecorator(IHealth* health) : HealthBase(health), m_healthValue(100)
	{
	}

private:

	int m_healthValue;
};

class ShieldDecorator : public HealthBase
{
public:

	void Add() override
	{
		m_shield += 50;
		std::cout << "Shield\n";

		m_health->Add();
	}

	ShieldDecorator(IHealth* health) : HealthBase(health), m_shield(0)
	{
	}

private:
	
	int m_shield;
};

int main()
{
	IHealth* playerHealth = new HealthBase(nullptr);
	playerHealth = new PlayerHealthDecorator(playerHealth);
	playerHealth->Add();

	playerHealth = new ShieldDecorator(playerHealth);
	playerHealth->Add();

	delete playerHealth;
	playerHealth = nullptr;
	system("pause");
	return 0;
}