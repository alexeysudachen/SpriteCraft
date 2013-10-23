
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

#ifndef ___e42797bb_337d_4def_8fc2_f49be0bdbd70___
#define ___e42797bb_337d_4def_8fc2_f49be0bdbd70___

enum { SCRAFT_MAX_TEXTURE_WIDTH = 512 };

enum SPRITE_IMAGE_TYPE
  {
    SPRITE_INVALID_TYPE = 0,
    SPRITE_SOLID        = 1,
    SPRITE_BITMASK      = 2,
    SPRITE_COLORKEY     = 3,
    SPRITE_BLEND        = 4,
    SPRITE_ADDITIVE     = 5
  };

enum SPRITE_HOTSPOT
  {
    HOTSPOT_LEFT_TOP      = 0,
    HOTSPOT_CENTER_TOP    = 1,
    HOTSPOT_RIGHT_TOP     = 2,
    HOTSPOT_RIGHT_CENTER  = 3,
    HOTSPOT_RIGHT_BOTTOM  = 4,
    HOTSPOT_CENTER_BOTTOM = 5,
    HOTSPOT_LEFT_BOTTOM   = 6,
    HOTSPOT_LEFT_CENTER   = 7,
    HOTSPOT_CENTER        = 8,
    HOTSPOT_CUSTOM        = 9
  };

struct SpriteColorFilter
  {
    virtual mrgb_t      GetRGB() const = 0;
    virtual void        SetRGB(mrgb_t) = 0;
  };

struct Sprite;
struct SpriteGroupControl;
struct SpriteSubImpl: public virtual IRefObject
  {
    virtual void SetSpritePtr(Sprite*) = 0;
  };

enum SPRITE_DEPS
  {
    SPRITE_DEPS_X             = MSKIN_BIT(0),
    SPRITE_DEPS_Y             = MSKIN_BIT(1),
    SPRITE_DEPS_DEGREE        = MSKIN_BIT(2),
    SPRITE_DEPS_LUMINANCE     = MSKIN_BIT(3),
    SPRITE_DEPS_TRANSPARENCY  = MSKIN_BIT(4),
    SPRITE_DEPS_CFILT         = MSKIN_BIT(5),
    SPRITE_DEPS_XSCALE        = MSKIN_BIT(6),
    SPRITE_DEPS_YSCALE        = MSKIN_BIT(7),
    SPRITE_DEPS_VISIBILITY    = MSKIN_BIT(8),
    SPRITE_DEPS_DISPOSE       = MSKIN_BIT(9)
  };

enum SPRITE_COLLIDE_TYPE
  {
    SPRITE_COLLIDE_RECTANGLE = 0,
    SPRITE_COLLIDE_RADIUS    = 1,
    SPRITE_COLLIDE_BITMASK   = 2
  };

/**
  ��������� �������
*/
struct Sprite : public SpriteColorFilter, public Adaptable
  {
    static  pchar_t const TypeID__;
    virtual void* Adaptate_(const void*);
    virtual SCERROR Show() = 0;
    virtual SCERROR Hide() = 0;
    virtual void        Move(float x,float y) = 0;
    virtual void        MoveX(float x) = 0;
    virtual void        MoveY(float y) = 0;
    virtual void        Rotate(float degree) = 0;
    virtual void        SetAngle(float radians) = 0;
    virtual void        Rescale(float w,float h) = 0;
    virtual void        Scale(float percent) = 0;
    virtual void        ScaleX(float percent) = 0;
    virtual void        ScaleY(float percent) = 0;
    virtual void        SetSizeX(float xsize) = 0;
    virtual void        SetSizeY(float ysize) = 0;
    virtual void        SetHotspotX(float xhsp) = 0;
    virtual void        SetHotspotY(float yhsp) = 0;
    virtual void        SetHotspot(unsigned hsptag) = 0;
    virtual float       GetHotspotX() = 0;
    virtual float       GetHotspotY() = 0;
    virtual float       GetDegee() const = 0;
    virtual float       GetAngle() const = 0;
    virtual float       GetScrAngle() const = 0;
    virtual float       GetX() const = 0;
    virtual float       GetY() const = 0;
    virtual float       GetScrX() const = 0;
    virtual float       GetScrY() const = 0;
    virtual float       GetWidth() const = 0;
    virtual float       GetHeight() const = 0;
    virtual pwide_t     GetKlass() const = 0;
    virtual bool        IsVisible() const = 0;
    virtual pwide_t     GetName()   const = 0;
    virtual void        SetLayer(int) = 0;
    virtual int         GetLayer()  const = 0;
    virtual void        SetSubLayer(int) = 0;
    virtual int         GetSubLayer()  const = 0;
    virtual void        SetFrameNo(int) = 0;
    virtual int         GetFrameNo() const = 0;
    virtual float       GetTransparency() const = 0;
    virtual void        SetTransparency(float percent) = 0;
    virtual float       GetLuminance() const = 0;
    virtual void        SetLuminance(float percent) = 0;
    virtual float       GetScaleX() const = 0;
    virtual float       GetScaleY() const = 0;
    virtual rect_t      GetRect() const = 0;
    virtual void        Dispose() = 0;
    virtual void        SetSubImpl(SpriteSubImpl*) = 0;
    virtual SpriteSubImpl* GetSubImpl() const = 0;
    virtual bool        Contains(float xX,float yY) const = 0;
    virtual void        SetFlipX(bool) = 0;
    virtual void        SetFlipY(bool) = 0;
    virtual bool        IsFlipX() const = 0;
    virtual bool        IsFlipY() const = 0;
    virtual void        SetText(pwide_t text) = 0;
    virtual pwide_t     GetText() const = 0;
    virtual Sprite*     GetParent() const = 0;
    virtual void        SetParent(Sprite*) = 0;
    virtual u32_t     GetParentDeps() const = 0;
    virtual void        SetParentDeps(u32_t) = 0;
    virtual u32_t     GetFrCount() const = 0;
    virtual SPRITE_COLLIDE_TYPE GetCollideType() const = 0;
    virtual SPRITE_IMAGE_TYPE GetImageType() const = 0;
    virtual void        GetRadius(float* r, float* x, float* y) const = 0;
    virtual void        GetRect(float* x, float* y) const = 0;
    virtual bool        Hit(const Sprite*,bool guard=true) const = 0;
    virtual bool        OutOfScreen() const = 0;
    virtual float       Distance(Sprite*) const = 0;
    virtual float       AngleWith(Sprite*) const = 0;
    virtual void        IncAngle(float) = 0;
    virtual void        IncX(float) = 0;
    virtual void        IncY(float) = 0;
    virtual void        SpriteToScreen(float* x,float* y) = 0;
    virtual void        ScreenToSprite(float* x,float* y) = 0;
    virtual bool        ContainsPoint(float* xX,float* yY) const = 0;
    virtual void        GetFullIdent(long* layer,long* sublayer,u32_t* ident) const = 0;
    virtual SCERROR ChangeKlass(pwide_t klass) = 0;
    virtual Sprite*     GetChild(pwide_t key) = 0;
    virtual void        AttachChild(Sprite* child, pwide_t key) = 0;
    virtual bool        TryEnableComplex() = 0;
    virtual bool        TryEnableTriangled() = 0;
    virtual void        DisableComplex() = 0;
    virtual void        DisableTriangled() = 0;
    virtual bool        IsComplex() const = 0;
    virtual bool        IsTriangled() const = 0;
    virtual void        SetTextViewWidth(float width) = 0;
    virtual float       GetTextViewWidth() const = 0;
    virtual void        SetTextViewHeight(float height) = 0;
    virtual float       GetTextViewHeight() const = 0;
    virtual void        SetTextViewBackground(mrgb_t color) = 0;
    virtual mrgb_t      GetTextViewBackground() const = 0;
    virtual void        SetTextViewBorder(long broder) = 0;
    virtual long        GetTextViewBorder() const = 0;
    virtual void        SetTextViewBorderColor(mrgb_t color) = 0;
    virtual mrgb_t      GetTextViewBorderColor() const = 0;
    virtual void        SetTextViewScrollX(float xOffset) = 0;
    virtual float       GetTextViewScrollX() const = 0;
    virtual void        SetTextViewScrollY(float yOffset) = 0;
    virtual float       GetTextViewScrollY() const = 0;
    virtual void        SetTextViewActive(bool active) = 0;
    virtual bool        IsTextViewActive() const = 0;
    virtual void        SetTextViewColorized(bool active) = 0;
    virtual bool        IsTextViewColorized() const = 0;
    virtual float       GetTextViewMaxScrollX() const = 0;
    virtual float       GetTextViewMaxScrollY() const = 0;
    virtual bool        IsText() const = 0;
    virtual bool        IntersectLine(float x0,float y0, float x1,float y1) const = 0;
    virtual long        GetSymheight() const = 0;
    virtual long        GetParalax() const = 0;
    virtual void        SetParalax( long ) = 0;

  protected:
    Sprite();
    virtual ~Sprite();
  private:
    Sprite(const Sprite&);
    Sprite& operator=(const Sprite&);
  };

inline void Dispose(Sprite*& s)
  {
    if ( s ) s->Dispose();
    s = 0;
  };

struct KlassProvider;
struct SPRITES_Inst;

/**
  ������-�����
*/
struct SPRITES
  {
    // ���� ����� ���������� ������� ����� ������� ������ �� ������-�������
    static IRefObject* Acquire();
    // ���� ����� ���������� ������� � ����� ������ �� ������-�������
    // ��� ����� ������� Release �� ������� ������������ Acquire
    // ��� ��� �������� ��������� �����������
    static void        Release();
    // ��������������� ��������� �����������
    static SCERROR Restore();
    // ���������� ��� ������� ���� � �������� ���������
    static SCERROR Display();
    /// ������� ��� ���������� � ������� � ��������
    static SCERROR Purge();
    /// ������� ����� ����� ������������� ��������
    static SCERROR NewKlass(pwide_t klass);
    /// ������� ����� ����� - ��������
    static SCERROR NewDummyKlass(pwide_t klass,bool renderable = false);
    /// ������� ����� ����� ��������� ��������
    static SCERROR NewFontKlassFrom(pwide_t fntklass,pwide_t resource,
      bool filtering,pwide_t symbols,SPRITE_IMAGE_TYPE t,long ckey);
    /// ����������� (���������) ������� ������,
    /// ���� �� ������������ � ����������������� �� ����������
    static SCERROR UnloadKlass(pwide_t klass,bool = false);
    /// ������������/��������� ������� �������
    static SCERROR RestoreKlass(pwide_t klass);
    /// ��������� ������������� ������ ��������
    static bool        HasKlass(pwide_t klass);
    /// ������� ����� (���������) ������ ���������� ������
    static Sprite*     NewSprite(pwide_t name,pwide_t klass,int layer);
    /// ������� ����� (�������) ������ ���������� ������ � ����������� x,y
    static Sprite*     NewSprite(pwide_t name,pwide_t klass,int layer,int x,int y);
    //  ������� ������
    static Sprite*     NewSpriteFrom(
      pwide_t name,pwide_t resource,
      int layer,int hno,int vno,
      bool filtering,
      bool cmprs,
      SPRITE_IMAGE_TYPE,long =0);
  //  /// ������� ����� (�������) ����� ������
  //  static TileMap*    NewTileMap(pwide_t name,unsigned rows,unsigned columns,unsigned tileSize,int layer);
  //  /// ������� ������� ������
  //  static Particles*  NewParticles(pwide_t name,pwide_t klass,int layer);
  //  /// ������� ������ ����������� ��������
  //  static LwsArray*   NewLwsArray(pwide_t name,pwide_t klass,int layer);
    /// ���������� ������
    static SCERROR DisposeSprite(pwide_t name);
  //  /// ���������� �������� �����
  //  static SCERROR DisposeTileMap(pwide_t name);
  //  /// ���������� ������� ������
  //  static SCERROR DisposeParticles(pwide_t name);
    /// ���������� ������ ����������� ��������
    static SCERROR DisposeLwsArray(pwide_t name);
    /// ������� ������ �� �����
    static Sprite*     FindSprite(pwide_t name);
  //  /// ������� ������� �� �����
  //  static TileMap*    FindTileMap(pwide_t name);
  //  /// ������� ������� ������
  //  static Particles*  FindParticles(pwide_t name);
  //  /// ������� ������ ����������� ��������
  //  static LwsArray*   FindLwsArray(pwide_t name);
  //  /// ������� ��������� ������ � ��������� �����������,
    /// � ������ ��������������� � �������� ��������
    static Sprite*     FindSpriteAt(long x,long y,long nearlayer,long farlayer);
    //  ������������� ���� ������������� ����������
    static void        SetNeedRefresh(bool val = true);
    //  ���������� ���� ������������� ����������
    static bool        NeedRefresh();
    //  ����������� �������
    static SCERROR EnumerateSprites(ArrayT<Sprite*>&,long lnear = LONG_MIN,long lfar = LONG_MAX);
  //  //  ����������� ���� �����
  //  static SCERROR EnumerateTileMaps(vector<TileMap*>&);
  //  static SCERROR EnumerateParticles(vector<Particles*>&);
    static void    SetLayerX(long no,float val);
    static void    SetLayerY(long no,float val);
    static void    SetLayerVisibility(long no,bool val);
    static float   GetLayerX(long no);
    static float   GetLayerY(long no);
    static bool    IsLayerVisible(long no);
    static SCERROR NewDynamicKlass(pwide_t klass,KlassProvider*);
    static SCERROR UpdateKlass(pwide_t name);
    static SCERROR UnloadAll();
  private:
    friend struct SPRITES_Inst;
    static SPRITES_Inst* instance_;
  };

#endif // ___e42797bb_337d_4def_8fc2_f49be0bdbd70___
