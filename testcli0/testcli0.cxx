// Generated CLP header
#include "testcli0CLP.h"

// anonymous namespace
namespace
{

/**
* Test that two values are equal and print message if not.
* @param name The name of the test.
* @param var The value to test.
* @param ref The reference value to compare with.
* @return True if both values are equal.
*/
template<class T>
bool test(const std::string& name, const T& var, const T& ref)
{
    if( var != ref )
    {
        std::cerr << "Test '" << name << "' FAILED: " 
             << "values are not equal ('" 
             << var << "' != '" << ref << "')." << std::endl;
        return false;
    }
    return true;
}

/**
* Test that two vectors are equal and print message if not.
* @param name The name of the test.
* @param var The vector to test.
* @param ref The reference vector to compare with.
* @return True if both vector have same size and same content.
*/
template<class T>
bool test(const std::string& name, const std::vector<T>& var, const std::vector<T>& ref)
{
    // Check vector sizes
    if( var.size() != ref.size() )
    {
        std::cerr << "Test '" << name << "' FAILED: " 
            << "Vector sizes are not equal ('" 
            << var.size() << "' != '" << ref.size() << "')." << std::endl;
        return false;
    }
    // Check vector content
    bool res = true;
    for( unsigned int i = 0; i < var.size(); ++i )
    {
        res &= test( name, var[i], ref[i] );
    }
    return res;
}

} // anonymous namespace

/**
* CLI test #0: check that default CLP arguments are passed as expected to 
* this application. See xml for arguments.
* (No external dependencies)
*/
int main (int argc, char *argv[])
{
    // Parse input arguments
    PARSE_ARGS;
  
    // Check arguments
    bool res = true;

    // basic types
    res &= test("int", tInt, (int)1);
    res &= test("float", tFloat, (float)1.0);
    res &= test("double", tDouble, (double)1.0);
    res &= test("bool", tBool, false);
    res &= test<std::string>("string", tString, "a");
    res &= test("constrained int", tInt2, (int)2);
    res &= test("constrained double", tDouble2, (double)2.0);
    
    // vectors
    std::vector<int> refIntVector(4);
    refIntVector[0] = (int)1;
    refIntVector[1] = (int)2;
    refIntVector[2] = (int)3;
    refIntVector[3] = (int)4;
    res &= test("int vector", tIntVector, refIntVector);
    std::vector<float> refFloatVector(4);
    refFloatVector[0] = (float)1.0;
    refFloatVector[1] = (float)2.0;
    refFloatVector[2] = (float)3.0;
    refFloatVector[3] = (float)4.0;
    res &= test("float vector", tFloatVector, refFloatVector);
    std::vector<double> refDoubleVector(4);
    refDoubleVector[0] = (double)1.0;
    refDoubleVector[1] = (double)2.0;
    refDoubleVector[2] = (double)3.0;
    refDoubleVector[3] = (double)4.0;
    res &= test("double vector", tDoubleVector, refDoubleVector);
    std::vector<std::string> refStringVector(4);
    refStringVector[0] = "a";
    refStringVector[1] = "b";
    refStringVector[2] = "c";
    refStringVector[3] = "d";
    res &= test("string vector", tStringVector, refStringVector);
    
    // enums
    res &= test("int enum", tIntEnum, (int)1);
    res &= test("float enum", tFloatEnum, (float)1.0);
    res &= test("double enum", tDoubleEnum, (double)1.0);
    res &= test<std::string>("str enum", tStrEnum, "a");
    
    // special
    res &= test<std::string>("file", tFile, "file.txt");
    res &= test<std::string>("directory", tDirectory, "/a/b/c");
    res &= test<std::string>("image", tImage, "image.img");
    res &= test<std::string>("geometry", tGeometry, "geometry.vtk");
    std::vector<float> refPoint(3);
    refPoint[0] = (float)1.0;
    refPoint[1] = (float)2.0;
    refPoint[2] = (float)3.0;
    res &= test("point", tPoint, refPoint);
    res &= test("region", tRegion, refPoint);
    std::vector< std::vector<float> > refFloatVectors(0);
    res &= test("points", tPoints, refFloatVectors);
    
    // FAILURE
    if(!res)
    {
        std::cerr << "Test #0 FAILED: all parameters are not passed correctly." << std::endl;
        return EXIT_FAILURE;
    }

    // SUCCESS
    std::cout << "Test #0 PASSED: all parameters are passed correctly." << std::endl;
    return EXIT_SUCCESS;
}
