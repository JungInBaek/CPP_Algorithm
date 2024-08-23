#include "pch.h"
#include "Board.h"
#include "Player.h"
#include "DisjointSet.h"


const char* TILE = "■";

Board::Board()
{
    
}

Board::~Board()
{
}

void Board::Init(int32 size, Player* player)
{
    _size = size;
    _player = player;

    //GenerateMap_Kruskal();
    GenerateMap_Prim();
}

void Board::Render()
{
    ConsoleHelper::SetCursorPosition(0, 0);
    ConsoleHelper::ShowConsoleCursor(false);

    for (int32 y = 0; y < 25; y++)
    {
        for (int32 x = 0; x < 25; x++)
        {
            ConsoleColor color = GetTileColor(Pos{ x, y });
            ConsoleHelper::SetCursorColor(color);
            cout << TILE;
        }
        cout << endl;
    }
}

// Binary Tree �̷� ���� �˰����
// - Mazes For Programmers
void Board::GenerateMap_Kruskal()
{
    struct CostEdge
    {
        int cost;
        Pos u;
        Pos v;

        bool operator<(CostEdge& other)
        {
            return cost < other.cost;
        }
    };

    for (int32 y = 0; y < _size; y++)
    {
        for (int32 x = 0; x < _size; x++)
        {
            if (x % 2 == 0 || y % 2 == 0)
            {
                _tile[y][x] = TileType::WALL;
            }
            else
            {
                _tile[y][x] = TileType::EMPTY;
            }
        }
    }

    // Kruskal �˰������ ���� �� ����
    vector<CostEdge> edges;

    for (int32 y = 0; y < _size; y++)
    {
        for (int32 x = 0; x < _size; x++)
        {
            if (x % 2 == 0 || y % 2 == 0)
            {
                continue;
            }

            if (x < _size - 2)
            {
                const int32 randValue = ::rand() % 100;
                edges.push_back(CostEdge{ randValue, Pos{x, y}, Pos{x + 2, y} });
            }

            if (y < _size - 2)
            {
                const int32 randValue = ::rand() % 100;
                edges.push_back(CostEdge{ randValue, Pos{x, y}, Pos{x, y + 2 } });
            }
        }
    }

    ::sort(edges.begin(), edges.end());

    DisjointSet sets(_size * _size);

    for (CostEdge& edge : edges)
    {
        int32 u = edge.u.y * _size + edge.u.x;
        int32 v = edge.v.y * _size + edge.v.x;

        if (sets.Find(u) == sets.Find(v))
        {
            continue;
        }

        sets.Merge(u, v);

        int32 x = (edge.u.x + edge.v.x) / 2;
        int32 y = (edge.u.y + edge.v.y) / 2;
        _tile[y][x] = TileType::EMPTY;
    }
}

void Board::GenerateMap_Prim()
{
    struct CostEdge
    {
        int cost;
        Pos vtx;

        bool operator<(const CostEdge& other) const
        {
            return cost < other.cost;
        }
    };

    for (int32 y = 0; y < _size; y++)
    {
        for (int32 x = 0; x < _size; x++)
        {
            if (x % 2 == 0 || y % 2 == 0)
            {
                _tile[y][x] = TileType::WALL;
            }
            else
            {
                _tile[y][x] = TileType::EMPTY;
            }
        }
    }

    // Prim �˰������ ���� �� ����
    map<Pos, vector<CostEdge>> edges;

    for (int y = 0; y < _size; y++)
    {
        for (int x = 0; x < _size; x++)
        {
            if (x % 2 == 0 || y % 2 == 0)
            {
                continue;
            }

            if (x < _size - 2)
            {
                const int32 randValue = ::rand() % 100;
                Pos u = Pos{ x, y };
                Pos v = Pos{ x + 2, y };
                edges[u].push_back(CostEdge{ randValue, v });
                edges[v].push_back(CostEdge{ randValue, u });
            }

            if (y < _size - 2)
            {
                const int32 randValue = ::rand() % 100;
                Pos u = Pos{ x, y };
                Pos v = Pos{ x, y + 2 };
                edges[u].push_back(CostEdge{ randValue, v });
                edges[v].push_back(CostEdge{ randValue, u });
            }
        }
    }

    map<Pos, bool> added;
    map<Pos, int32> best;
    map<Pos, Pos> parent;

    for (int y = 0; y < _size; y++)
    {
        for (int x = 0; x < _size; x++)
        {
            added[Pos{ x, y }] = false;
            best[Pos{ x, y }] = INT32_MAX;
        }
    }

    priority_queue<CostEdge> pq;

    const Pos startPos = { 1, 1 };
    best[startPos] = 0;
    parent[startPos] = startPos;
    pq.push(CostEdge{ 0, startPos });

    while (pq.empty() == false)
    {
        CostEdge bestEdge = pq.top();
        pq.pop();

        Pos v = bestEdge.vtx;
        if (added[v])
        {
            continue;
        }

        added[v] = true;

        {
            int32 x = (v.x + parent[v].x) / 2;
            int32 y = (v.y + parent[v].y) / 2;
            _tile[y][x] = TileType::EMPTY;
        }

        for (CostEdge& edge : edges[v])
        {
            if (added[edge.vtx])
            {
                continue;
            }

            if (edge.cost > best[edge.vtx])
            {
                continue;
            }

            best[edge.vtx] = edge.cost;
            parent[edge.vtx] = v;
            pq.push(edge);
        }
    }
}

TileType Board::GetTileType(Pos pos)
{
    if (pos.x < 0 || pos.x >= _size)
    {
        return TileType::NONE;
    }
    if (pos.y < 0 || pos.y >= _size)
    {
        return TileType::NONE;
    }
    return _tile[pos.y][pos.x];
}

ConsoleColor Board::GetTileColor(Pos pos)
{
    if (_player && _player->GetPos() == pos)
    {
        return ConsoleColor::YELLOW;
    }

    if (GetExitPos() == pos)
    {
        return ConsoleColor::BLUE;
    }

    TileType tileType = GetTileType(pos);

    switch (tileType)
    {
    case TileType::EMPTY:
        return ConsoleColor::GREEN;
    case TileType::WALL:
        return ConsoleColor::RED;
    }

    return ConsoleColor::WHITE;
}