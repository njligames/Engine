#include "hello.h"
#include <iostream>


#include "assimp/Importer.hpp"      // C++ importer interface
#include "assimp/scene.h"           // Output data structure
#include "assimp/postprocess.h"     // Post processing flags

#include "btBulletCollisionCommon.h"

#include "glm/glm.hpp"

#include "json/value.h"

#include "tinyxml2.h"

Hello::Hello(int number)
    : _number(number) {
}

void Hello::printHello(void) const {
    std::cout << "Hello, " << this->_number << std::endl;
}

// bool Hello::DoTheImportThing_assimp( const std::string& pFile)
// {
//   // Create an instance of the Importer class
//   Assimp::Importer importer;
//   // And have it read the given file with some example postprocessing
//   // Usually - if speed is not the most important aspect for you - you'll 
//   // propably to request more postprocessing than we do in this example.
//   const aiScene* scene = importer.ReadFile( pFile, 
//         aiProcess_CalcTangentSpace       | 
//         aiProcess_Triangulate            |
//         aiProcess_JoinIdenticalVertices  |
//         aiProcess_SortByPType);
  
//   // If the import failed, report it
//   if( !scene)
//   {
//     // DoTheErrorLogging( importer.GetErrorString());
//     return false;
//   }
//   // Now we can access the file's contents. 
//   // DoTheSceneProcessing( scene);
//   // We're done. Everything will be cleaned up by the importer destructor
//   return true;
// }

int Hello::DoTheImportThing_bullet3 (void)
{

        //btVector3 fallInertia(0, 0, 0);

        return 0;
}
int Hello::DoTheImportThing_glm(void)
{
	//glm::vec4 Position = glm::vec4(glm::vec3(0.0), 1.0);
	//glm::mat4 Model = glm::mat4(1.0);
	//Model[4] = glm::vec4(1.0, 1.0, 0.0, 1.0);
	//glm::vec4 Transformed = Model * Position;
	return 0;
}

int Hello::DoTheImportThing_jsoncpp(void)
{
	//Json::Value root;   // starts as "null"; will contain the root value after parsing
	return 0;
}

int Hello::DoTheImportThing_tinyxml2(void)
{
	//tinyxml2::XMLDocument doc;
    //doc.LoadFile( "dream.xml" );

    // Structure of the XML file:
    // - Element "PLAY"      the root Element, which is the 
    //                       FirstChildElement of the Document
    // - - Element "TITLE"   child of the root PLAY Element
    // - - - Text            child of the TITLE Element

    // Navigate to the title, using the convenience function,
    // with a dangerous lack of error checking.
    //const char* title = doc.FirstChildElement( "PLAY" )->FirstChildElement( "TITLE" )->GetText();
    //printf( "Name of play (1): %s\n", title );

    // Text is just another Node to TinyXML-2. The more
    // general way to get to the XMLText:
    //tinyxml2::XMLText* textNode = doc.FirstChildElement( "PLAY" )->FirstChildElement( "TITLE" )->FirstChild()->ToText();
    //title = textNode->Value();
    //printf( "Name of play (2): %s\n", title );
    return 0;
}
