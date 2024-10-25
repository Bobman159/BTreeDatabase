#include "pch.h"
#include "CppUnitTest.h"
#include "BTreeTable.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BTreeTableDefinitionMSUnitTests
{
	TEST_CLASS(BTreeTableDefinitionMSUnitTests)
	{
	public:
		
		TEST_METHOD(TestcreateTable)
		{
//            struct TableDefinition* tableP = createTable("Meals");
            createTable("Meals");
//            Assert::AreEqual(tableP->tableName, "Meals2");
//            Assert::IsNotNull(tableP);
		}
	};
}
