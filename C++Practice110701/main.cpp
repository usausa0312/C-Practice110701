#include<iostream>
#include<vector>
#include<functional>

void ToAikoHello() noexcept { std::cout << "���[����񂨂͂�!" << std::endl; }
void ToMiriHello()noexcept { std::cout << "�݂�ҋv���Ԃ�B�B�B" << std::endl; }
void ToAikoLove(std::string& name)noexcept { std::cout << name << ":���߂Č��������炸���ƍD���ł���" << std::endl; }
void ToMiriLove(std::string& name) noexcept { std::cout << name << ":���܂ł���D���ł�" << std::endl; }
void AikoAns(std::string& name)noexcept { std::cout<<name << ":������D���ł�" << std::endl; };
void MiriAns(std::string& name)noexcept { std::cout << name << ":���������Ă�o�J" << std::endl; }

class Human
{
public:
	virtual void Update() = 0;
protected:
	std::string m_name;
public:
	//�ݒ�Ȃ�
	Human() :m_name("NoName") {};
	virtual ~Human() {};
};


class Man : public Human
{
public:
	void Update() noexcept {
		if (this->m_name == "���")
		{
			Greeting(ToAikoHello);
			Greeting(ToMiriHello);
			Confession(ToAikoLove);
			Confession(ToMiriLove);
		}
		else
		{//�����C�x���g�͖���
			Greeting(ToAikoHello);
			Greeting(ToMiriHello);
		}
	};
public:
	//�R���X�g���N�^(����)
	Man(const std::string& name) { m_name = name; }
	~Man() { std::cout << m_name <<"���S" << std::endl; }
private:
	//����
	void Confession(const std::function<void(std::string&)>& callback) noexcept {callback(m_name);};
	//�܂��͊ȒP�Ȉ��A
	void Greeting(const std::function<void()>& callback) noexcept { callback(); }
};

class Woman : public Human
{
public:
	void Update() noexcept {
		if (this->m_name == "���[�����")
		{
			Response(AikoAns);
		}else if (this->m_name == "�݂肿���")
		{
			Response(MiriAns);
		}
};
public:
	Woman(const std::string& name) { m_name = name; }
	~Woman() { std::cout << m_name << "���S" << std::endl; }
private:
	//����
	void Response(const std::function<void(std::string&)>& callback) noexcept {callback(m_name); }
};


int main(void)
{
	std::vector<std::unique_ptr<Human>> People;
	People.emplace_back(std::make_unique<Man>("���"));
	People.emplace_back(std::make_unique<Woman>("���[�����"));
	People.emplace_back(std::make_unique<Woman>("�݂肿���"));

	for (const auto& v : People)
		v->Update();

	return 1;
}