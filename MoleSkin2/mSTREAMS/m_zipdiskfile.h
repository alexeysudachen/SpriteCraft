
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

#if !defined m_zipdiskfile_h
#define m_zipdiskfile_h

#include "../mcore/m_core.h"
//#include "../mUTIL/m_stringkey.h"
#include "m_istream.h"

NAMESPACE_MSKIN_BEGIN

class ZipInputSubStream;
/**
  \class ZipDiskFile
  \brief ����� ������������� ������ � ��� ������ ��� ������ � ���������� �������
*/
class ZipDiskFile : public IRefObject, private refbase {
public:
  virtual void Release_() const;
  virtual void Grab_() const;
  struct STATS{
    u32_t packed_size;    ///< ������ ������ � ������
    u32_t unpacked_size;  ///< ��������� ������ � ������
    u32_t date;           ///< ���� ������
    bool    compressed;     ///< ���� ���� ����� �� ������
  };
  ZipDiskFile();
  ~ZipDiskFile();
  /// ������� ����� �������� ���� ��� ������ ������
  SCERROR Create(pwide_t fname,bool failIfExists = false);
  /// �������� ������������ �����
  SCERROR Open(pwide_t fname,bool createIfNotExists = false);
  /// ��������� ������������ ����� , ������ ��� ������
  SCERROR OpenRO(pwide_t fname);
  /// ��������� ������������ ����� ����� �����, ������ ��� ������
  /// ����� ������ ������������ Reset � Skip
  SCERROR OpenRO(InputStreamEx* ra_stream);
  /// ��������� �����
  SCERROR Close();
  /// ���������� ����� � �����
  SCERROR PackStreamInplace(pwide_t fname,InputStream* stream,u32_t level);
  /// ��������� ��� ������ ����� �� ������
  SCERROR ExtractStream(pwide_t fname,InputStreamEx** stream);
  /// ���������� � ������ � ������
  SCERROR GetStats(pwide_t fname,STATS& stats);
  /// ������������ ���� ������� � ������
  SCERROR Enumerate(BufferT<widestring>& e);
private:
  SCERROR ParseZipHeader();
  SCERROR CreateZipHeader();
  SCERROR ReadBuffer_(byte_t* buff,u32_t* sz);
  SCERROR ReadBuffer(byte_t* buff,u32_t sz);
  SCERROR ReadLongFd(u32_t* val);
  SCERROR ReadShortFd(u16_t* val);
  SCERROR SeekFd(long pos,int seek_set);
  SCERROR SearchCentralDirectory(u32_t* pos);
  SCERROR LoadCentralDirectory(u32_t pos);
  SCERROR StoreCentralDirectory(u32_t pos);
  u32_t WasReadFd();
  void InvalidateAllStreams();
  struct RECORD {
    u16_t version;
    u16_t extract_version;
    u16_t bits_flags;
    u16_t compress_method;
    u16_t last_mod_time;
    u16_t last_mod_date;
    u32_t  crc32_val;
    u32_t  compressed_sz;
    u32_t  uncompressed_sz;
    u16_t fname_length;
    u16_t extra_length;
    u16_t comment_length;
    u16_t disk_skip;
    u16_t internal_attr;
    u32_t  external_attr;
    u32_t  rel_offset;
    widestring fname;
  };
  typedef CollectionT<RECORD> RECMAP;
  RECMAP records_;
  widestring zipfile_;
  bool roMode_;
  u32_t centraldir_;
  FILE* fd_;
  FlatsetT<ZipInputSubStream*> substreams_;
  friend class ZipInputSubStream;
  void ForgetAbout(ZipInputSubStream*);
};

NAMESPACE_MSKIN_END

#endif // m_zipdiskfile_h

