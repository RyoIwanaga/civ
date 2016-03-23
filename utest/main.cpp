#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

// targets
#include "../Util.h"
#include "../Hex.h"

#include <stdio.h>
#include <set>

/*** Template
 
class UtilTest : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(UtilTest);
	CPPUNIT_TEST(addCircle);
	CPPUNIT_TEST_SUITE_END();

protected:

public:
	void setUp()
	{
	}
	void testDown()
	{
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(UtilTest);
  */

class UtilTest : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(UtilTest);
	CPPUNIT_TEST(addCircle);
	CPPUNIT_TEST_SUITE_END();

protected:
	void addCircle()
	{
		CPPUNIT_ASSERT_EQUAL(Util::addCircle(0, 1, 5), 1);
		CPPUNIT_ASSERT_EQUAL(Util::addCircle(0, 6, 5), 0);
		CPPUNIT_ASSERT_EQUAL(Util::addCircle(3, 5, 5), 2);
		CPPUNIT_ASSERT_EQUAL(Util::addCircle(3, 12, 5), 3);
		
		CPPUNIT_ASSERT_EQUAL(Util::addCircle(0, 1, 4, -1), 1);
		CPPUNIT_ASSERT_EQUAL(Util::addCircle(0, 5, 4, -1), -1);
		CPPUNIT_ASSERT_EQUAL(Util::addCircle(0, 12, 4, -1), 0);

		CPPUNIT_ASSERT_EQUAL(Util::addCircle(3, -1, 5), 2);
		CPPUNIT_ASSERT_EQUAL(Util::addCircle(3, -6, 5), 3);
		CPPUNIT_ASSERT_EQUAL(Util::addCircle(3, -12, 5), 3);

		CPPUNIT_ASSERT_EQUAL(Util::addCircle(0, -1, 3, -1), -1);
		CPPUNIT_ASSERT_EQUAL(Util::addCircle(0, -5, 3, -1), 0);
		CPPUNIT_ASSERT_EQUAL(Util::addCircle(0, -10, 3, -1), 0);

		//CPPUNIT_ASSERT_EQUAL(Util::addCircle(3, -2, 5), 1);
		//CPPUNIT_ASSERT_EQUAL(Util::addCircle(3, -5, 5), 4);
	}

public:
	void setUp()
	{
	}
	void testDown()
	{
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(UtilTest);

class HexTest : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(HexTest);
	CPPUNIT_TEST(neighbor);
	CPPUNIT_TEST_SUITE_END();

protected:
	void neighbor()
	{
		/*  width = 3
		 *
		 *     0 1 2
		 *	 +-------
		 * 0 | 0 1 2
		 * 1 |  3 4 5
		 * 2 | 6 7 8
		 * 3 |  9 a b 
		 */
		const int height = 4;
		const int width = 3;

		std::set<int> result;
		std::set<int> a;


		auto l = Hex::neighbors(0, height, width, false);

		result = listToSet(Hex::neighbors(0, height, width, false));
		a = std::set<int>{ 1, 3 };		
		CPPUNIT_ASSERT(result == a);

		for (auto item : result)
			printf("%d ", item);
		printf("\n");

		//std::cout << result << std::endl;
	}

	std::set<int> listToSet(const std::list<int>& lst)
	{
		std::set<int> s;

		for (auto item : lst)
			s.insert(item);

		return s;
	}

public:
	void setUp()
	{
	
	}
	void testDown()
	{
	
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(HexTest);


int main(int argc, char const *argv[]){

	CPPUNIT_NS::TestResult controller;

	//結果収集
	CPPUNIT_NS::TestResultCollector result;
	controller.addListener(&result);

	//途中結果の収集
	CPPUNIT_NS::BriefTestProgressListener progress;
	controller.addListener(&progress);

	//テストを走らせる。テストを入れて走る
	CPPUNIT_NS::TestRunner runner;
	runner.addTest( CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest() );
	runner.run(controller);

	//結果を標準出力にする。
	CPPUNIT_NS::CompilerOutputter outputter(&result,CPPUNIT_NS::stdCOut());
	outputter.write();

	return result.wasSuccessful() ? 0 : 1;
}
