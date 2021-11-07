#include<iostream>
#include<vector>
#include<functional>

void ToAikoHello() noexcept { std::cout << "あーちゃんおはよ!" << std::endl; }
void ToMiriHello()noexcept { std::cout << "みりぴ久しぶり。。。" << std::endl; }
void ToAikoLove(std::string& name)noexcept { std::cout << name << ":初めて見た時からずっと好きでした" << std::endl; }
void ToMiriLove(std::string& name) noexcept { std::cout << name << ":いつまでも大好きです" << std::endl; }
void AikoAns(std::string& name)noexcept { std::cout<<name << ":私も大好きです" << std::endl; };
void MiriAns(std::string& name)noexcept { std::cout << name << ":早く言ってよバカ" << std::endl; }

class Human
{
public:
	virtual void Update() = 0;
protected:
	std::string m_name;
public:
	//設定なし
	Human() :m_name("NoName") {};
	virtual ~Human() {};
};


class Man : public Human
{
public:
	void Update() noexcept {
		if (this->m_name == "りと")
		{
			Greeting(ToAikoHello);
			Greeting(ToMiriHello);
			Confession(ToAikoLove);
			Confession(ToMiriLove);
		}
		else
		{//告白イベントは無し
			Greeting(ToAikoHello);
			Greeting(ToMiriHello);
		}
	};
public:
	//コンストラクタ(合成)
	Man(const std::string& name) { m_name = name; }
	~Man() { std::cout << m_name <<"死亡" << std::endl; }
private:
	//告白
	void Confession(const std::function<void(std::string&)>& callback) noexcept {callback(m_name);};
	//まずは簡単な挨拶
	void Greeting(const std::function<void()>& callback) noexcept { callback(); }
};

class Woman : public Human
{
public:
	void Update() noexcept {
		if (this->m_name == "あーちゃん")
		{
			Response(AikoAns);
		}else if (this->m_name == "みりちゃん")
		{
			Response(MiriAns);
		}
};
public:
	Woman(const std::string& name) { m_name = name; }
	~Woman() { std::cout << m_name << "死亡" << std::endl; }
private:
	//反応
	void Response(const std::function<void(std::string&)>& callback) noexcept {callback(m_name); }
};


int main(void)
{
	std::vector<std::unique_ptr<Human>> People;
	People.emplace_back(std::make_unique<Man>("りと"));
	People.emplace_back(std::make_unique<Woman>("あーちゃん"));
	People.emplace_back(std::make_unique<Woman>("みりちゃん"));

	for (const auto& v : People)
		v->Update();

	return 1;
}