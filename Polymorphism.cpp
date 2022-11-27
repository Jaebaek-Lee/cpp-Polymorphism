﻿#include <iostream>

using namespace std;

//동일한 계층구조 안에 있다면, 자식객체들의 데이터 타입(클래스 이름)과 관계 없이
//부모 클래스의 포인터나 참조자로 연결함으로써 자식객체의 함수를 동적으로 사용할 수 있다.
//다형성이 없을 경우 : 블츠 픽 -> q -> 모든 챔피언을 돌며 블츠인지 아닌지 판단 -> 블츠를 찾으면 블츠의 q스킬 리턴 -> w -> 또 블츠를 찾음
//q가 블츠인지 니달린지 뭔지 그걸 매번 돌면서 파악해야함. -> 이 경우 q, w, e, r에 대한 모든 경우의 수를 다 만들어줘야함.
//다형성이 있을 경우 : 베이스 클래스의 포인터(q, w, e, r을 가진)를 자식 객체에 연결하는 과정을 거침.
//q 사용 -> 블츠를 찾을때까지 for문 돌다가 찾으면 q가 들어있는 챔피언이라는 베이스 클래스의 포인터를 블츠라는 객체에 동적으로 연결.
//앞으로 사용하는 모든 q w e r은 블츠의 q w e r로 인식됨.
//신챔이 추가되면 그냥 if(내 챔피언 == 신챔) 신챔에 포인터 연결// 하나만 더 만들어주면 됨.
//하나의 함수로 여러개의 객체 함수를 커버할 수 있음 -> 다형성
//베이스 포인터로 파생클래스 연결 -> ptr->파생클래스의 멤버함수 호출 불가능. 베이스니까 결국 베이스만 가능. = 업캐스팅(자식객체가 부모객체처럼 승격).
//베이스 클래스의 멤버함수를 가상함수로 만들면 무시하고 파생클래스의 동일한 이름 멤버함수를 호출.

class Base {
public:
	void fun() { display(); }
	virtual void display() { cout << "Base" << endl; }
	virtual ~Base() { cout << "Base destructor.\n"; }
};

class Derived : public Base {
public:
	/*virtual(자동 상속)*/void display() override/*명시적으로 적음. 그리고 시그니처 다를때 오류를 띄워줌.*/
	/*여기까지만 오버라이딩 할 것. 파생 파생 클래스에서는 display를 재정의할 수 없음.*/ { cout << "Deriver" << endl; }
	//중복정의(오버로딩)이 아닌 재정의(오버라이딩). 완벽히 같은 프로토타입.
	~Derived() { cout << "Derived destructor.\n"; }
};

//void Drived::display() const { ~~ } 외부 정의시에 virtual, override 키워드를 뺌.

int main() {
	Base* ptr = new Derived;
	ptr->display(); //오버라이딩 된 파생클래스 display 호출.
	ptr->fun(); //파생클래스의 display를 호출함. -> 위 베이스 하나만 설계 : 지금은 베이스만 쓰지만, 언젠가 fun함수로 파생클래스의 display를 실행할거임.
	delete ptr; //ptr에 동적할당한 메모리를 해제. 여기서는 베이스 포인터라 그냥 베이스 소멸자만 호출하고 파생 소멸자 호출 안해버림.
	//그건 정의되지 않은 행동이다. 하지만 베이스 소멸자를 가상 소멸자로 만든다. 그럼 파생 소멸자를 먼저 호출하고 그 다음 정상적으로 베이스 소멸자 호출.
}

//재정의(오버라이딩). 베이스와 파생이 가진 똑같은 함수 시그니처가 있을때, 파생으로 재정의 된 것. 따라서 der.fun() 하면 변수 가리기로 파생이 호출.
//하지만 Base 포인터로 파생 연결 후 base->fun() 하면 결국 base 타입이라 base의 함수가 호출됨. base::fun()마냥. 그래서 베이스의 함수 프로토타입을
//virual 선언하면 베이스의 함수를 무시하고 파생에서 재정의된 함수를 호출하게 됨.

//순수 가상함수 : 정의부를 가지고 있지 않음. 즉 = 0;으로 선언된 함수.
//즉 형태만 가지고 있고 기능(동작)은 없음.
//이걸 하나 이상 가지고 있으면 추상 클래스가 됨.
//추상 클래스로는 객체를 만들 수 없다.
//그러나 상속은 가능하다. 포인터와 참조자는 만들 수 있다. 다형성도 가능.
//추상 클래스 - 자식클래스에게 다형성을 제공해준다. and 개발 효율 높아짐.

//파생클래스는 반드시 모든 순수 가상함수를 오버라이딩 해야함. 안그러면 파생도
//추상 클래스가 됨. -> 오버라이딩 다 되면 concrete class(구체, 구현)가 된다.

//예외 : 순수가상함수를 외부 정의한 경우: 모든 파생클래스들에게 디폴트 기능을 제공하고 싶을 때 사용.
//베이스에서 선언된 순수 가상함수를 파생클래스에서 오버라이딩 했다면, 그 파생클래스의 파생클래스에서는 안해도 객체를 생성할 수 있다.//아닌가...?

//const A* aptr = &ptr; - aptr이 간접적으로 가리키는 값을 변경할 수 없음.
//A* const aptr = &ptr; - aptr이 가리키는 주소를 변경할 수 없음.
//const A* const aptr = &ptr; - aptr이 간접적으로 가리키는 값과 주소를 모두 바꿀 수 없음.
