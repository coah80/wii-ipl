typedef unsigned char u8;
typedef int bool;
typedef struct Vec2 { float x, y; } Vec2;
typedef struct Size { float width, height; } Size;
typedef struct Color { u8 r,g,b,a; } Color;
typedef Vec2 TexCoords[4];
typedef struct Material { u8 (*GetTextureNum)(void); bool (*SetupGX)(bool,u8); } Material;
typedef struct Frame { Material* pMaterial; } Frame;
typedef struct WindowFrameSize { float l,r,t,b; } WindowFrameSize;
extern Size mSize;
extern int GX_TEXMAP0, GX_TEXMAP1, VERTEXCOLOR_MAX, NULL;
extern int TEXTUREFLIP_NONE, TEXTUREFLIP_H, TEXTUREFLIP_180, TEXTUREFLIP_V;
bool IsModulateVertexColor(const Color*,u8);
Size GetTextureSize(Material*,u8);
void SetVertexFormat(bool,u8);
void DrawQuad(Vec2,Size,u8,const TexCoords*,const Color*,u8);
void GetLTFrameSize(Vec2*,Size*,Vec2,Size,WindowFrameSize);
void GetLTTexCoord(TexCoords,Size,Size,u8);
void GetRTFrameSize(Vec2*,Size*,Vec2,Size,WindowFrameSize);
void GetRTTexCoord(TexCoords,Size,Size,u8);
void GetRBFrameSize(Vec2*,Size*,Vec2,Size,WindowFrameSize);
void GetRBTexCoord(TexCoords,Size,Size,u8);
void GetLBFrameSize(Vec2*,Size*,Vec2,Size,WindowFrameSize);
void GetLBTexCoord(TexCoords,Size,Size,u8);
void DrawFrame(const Vec2 basePt, const Frame frame, const WindowFrameSize frameSize, u8 alpha)
{
            if (frame.pMaterial->GetTextureNum() == GX_TEXMAP0) {
                return;
            }
            const bool bUseVtxCol = frame.pMaterial->SetupGX(IsModulateVertexColor(NULL, alpha), alpha);
            SetVertexFormat(bUseVtxCol, GX_TEXMAP1);
            const Size texSize = GetTextureSize(frame.pMaterial, GX_TEXMAP0);
            const Color vtxColors[VERTEXCOLOR_MAX];
            TexCoords texCds[1];
            Vec2 polPt;
            Size polSize;
            { GetLTFrameSize(&polPt, &polSize, basePt, mSize, frameSize); GetLTTexCoord(*texCds, polSize, texSize, TEXTUREFLIP_NONE); DrawQuad(polPt, polSize, GX_TEXMAP1, texCds, bUseVtxCol ? vtxColors : NULL, alpha); };
            { GetRTFrameSize(&polPt, &polSize, basePt, mSize, frameSize); GetRTTexCoord(*texCds, polSize, texSize, TEXTUREFLIP_H); DrawQuad(polPt, polSize, GX_TEXMAP1, texCds, bUseVtxCol ? vtxColors : NULL, alpha); };
            { GetRBFrameSize(&polPt, &polSize, basePt, mSize, frameSize); GetRBTexCoord(*texCds, polSize, texSize, TEXTUREFLIP_180); DrawQuad(polPt, polSize, GX_TEXMAP1, texCds, bUseVtxCol ? vtxColors : NULL, alpha); };
            { GetLBFrameSize(&polPt, &polSize, basePt, mSize, frameSize); GetLBTexCoord(*texCds, polSize, texSize, TEXTUREFLIP_V); DrawQuad(polPt, polSize, GX_TEXMAP1, texCds, bUseVtxCol ? vtxColors : NULL, alpha); };
        }
