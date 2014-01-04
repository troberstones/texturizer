#ifndef TILE_H
#define TILE_H

#include <map>
#include <string>
#include <vector>
#include <QVariant>
#include <iostream>

class item {
public:
    // Commend out for now, as I need to pass in consts to test
    //item(float &inx, float &iny, float &inz, float &width, float &height, float &rot);
    item(float inx, float iny, float inz, float width, float height, float rot);
    ~item();
    void setTile  (const float &inx, const float &iny, const float &inz, const float &inw, const float &inh, const float &inrot);
    //void scale    (const float &x, const float &y);
    //void rotate   (const float &x);
    //void jitter   (const float &x, const float &y);
    bool intersect(const float &testX, const float &testY, float &hitS, float &hitT);

    //int id;
    float x;
    float y;
    float z;

    float w;
    float h;

    float r;
    float g;
    float b;

    float rotate;
};


class Tile
{
public:
    typedef std::vector<item> ItemArray;

    enum kTilemode {
        kRandUniform,
        kRandGaussian,
        kUniform,
    };
    Tile();
    Tile(std::string name);
    void SetTileMode(kTilemode mode)          { m_mode = mode;}
    void SetCount(size_t count)               { m_tileCount = count;}
    //TODO: handle maps
    void SetMemo  (std::string memo)          { m_memo= memo;}
    void SetName  (std::string name)          { m_name= name;}
    void SetMap   (std::string texture)       { m_texture = texture;}
    void SetJitter(float jitter)              { m_jitter = jitter;}
    void SetScale (float scale)               { m_scale = scale;}
    void SetScaleRange(float range)           { m_scaleRange = range;}
    void SetXScale(float xscale )             { m_xscale = xscale;}
    void SetYScale(float yscale )             { m_yscale = yscale;}
    void SetWidth (float width)               { m_width = width;}
    void SetWidthRange(float range)           { m_widthRange = range;}
    void SetRotate(float rotate)              { m_rotate = rotate;}
    void SetRotateRange(float range)          { m_rotateRange = range;}
    void SetHeight(float height)              { m_height = height;}
    void SetHeightRange(float range)          { m_heightRange = range;}

    ItemArray &GetItemArray()                 { return m_tiles;}
    std::string GetMemo()                     { return m_memo;}
    std::string GetName()                     { return m_name;}
    size_t GetCount()                         { return m_tileCount;}
    float GetJitter()                         { return m_jitter;}
    float GetScale ()                         { return m_scale;}
    float GetScaleRange ()                    { return m_scaleRange;}
    float GetXScale()                         { return m_xscale;}
    float GetYScale()                         { return m_yscale;}
    float GetWidth ()                         { return m_width;}
    float GetWidthRange()                     { return m_widthRange;}
    float GetRotate()                         { return m_rotate;}
    float GetRotateRange()                    { return m_rotateRange;}
    float GetHeight()                         { return m_height;}
    float GetHeightRange()                    { return m_heightRange;}
    std::string GetLabelAtIndex(int index){
        return s_labels[index];
    }
    int GetParamCount(){return s_paramCount;}

    QVariant GetOrEditValueAtIndex(int index, int m=0, QVariant val=NULL)
    {
        QVariant result;
        switch (index) {
        case Count:
            if(m == Fetch)
                result = GetCount();
            else
                SetCount(val.toInt());
            break;
        case Jitter:
            if(m == Fetch)
                result = GetJitter();
            else
                SetJitter(val.toFloat());
            break;
        case Scale:
            if(m == Fetch)
                result = GetScale();
            else
                SetScale(val.toFloat());
            break;
        case ScaleRange:
            if(m == Fetch)
                result = GetScaleRange();
            else
                SetScaleRange(val.toFloat());
            break;
        case XScale:
            if(m == Fetch)
                result = GetXScale();
            else
                SetXScale(val.toFloat());
            break;
        case YScale:
            if(m == Fetch)
                result = GetXScale();
            else
                SetXScale(val.toFloat());
            break;
        case Width:
            if(m == Fetch)
                result = GetWidth();
            else
                SetWidth(val.toFloat());
            break;
        case WidthRange:
            if(m == Fetch)
            result = GetWidthRange();
            else
                SetWidthRange(val.toFloat());
            break;
        case Rotate:
            if(m == Fetch)
                result = GetRotate();
            else
                SetRotate(val.toFloat());
            break;
        case RotateRange:
            if(m == Fetch)
            result = GetRotateRange();
            else
                SetRotateRange(val.toFloat());
            break;
        case Height:
            if(m == Fetch)
                result = GetHeight();
            else
                SetHeight(val.toFloat());
            break;
        case HeightRange:
            if(m == Fetch)
                result = GetHeightRange();
            else
                SetHeightRange(val.toFloat());
            break;
        case Name:
            if(m == Fetch)
                result = GetName().c_str();
            else
                SetName(val.toString().toStdString());
            break;
        case Memo:
            if(m == Fetch)
                result = GetMemo().c_str();
            else
                SetMemo(val.toString().toStdString());
        default:
            break;
        }
        return result;
    }

    // populate the tiles
    void Populate();
    // Loop over each tile and compute the color
    void Sample(const float &x, const float &y);


    enum EEditMode {
        Fetch=0,
        Edit,
    };

    enum ENames {
        Count = 0,
        Jitter,
        Scale,
        ScaleRange,
        XScale,
        YScale,
        Width,
        WidthRange,
        Rotate,
        RotateRange,
        Height,
        HeightRange,
        Name,
        Memo
    };

private:
    void initLabels(){
        char* labels[] = {
                        "Count",
                        "Jitter",
                        "Scale",
                        "ScaleRange",
                        "XScale",
                        "YScale",
                        "Width",
                        "WidthRange",
                        "Rotate",
                        "RotateRange",
                        "Height",
                        "HeightRange",
                        "Name",
                        "Memo"};
        int count =  sizeof(labels)/sizeof(labels[0]);
        std::cout << "Num itesm:" << count << std::endl;
        for(int i = 0; i < count; i++)
        {
            s_labels.push_back(std::string(labels[i]));
        }


        //s_labels = &labels;
        //s_labels.assign((labels, count);
        s_paramCount = count;
    };
    int s_paramCount;
    std::vector<std::string> s_labels;
    // each property has a base value and a
    // range. These valuse will be used to populate
    // the tiles that belong to this node.
    int   m_seed;
    size_t      m_tileCount;
    kTilemode   m_mode;
    std::string m_texture;
    std::string m_name;
    std::string m_memo;

    float m_rotate;
    float m_rotateRange;

    float m_scale;
    float m_scaleRange;

    float m_width;
    float m_widthRange;

    float m_height;
    float m_heightRange;

    float m_xscale;
    float m_yscale;

    float m_jitter;

    // The actual tiles
    ItemArray m_tiles;
    //std::vector<item> m_tiles;
    // or
    std::map<int,std::vector<item> > m_accelTiles;

    void* image;// TODO: ch: need to define how images are referenced
                // Using something like oiio would be nice since it handles caching
                // and image formats
};

#endif // TILE_H
