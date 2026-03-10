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
	virtual void Add() override {}
};

class Decorator : public IHealth
{
public:

	void Add() override
	{
		std::cout << "Base\n";
	}

	Decorator(IHealth* health) : m_health(health)
	{
	}

	virtual ~Decorator()
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

class PlayerHealthDecorator : public Decorator
{
public:

	void Add() override
	{
		m_healthValue += 50;
		std::cout << "Health\n";

		m_health->Add();
	}

	PlayerHealthDecorator(IHealth* health) : Decorator(health), m_healthValue(100)
	{
	}

private:

	int m_healthValue;
};

class ShieldDecorator : public Decorator
{
public:

	void Add() override
	{
		m_shield += 50;
		std::cout << "Shield\n";

		m_health->Add();
	}

	ShieldDecorator(IHealth* health) : Decorator(health), m_shield(0)
	{
	}

private:
	
	int m_shield;
};

int main()
{
	IHealth* playerHealth = new Decorator(nullptr);
	playerHealth = new PlayerHealthDecorator(playerHealth);
	playerHealth->Add();

	playerHealth = new ShieldDecorator(playerHealth);
	playerHealth->Add();

	delete playerHealth;

	int i = 7;

	std::cout << "\n\n" << i << std::endl;
	system("pause");
	return 0;
}