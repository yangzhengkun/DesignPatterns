//
// Created by yangzhengkun on 2018/8/1.
// reference: https://sourcemaking.com/design_patterns/abstract_factory/cpp/before-after
//

#include <iostream>

#define LINUX

using namespace std;
/**
 * Abstract base product
 */
class Widget {
 public:
  virtual void draw() = 0;
  virtual ~Widget()
  {}
};

/**
 * Concrete product family 1
 */
class LinuxButton : public Widget {
 public:
  void draw() override
  { cout << "LinuxButton" << endl; }
};

class LinuxMenu : public Widget {
 public:
  void draw() override
  {
	  cout << "LinuxMenu" << endl;
  }
};

/**
 * Concrete product family 2
 */
class WindowsButton : public Widget {
 public:
  void draw() override
  {
	  cout << "WindowsButton" << endl;
  }
};
class WindowsMenu : public Widget {
 public:
  void draw() override
  {
	  cout << "WindowsMenu" << endl;
  }
};

/**
 * 抽象工厂类，由其子类创建具体对象
 */
class AbstractFactory {
 public:
  virtual Widget *create_button() = 0;
  virtual Widget *create_menu() = 0;
  virtual ~AbstractFactory()
  {}
};

/**
 * 具体工厂类，用于创建特定类型的对象
 */
class LinuxFactory : public AbstractFactory {
 public:
  Widget *create_button() override
  {
	  return new LinuxButton;
  }
  Widget *create_menu() override
  {
	  return new LinuxMenu;
  }
  ~LinuxFactory() = default;
};

class WindowsFactory : public AbstractFactory {
 public:
  Widget *create_button() override
  {
	  return new WindowsButton;
  }
  Widget *create_menu() override
  {
	  return new WindowsMenu;
  }
  ~WindowsFactory() = default;
};

class Client {
 private:
  AbstractFactory *factory;

 public:
  Client(AbstractFactory *f) : factory(f)
  {}
  void draw()
  {
	  Widget *w = factory->create_button();
	  w->draw();
	  display_window_one();
	  display_window_two();
	  delete w;
  }

  void display_window_one()
  {
	  Widget *w[]{
		  factory->create_button(),
		  factory->create_menu()
	  };
	  w[0]->draw();
	  w[1]->draw();
	  delete w[0];
	  delete w[1];
  }
  void display_window_two()
  {
	  Widget *w[] = {
		  factory->create_menu(),
		  factory->create_button()
	  };
	  w[0]->draw();
	  w[1]->draw();
	  delete w[0];
	  delete w[1];
  }
};

int main()
{
	AbstractFactory *factory;
#ifdef LINUX
	factory = new LinuxFactory;
#else
	factory = new WindowsFactory;
#endif

	Client *c = new Client(factory);
	c->draw();
	delete c;
	return 0;
}