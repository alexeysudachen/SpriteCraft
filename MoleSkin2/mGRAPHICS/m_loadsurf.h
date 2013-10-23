
/*

Copyright © 2003-2013, Alexéy Sudachén, alexey@sudachen.name

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

#include "../mcore/m_autoconf.h"
#include "m_surface.h"
#include "m_color.h"
#include "../mstreams/m_dsource.h"

#if !defined __m_loadsurf_h__
#define __m_loadsurf_h__

NAMESPACE_MSKIN_BEGIN

/// ����� ������ ��� �������� �����������
class ImageDataSource : public StreamedDataSource {
public:
  /// �������� �����������
  struct ImageInfo{
    int width;              /// ������ ����������� � ��������
    int height;             /// ������ ����������� � ��������
    int stride;             /// ������ ������ �������� � ������
    int bpp;                /// ������� ����� 8/16/24/32
    bool updown;            /// ������� ������ ����� ����� �����
    bool alphabits;         /// ������� ������� ����������
    bool shortgreen;        /// ��� 16��� , �������� ������� ����������
    int palsize;            /// ���������� ������������ ��������� �������
    int frames;             /// ���������� ������ � ��������
    BufferT<mrgba_t> pal;    /// ��� ����������, ������� �����������
    BufferT<float> duration; /// ��� ��������, ������������ ������
  };
  /// ������ ��������� �����������
  virtual SCERROR ReadPicInfo (ImageInfo&) = 0;
  /// ������ ������ ��������
  /// ������ �������� ���������� ������� � ������� BGRA
  /// ��� ������������ ����������� 32/24 ������ ������� 888[8] 
  /// ��� 16-������ ����������� ������ ������� 565 ��� 555 ���� ���������� shortgreen
  /// ���� ���������� alphabits �� ������ �������� ����������
  virtual SCERROR ReadRow(BufferT<byte_t>& row) = 0;
protected:
  ImageDataSource(DataSource* ds) : StreamedDataSource(ds){}
  ImageDataSource(InputStreamEx* is, pwide_t name = L"<unknown>") : StreamedDataSource(is,name){}
  virtual ~ImageDataSource() {}
};
typedef auto_ref<ImageDataSource> AutoImageDataSource;

/// ��������� ����������� �� �������
SCERROR MOLE_FUNCALL LoadSurfaceFrom(pwide_t source,Surface* surf);

/// ��������� ����������� �� �������
/// ���� ������� �� ������, �� ������� ����������� ������� � ��������� ��������
SCERROR MOLE_FUNCALL LoadSurfaceFrom(pwide_t source,AutoSurface& surf,unsigned format);

/// ��������� ����������� �� �������
SCERROR MOLE_FUNCALL LoadSurfaceFrom(DataSource* ds,Surface* surf);

/// ��������� ����������� �� �������
/// ���� ������� �� ������, �� ������� ����������� ������� � ��������� ��������
SCERROR MOLE_FUNCALL LoadSurfaceFrom(DataSource* ds,AutoSurface& surf,unsigned format);

/// ��������� ����������� �� �������
/// ���� ������� �� ������, �� ������� ����������� ������� � ��������� ��������
SCERROR MOLE_FUNCALL LoadSurfaceFrom(ImageDataSource* ds,AutoSurface& surf,unsigned fmt);

/// ������� ������� �� ���� �����������
Surface*    MOLE_FUNCALL CreateSurfaceFrom(DataSource*,unsigned = Surface::PREFERRED);

/// ������� ������� �� ���� �����������
Surface*    MOLE_FUNCALL CreateSurfaceFrom(pwide_t resname,unsigned fmt = Surface::PREFERRED);

/// ������� ����� ������ ��� �������� ����������� � ������� MS BMP
ImageDataSource* MOLE_FUNCALL MakeBMPImageDataSource(DataSource*);
ImageDataSource* MOLE_FUNCALL MakeTGAImageDataSource(DataSource*);
ImageDataSource* MOLE_FUNCALL MakeJPGImageDataSource(DataSource*);
ImageDataSource* MOLE_FUNCALL MakePNGImageDataSource(DataSource*);
ImageDataSource* MOLE_FUNCALL MakeTAFImageDataSource(DataSource*);

/// ���������� ������ ����������� � ������� ����� ������ ��� ��������
ImageDataSource* MOLE_FUNCALL MakeImageDataSourceFrom(DataSource*);

typedef ImageDataSource* (__cdecl *LPFN_IMAGING)(DataSource*);
SCERROR MOLE_FUNCALL AddImagingEXT(LPFN_IMAGING cb);
SCERROR MOLE_FUNCALL RemoveImagingEXT(LPFN_IMAGING cb);


NAMESPACE_MSKIN_END

#endif // __m_loadsurf_h__
