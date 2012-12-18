// Generated CLP header
#include "testcli3CLP.h"

// Using ITK to read images
#include <itkImageRegionConstIterator.h>
#include <itkImageFileReader.h>

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
* CLI test #3: Test that passing data via memory works. See xml for arguments.
* (No external dependencies)
*/
int main (int argc, char *argv[])
{
    // Parse input arguments
    PARSE_ARGS;

    // Check arguments
    bool res = true;

    // Load image
    typedef unsigned char PixelType;
    const unsigned int Dimension = 3;
    typedef itk::Image< PixelType, Dimension > ImageType;
	typedef itk::ImageFileReader< ImageType > ReaderType;
    
    ReaderType::Pointer imageReader = ReaderType::New();
    imageReader->SetFileName( tImage.c_str() );

    // Image type
    imageReader->UpdateOutputInformation();
    itk::ImageIOBase::IOPixelType pixelType = imageReader->GetImageIO()->GetPixelType();
    itk::ImageIOBase::IOComponentType componentType = imageReader->GetImageIO()->GetComponentType();
    res &= test("pixel type", pixelType, itk::ImageIOBase::SCALAR);
    res &= test("data type", componentType, itk::ImageIOBase::UCHAR);
    // Fail now otherwise the read will crash
    if(!res)
    {
        std::cerr << "Test #3 FAILED: image passed via memory was not passed correctly." << std::endl;
        return EXIT_FAILURE;
    }
 
    ReaderType::Pointer refImageReader = ReaderType::New();
    refImageReader->SetFileName( tRefImage.c_str() );

    // run pipeline
    try
    {
        imageReader->Update();
        refImageReader->Update();
    }
    catch( itk::ExceptionObject & err )
    {
        std::cerr << "ExceptionObject caught !" << std::endl;
        std::cerr << err << std::endl;
        return EXIT_FAILURE;
    }
    catch( ... )
    {
        std::cerr << "ExceptionObject caught !" << std::endl;
        return EXIT_FAILURE;
    }

    ImageType::ConstPointer image = imageReader->GetOutput();
    ImageType::ConstPointer refImage = refImageReader->GetOutput();
    
    // size
    const itk::ImageRegion< Dimension >::SizeType imageSize = 
        image->GetLargestPossibleRegion().GetSize();
    const itk::ImageRegion< Dimension >::SizeType refImageSize = 
        refImage->GetLargestPossibleRegion().GetSize();
    res &= test("number of colums", imageSize[0], refImageSize[0]);
    res &= test("number of rows", imageSize[1], refImageSize[1]);
    res &= test("number of slices", imageSize[2], refImageSize[2]);
    
    // spacing
    res &= test("column spacing", image->GetSpacing()[0], 
        refImage->GetSpacing()[0]);
    res &= test("row spacing", image->GetSpacing()[1], 
        refImage->GetSpacing()[1]);
    res &= test("slice spacing", image->GetSpacing()[2], 
        refImage->GetSpacing()[2]);

    // rescale slope and intercept
    // TODO find an image with a non standard slope / intercept
    //res &= test("slope", image->scl_slope, (float)0.0);
    //res &= test("intercept", image->scl_inter, (float)0.0);
    
    // data type
    //res &= test("data type", image->datatype, NIFTI_TYPE_UINT8);

    // data
    itk::ImageRegionConstIterator< ImageType > itImage( image, image->GetRequestedRegion() );
    itk::ImageRegionConstIterator< ImageType > itRefImage( refImage, refImage->GetRequestedRegion() );
    unsigned int i = 0;
    for( itImage.GoToBegin(), itRefImage.GoToBegin(); !itImage.IsAtEnd();
        ++itImage, ++itRefImage )
    {
        std::ostringstream oss;
        oss << "image data at i=" << i++;
        res &= test(oss.str(), itImage.Get(), itRefImage.Get());
        if( !res )
        {
            break;
        }
    }

    // FAILURE
    if(!res)
    {
        std::cerr << "Test #3 FAILED: image passed via memory was not passed correctly." << std::endl;
        return EXIT_FAILURE;
    }

    // SUCCESS
    std::cout << "Test #3 PASSED: image passed via memory was passed correctly." << std::endl;
    return EXIT_SUCCESS;
}
