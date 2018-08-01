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

class Client {
 public:
  void draw()
  {
#ifdef LINUX
	  Widget *w = new LinuxButton;
#else
	  Widget *w = new WindowsButton;
#endif
	  w->draw();
	  display_window_one();
	  display_window_two();
  }
  void display_window_one()
  {
#ifdef LINUX
	  Widget *w[] = {
		  new LinuxButton,
		  new LinuxMenu
	  };
#else
	  Widget *w[] = {
		new WindowsButton,
		new WindowsMenu
	};
#endif
	  w[0]->draw();
	  w[1]->draw();
  }
  void display_window_two()
  {
#ifdef LINUX
	  Widget *w[] = {
		  new LinuxMenu,
		  new LinuxButton
	  };
#else // WINDOWS
	  Widget *w[] = {
		new WindowsMenu,
		new WindowsButton
	};
#endif
	  w[0]->draw();
	  w[1]->draw();
  }
};

int main()
{
	Client *c = new Client();
	c->draw();
	delete c;
	return 0;
}