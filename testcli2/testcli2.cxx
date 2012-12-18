// Generated CLP header
#include "testcli2CLP.h"

#include <nifti1_io.h>

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

} // anonymous namespace

/**
* CLI test #2: ... See xml for arguments.
* (No external dependencies)
*/
int main (int argc, char *argv[])
{
    // Parse input arguments
    PARSE_ARGS;

    // Load image
    nifti_image* image = nifti_image_read(tImage.c_str(),true);
    if( !image )
    {
        std::cerr << "Test #2 FAILED: could not load the input image." << std::endl;
        return EXIT_FAILURE;
    }

    nifti_image* refImage = nifti_image_read(tRefImage.c_str(),true);
    if( !refImage )
    {
        std::cerr << "Test #2 FAILED: could not load the reference input image." << std::endl;
        return EXIT_FAILURE;
    }

    // Check arguments
    bool res = true;

    // size
    res &= test("number of colums", image->nx, refImage->nx);
    res &= test("number of rows", image->ny, refImage->ny);
    res &= test("number of slices", image->nz, refImage->nz);
    
    // spacing
    res &= test("column spacing", image->dx, refImage->dx);
    res &= test("row spacing", image->dy, refImage->dy);
    res &= test("slice spacing", image->dz, refImage->dz);
    
    // rescale slope and intercept
    // TODO find an image with a non standard slope / intercept
    //res &= test("slope", image->scl_slope, refImage->scl_slope);
    //res &= test("intercept", image->scl_inter, refImage->scl_inter);
    
    // data type
    res &= test("data type", image->datatype, refImage->datatype);

    // data
    unsigned int index = 0;
    unsigned char value = 0;
    unsigned char refValue = 0;
    for(unsigned int i=0; i < image->dx*image->dx*image->dy; ++i)
    {
        value = *((unsigned char*)(image->data) + i);
        refValue = *((unsigned char*)(refImage->data) + i);
        res &= test("image data", value, refValue);
        if( !res )
        {
            break;
        }
    }

    // clean
    nifti_image_free( image );
    nifti_image_free( refImage );

    // FAILURE
    if(!res)
    {
        std::cerr << "Test #2 FAILED: images were not passed correctly." << std::endl;
        return EXIT_FAILURE;
    }

    // SUCCESS
    std::cout << "Test #2 PASSED: images were passed correctly." << std::endl;
    return EXIT_SUCCESS;
}
