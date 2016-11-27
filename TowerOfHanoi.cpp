#include <iostream>
#include <vector>

class Tower
{
public:
    void Push(int disk)
    {
        if (!m_disks.empty() && m_disks.back() <= disk)
            throw 1;
        m_disks.push_back(disk);
    }

    int Pop()
    {
        auto disk = m_disks.back();
        m_disks.pop_back();
        return disk;
    }

    const auto& Disks() const
    {
        return m_disks;
    }

private:
    std::vector<int> m_disks;
};

class Game
{
public:
    Game(int size) : m_size(size)
    {
        for (auto i = size; i--; )
            m_original.Push(i);
    }

    void Solve()
    {
        MoveDisks(m_size, m_original, m_destination, m_middle);
    }

    void Print()
    {
        for (auto row = m_size; row--; )
        {
            PrintDisk(m_original, row);
            PrintDisk(m_middle, row);
            PrintDisk(m_destination, row);
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

private:
    void PrintDisk(const Tower& tower, int row)
    {
        auto disk = row < tower.Disks().size() ? tower.Disks()[row] : 0;
        auto space = m_size - disk;

        for (auto i = space; i--; ) std::cout << " ";
        for (auto i = disk;  i--; ) std::cout << "=";

        std::cout << "|";

        for (auto i = disk;  i--; ) std::cout << "=";
        for (auto i = space; i--; ) std::cout << " ";

        std::cout << "   ";
    }

    void MoveDisks(int count, Tower& from, Tower& to, Tower& buffer)
    {
        if (count > 0)
        {
            MoveDisks(count - 1, from, buffer, to);

            to.Push(from.Pop());
            Print();

            MoveDisks(count - 1, buffer, to, from);
        }
    }

    Tower m_original;
    Tower m_middle;
    Tower m_destination;
    int m_size;
};

int main()
{
    Game game(15);
    game.Print();
    game.Solve();

    return 0;
}
