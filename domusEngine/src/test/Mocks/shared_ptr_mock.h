/*
 * shared_ptr_mock.h
 *
 *  Created on: 31/dic/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_MOCKS_SHARED_PTR_MOCK_H_
#define SRC_TEST_MOCKS_SHARED_PTR_MOCK_H_

#include <memory>

template<typename Base, class Mock>
class shared_ptr_mock : public std::shared_ptr<Mock> {
public:
	shared_ptr_mock():std::shared_ptr<Mock>(std::make_shared<Mock>()){}
	shared_ptr_mock(Mock * mock): std::shared_ptr<Mock>(mock){}
	operator std::shared_ptr<Base> (){return std::dynamic_pointer_cast<Base>(*this);}
	std::shared_ptr<Base> getBase() {return std::dynamic_pointer_cast<Base>(*this);}
};

template<typename Base, class Mock>
class sharedMockClass {
public:
	static shared_ptr_mock<Base, Mock> makeShared() {return shared_ptr_mock<Base, Mock>(new Mock{});}
};


#endif /* SRC_TEST_MOCKS_SHARED_PTR_MOCK_H_ */
