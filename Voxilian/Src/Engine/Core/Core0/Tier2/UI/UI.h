#ifndef H_UI
#define H_UI
#include "..\..\Globals.h"
#include "..\..\Tier1\Tier1.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef __OPENGL_IMAGE_LOADER_DEVIL__
#define __OPENGL_IMAGE_LOADER_DEVIL__
 
#include <algorithm>
#include <cctype>
#include <cstdlib>
 
#include <mygui\MyGUI_DataManager.h>
#include <mygui\MyGUI_OpenGLImageLoader.h>
 
#include <IL\il.h>
 
class OpenGLImageLoader_Devil : public MyGUI::OpenGLImageLoader
{
public:
    OpenGLImageLoader_Devil() :
        MyGUI::OpenGLImageLoader()
    {
        // Take this out of here if you initialise DevIL elsewhere
        ilInit();
    }
 
	virtual ~OpenGLImageLoader_Devil()
    {
    }
 
    void* loadImage(
        int& _width, 
        int& _height, 
        MyGUI::PixelFormat& _format, 
        const std::string& _filename)
    {
        // Generate an image name and bind it so we can use it
        ILuint image;
        ilGenImages(1, &image);
        ilBindImage(image);
 
        // Load the image as a resource
        MyGUI::IDataStream* stream = MyGUI::DataManager::getInstancePtr()->getData(_filename);
        size_t lumpSize = stream->size();
        void* lumpData = malloc(lumpSize);
        stream->read(lumpData, lumpSize);
 
#ifdef _UNICODE
        // Convert filename to a std::wstring
        std::wstring filename(_filename.length(), L' ');
        std::copy(_filename.begin(), _filename.end(), filename.begin());
#else
        std::string filename = _filename;
#endif
 
        // Try to determine the image type
        ILenum imageType = ilDetermineType(filename.c_str());
        if (imageType == IL_TYPE_UNKNOWN)
        {
            imageType = ilDetermineTypeL(lumpData, lumpSize);
        }
 
        // Try to load the image
        if (ilLoadL(imageType, lumpData, lumpSize) == IL_FALSE)
        {
            free(lumpData);
            return 0;
        }
 
        free(lumpData);
 
        // Retrieve image information
        _width = ilGetInteger(IL_IMAGE_WIDTH);
        _height = ilGetInteger(IL_IMAGE_HEIGHT);
        ILenum format = ilGetInteger(IL_IMAGE_FORMAT);
        ILenum type = ilGetInteger(IL_IMAGE_TYPE);
 
        // If the format is not supported, convert to a supported format
        // Also convert if the pixel type is not unsigned byte
        ILenum convertToFormat = format;
 
        switch (format)
        {
        case IL_COLOUR_INDEX: convertToFormat = IL_RGB; break;
        case IL_ALPHA: convertToFormat = IL_LUMINANCE_ALPHA; break;
        case IL_BGR: convertToFormat = IL_RGB; break;
        case IL_BGRA: convertToFormat = IL_RGBA; break;
        default: break;
        }
 
        if ((convertToFormat != format) || (type != IL_UNSIGNED_BYTE))
        {
            if (ilConvertImage(convertToFormat, IL_UNSIGNED_BYTE) == IL_FALSE)
            {
                return 0;
            }
        }
 
        // Determine MyGUI pixel formats
        switch (format)
        {
        case IL_RGB: _format = MyGUI::PixelFormat::R8G8B8; break;
        case IL_RGBA: _format = MyGUI::PixelFormat::R8G8B8A8; break;
        case IL_LUMINANCE: _format = MyGUI::PixelFormat::L8; break;
        case IL_LUMINANCE_ALPHA: _format = MyGUI::PixelFormat::L8A8; break;
        default: _format = MyGUI::PixelFormat::Unknow; break;
        }
 
        // Copy the image data into some new memory
        ILint size = ilGetInteger(IL_IMAGE_SIZE_OF_DATA);
        void* _data = malloc(size);
        ILubyte* data = ilGetData();
        memcpy(_data, data, size);
 
        return _data;
    }
};
 
#endif // __OPENGL_IMAGE_LOADER_DEVIL__
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CUIImageLoader : public OpenGLImageLoader_Devil
{
public:
	//virtual void* loadImage(int& _width, int& _height, MyGUI::PixelFormat& _format, const std::string& _filename);
	virtual void saveImage(int _width, int _height, MyGUI::PixelFormat _format, void* _texture, const std::string& _filename);
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Panel
{
public:
	btTransform trans;
	Panel()
	{
		trans.setOrigin(btVector3(0,0,0));
		trans.setRotation(btQuaternion(0,0,0));
	}
};
class CUI
{
public:
	MyGUI::Gui* ui;
	MyGUI::LogManager* logger;
	MyGUI::OpenGLPlatform* platform;
	OpenGLImageLoader_Devil* loader;
	CUI();
	void Init();
	void Update();
	void Render();
	void CursorToggle();
	void CursorShow();
	void CursorHide();
	bool CursorVisible();
	void CursorWindowsToggle();
	void CursorWindowsShow();
	void CursorWindowsHide();
	bool CursorWindowsVisible();
};
void InjectInput(InputStruct in);
extern CUI UI;

#endif