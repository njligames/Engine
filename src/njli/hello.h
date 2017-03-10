#ifndef HELLO_H
#define HELLO_H

class Hello {
    private:
        int _number;

    public:
        Hello(int number);
        void printHello(void) const;
        // bool DoTheImportThing_assimp( const std::string& pFile);
        int DoTheImportThing_bullet3 (void);
        int DoTheImportThing_glm(void);
        int DoTheImportThing_jsoncpp(void);
        int DoTheImportThing_tinyxml2(void);
};

#endif
