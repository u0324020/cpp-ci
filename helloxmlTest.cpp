#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/XmlOutputter.h>
#include <netinet/in.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
// you need to first register the test fixtures that you have made
CPPUNIT_TEST_SUITE_REGISTRATION(MathsMeanTest);
int main(int argc, char* argv[])
{
     // this is to inform test listener about testresults from the fixture
     CPPUNIT_NS::TestResult mytestresult;
     // this is to register listener for collecting test results
     CPPUNIT_NS::TestResultCollector mycollectedresults;
     mytestresult.addListener (&mycollectedresults);
     // this is to register listener for per test progress
     CPPUNIT_NS::BriefTestProgressListener myprogress;
     mytestresult.addListener (&myprogress);
     // this is to insert test suite at test runner by registry
     CPPUNIT_NS::TestRunner mytestrunner;
     mytestrunner.addTest (CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest ());
     mytestrunner.run(mytestresult);
     // this is to output results in compiler format
     CPPUNIT_NS::CompilerOutputter mycompileroutputter(&mycollectedresults, std::cerr);
     mycompileroutputter.write ();
     // this is to output XML for jenkins Cppunit plugin
     ofstream xmlFileOut("cppMathsMeanResult.xml");
     XmlOutputter xmlOut(&mycollectedresults, xmlFileOut);
     xmlOut.write();
     // this is to return 0 if tests were successful
     return mycollectedresults.wasSuccessful() ? 0 : 1;
}