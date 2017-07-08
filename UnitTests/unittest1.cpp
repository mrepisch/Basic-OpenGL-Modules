#include "stdafx.h"
#include "CppUnitTest.h"
#include "../BasicOpenGLModules/src/util/Vector3D.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Vector3D<float>a_test(20.0f,30.0f,40.0f);
			Assert::IsTrue(a_test.getX() <= 21.0f);
			// TODO: Testcode hier eingeben
		}

	};
}