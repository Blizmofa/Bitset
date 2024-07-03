#include <iostream>
#include <bitset>
#include <vector>

struct sBitmask
{
    std::bitset<64> mask;

    void setBit(int position)
    {
        if (position >= 0 && position < 64)
        {
            mask.set(position);
        }
    }

    // Method to clear a bit at a specific position
    void clearBit(int position)
    {
        if (position >= 0 && position < 64)
        {
            mask.reset(position);
        }
    }

    // Method to toggle a bit at a specific position
    void toggleBit(int position)
    {
        if (position >= 0 && position < 64)
        {
            mask.flip(position);
        }
    }

    // Method to check if a bit at a specific position is set
    bool isBitSet(int position) const
    {
        if (position >= 0 && position < 64)
        {
            return mask.test(position);
        }
        return false;
    }

    // Method to print the bitmask as a binary string
    void print() const
    {
        std::cout << mask.to_string() << '\n';
    }

    // Method to flip bits in place starting from a specific position for a given count
    sBitmask &flipBits(int start, int count)
    {
        for (int i = start; i < start + count; ++i)
        {
            if (i >= 0 && i < 64)
            {
                mask.flip(i);
            }
        }
        return *this;
    }

    // Method to set bits from another bitmask
    void setBitsFrom(const sBitmask &other, int start, int count, int targetStart)
    {
        for (int i = 0; i < count; ++i)
        {
            if (start + i < 64 && targetStart + i < 64)
            {
                mask[targetStart + i] = other.mask[start + i];
            }
        }
    }

    // Method to aggregate bits from two BitMask64 objects
    sBitmask &aggregateBits(const sBitmask &bm1, const sBitmask &bm2)
    {
        for (int i = 0; i < 64; ++i)
        {
            if (bm1.mask.test(i))
            {
                mask.set(i);
            }
            if (bm2.mask.test(i))
            {
                mask.set(i);
            }
        }
        return *this;
    }

    // Method to aggregate bits from multiple BitMask64 objects
    sBitmask &aggregateVectorBits(const std::vector<sBitmask> &bitmasks)
    {
        for (const auto &bm : bitmasks)
        {
            for (int i = 0; i < 64; ++i)
            {
                if (bm.mask.test(i))
                {
                    mask.set(i);
                }
            }
        }
        return *this;
    }
};

int main()
{

    sBitmask A;
    sBitmask B;
    sBitmask rule;

    std::vector<sBitmask>
        vec1 = {A, B};
    std::vector<sBitmask> vec2 = {A, B};

    std::cout << "Vector1 A bitmask before:\n";
    vec1[0].print();

    vec1[0].flipBits(0, 3);
    std::cout << "Vector1 A bitmask after:\n";
    vec1[0].print();

    std::cout << "Vector1 B bitmask before:\n";
    vec1[1].print();
    vec1[1].flipBits(3, 3);
    std::cout << "Vector1 B bitmask after:\n";
    vec1[1].print();

    std::cout << "Vector2 A bitmask before:\n";
    vec2[0].print();
    vec2[0].flipBits(61, 3);
    std::cout << "Vector2 A bitmask after:\n";
    vec2[0].print();

    std::cout << "Vector2 B bitmask before:\n";
    vec2[1].print();
    vec2[1].flipBits(58, 3);
    std::cout << "Vector2 B bitmask after:\n";
    vec2[0].print();

    std::cout << "Aggregated Rule bitmask before:\n";
    rule.print();
    std::cout << "Aggregated Rule bitmask after:\n";
    rule.aggregateVectorBits(vec1);
    rule.aggregateVectorBits(vec2);
    rule.print();

    return 0;
}