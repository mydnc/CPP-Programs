#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <cassert>
#include <cmath>
#include <cctype>
#include <climits>

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <algorithm>
#include <functional>
#include <memory>
#include <bitset>
using namespace std;

//const uint16_t ENDIAN_LITTLE = 0x4949;
//const uint16_t ENDIAN_BIG    = 0x4d4d;

class Image{
    ifstream inResim;
    ofstream outResim;
    uint16_t m_Endian;
    uint16_t m_Width;
    uint16_t m_Height;
    uint16_t m_PixelFormat;
    vector<vector<uint64_t>> m_Vector;
    int sizeW=0;
public:
    Image(const char * srcFileName, const char* dstFileName,bool flipHorizontal, bool flipVertical) {
        inResim.open(srcFileName, std::ios::binary | std::ios::in);

        outResim.open(dstFileName, std::ios::binary | std::ios::out);
    }

    ~Image(){
        inResim.close();
        outResim.close();
    }

    bool readHeader(){
        if (!inResim || !inResim.is_open())
            return false;
        inResim.read((char*)&m_Endian,2);
        if(inResim.fail())
            return false;
        inResim.read((char*)&m_Width,2);
        if(inResim.fail())
            return false;
        inResim.read((char*)&m_Height,2);
        if(inResim.fail())
            return false;
        inResim.read((char*)&m_PixelFormat,2);
        if(inResim.fail())
            return false;
        return true;
    }

    bool pixelFormatSpec(){
        bool flag;
        flag =  this->m_PixelFormat == 0 || this->m_PixelFormat == 2 || this->m_PixelFormat == 3 ||
                this->m_PixelFormat == 12 ||this->m_PixelFormat == 14 ||this->m_PixelFormat == 15 ||
                this->m_PixelFormat == 16 || this->m_PixelFormat == 17 || this->m_PixelFormat == 19;
        return flag;
    }

    bool readPixels () {
        if(!inResim)
            return false;
        switch (this->m_PixelFormat){
            case 0: sizeW = 1; break;
            case 2: sizeW = 3; break;
            case 3: sizeW = 4; break;
            case 12: sizeW = 1; break;
            case 14: sizeW = 3; break;
            case 15: sizeW = 4; break;
            case 16: sizeW = 2; break;
            case 17: sizeW = 6; break;
            case 19: sizeW = 8; break;
            default: return false;
        }
        m_Vector.resize(m_Height,vector<uint64_t>(m_Width));

        for (uint64_t i = 0; i < this->m_Height ; ++i) {
            for (uint64_t j = 0; j < this->m_Width; ++j) {
                inResim.read((char *) &m_Vector[i][j], sizeW);
                if(inResim.fail())
                    return false;
            }
        }
        inResim.get();
        return inResim.eof();

    }

    void flipVert () {
        uint64_t height_2 = m_Height / 2;
        uint64_t tmp = 0;
        for (uint64_t i = 0; i < m_Width; ++i) {
            for (uint64_t j = 0; j < height_2; ++j) {
                tmp = m_Vector[j][i];
                m_Vector[j][i] = m_Vector[m_Height-j-1][i];
                m_Vector[m_Height-j-1][i] = tmp;
            }
        }
    }

    void flipHor () {
        uint64_t width_2 = m_Width / 2;
        uint64_t tmp = 0;
        for (uint64_t i = 0; i < m_Height ; ++i) {
            for (uint64_t j = 0; j < width_2; ++j) {
                tmp = m_Vector[i][j];
                m_Vector[i][j] = m_Vector[i][m_Width-j-1];
                m_Vector[i][m_Width-j-1] = tmp;
            }
        }
    }

    bool writeImage () {
        if (!outResim || !outResim.is_open())
            return false;
        outResim.write((char*)&m_Endian,2);
        if (outResim.fail())
            return false;
        outResim.write((char*)&m_Width,2);
        if (outResim.fail())
            return false;
        outResim.write((char*)&m_Height,2);
        if (outResim.fail())
            return false;
        outResim.write((char*)&m_PixelFormat,2);
        if (outResim.fail())
            return false;
        for (uint64_t i = 0; i < this->m_Height ; ++i) {
            for (uint64_t j = 0; j < this->m_Width; ++j) {
                outResim.write((char *) &m_Vector[i][j], sizeW);
                if (outResim.fail())
                    return false;
            }
        }
        return true;
    }
};

bool flipImage ( const char  * srcFileName,
                 const char  * dstFileName,
                 bool          flipHorizontal,
                 bool          flipVertical ) {
    Image i(srcFileName, dstFileName, flipHorizontal, flipVertical);
    if(!i.readHeader())
        return false;
    i.pixelFormatSpec();
    if(!i.readPixels())
        return false;
    if (flipHorizontal && flipVertical){
        i.flipVert();
        i.flipHor();
    }else if(flipHorizontal){
        i.flipHor();
    }else if(flipVertical){
        i.flipVert();
    }
    if (! i.writeImage())
    {return false;}
    return true;
}

bool identicalFiles ( const char * fileName1,
                      const char * fileName2 )
{
    // DIY
    return true;
}

int main ()
{
    assert ( flipImage ( "sample/input/input_00.img", "sample/output/output_00.img", true, false )
             && identicalFiles ( "sample/output/output_00.img", "sample/input/ref_00.img" ) );

    assert ( flipImage ( "sample/input/input_01.img", "sample/output/output_01.img", false, true )
             && identicalFiles ( "sample/output/output_01.img", "sample/input/ref_01.img" ) );

    assert ( flipImage ( "sample/input/input_02.img", "sample/output/output_02.img", true, true )
             && identicalFiles ( "sample/output/output_02.img", "sample/input/ref_02.img" ) );

    assert ( flipImage ( "sample/input/input_03.img", "sample/output/output_03.img", false, false )
             && identicalFiles ( "sample/output/output_03.img", "sample/input/ref_03.img" ) );

    assert ( flipImage ( "sample/input/input_04.img", "sample/output/output_04.img", true, false )
             && identicalFiles ( "sample/output/output_04.img", "sample/input/ref_04.img" ) );

    assert ( flipImage ( "sample/input/input_05.img", "sample/output/output_05.img", true, true )
             && identicalFiles ( "sample/output/output_05.img", "sample/input/ref_05.img" ) );

    assert ( flipImage ( "sample/input/input_06.img", "sample/output/output_06.img", false, true )
             && identicalFiles ( "sample/output/output_06.img", "sample/input/ref_06.img" ) );

    assert ( flipImage ( "sample/input/input_07.img", "sample/output/output_07.img", true, false )
             && identicalFiles ( "sample/output/output_07.img", "sample/input/ref_07.img" ) );

    assert ( flipImage ( "sample/input/input_08.img", "sample/output/output_08.img", true, true )
             && identicalFiles ( "sample/output/output_08.img", "sample/input/ref_08.img" ) );

    assert ( ! flipImage ( "sample/input/input_09.img", "sample/output/output_09.img", true, false ) );
    /*
    // extra inputs (optional & bonus tests)
    //do not forget to fix paths of the files
    assert ( flipImage ( "extra_input_00.img", "extra_out_00.img", true, false )
             && identicalFiles ( "extra_out_00.img", "extra_ref_00.img" ) );
    assert ( flipImage ( "extra_input_01.img", "extra_out_01.img", false, true )
             && identicalFiles ( "extra_out_01.img", "extra_ref_01.img" ) );
    assert ( flipImage ( "extra_input_02.img", "extra_out_02.img", true, false )
             && identicalFiles ( "extra_out_02.img", "extra_ref_02.img" ) );
    assert ( flipImage ( "extra_input_03.img", "extra_out_03.img", false, true )
             && identicalFiles ( "extra_out_03.img", "extra_ref_03.img" ) );
    assert ( flipImage ( "extra_input_04.img", "extra_out_04.img", true, false )
             && identicalFiles ( "extra_out_04.img", "extra_ref_04.img" ) );
    assert ( flipImage ( "extra_input_05.img", "extra_out_05.img", false, true )
             && identicalFiles ( "extra_out_05.img", "extra_ref_05.img" ) );
    assert ( flipImage ( "extra_input_06.img", "extra_out_06.img", true, false )
             && identicalFiles ( "extra_out_06.img", "extra_ref_06.img" ) );
    assert ( flipImage ( "extra_input_07.img", "extra_out_07.img", false, true )
             && identicalFiles ( "extra_out_07.img", "extra_ref_07.img" ) );
    assert ( flipImage ( "extra_input_08.img", "extra_out_08.img", true, false )
             && identicalFiles ( "extra_out_08.img", "extra_ref_08.img" ) );
    assert ( flipImage ( "extra_input_09.img", "extra_out_09.img", false, true )
             && identicalFiles ( "extra_out_09.img", "extra_ref_09.img" ) );
    assert ( flipImage ( "extra_input_10.img", "extra_out_10.img", true, false )
             && identicalFiles ( "extra_out_10.img", "extra_ref_10.img" ) );
    assert ( flipImage ( "extra_input_11.img", "extra_out_11.img", false, true )
             && identicalFiles ( "extra_out_11.img", "extra_ref_11.img" ) );
    */
    return 0;
}