#pragma once

template<typename T>
class CORE_DLL Size
{
public:
    T Width;
    T Height;

public:
    Size()
    {
        Width  = T(0);
        Height = T(0);
    }

    Size(T width, T height)
    {
        Width  = width;
        Height = height;
    }

    Size(const Size& other)
    {
        Width  = other.Width;
        Height = other.Height;
    }

public:
    void Set(T width, T height)
    {
        Width  = width;
        Height = height;
    }

    void Empty()
    {
        Width  = T(0);
        Height = T(0);
    }

    bool IsEmpty() const
    {
        return (Width == T(0) && Height == T(0));
    }

    Size& operator = (const Size& other)
    {
        Width  = other.Width;
        Height = other.Height;
        return *this;
    }

    bool operator == (const Size& other) const
    {
        return (Width == other.Width && Height == other.Height);
    }

    bool operator != (const Size& other) const
    {
        return (Width != other.Width || Height != other.Height);
    }
};
