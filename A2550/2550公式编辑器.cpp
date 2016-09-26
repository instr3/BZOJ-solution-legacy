#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;
#define rep(i,n) for(int i=1;i<=(n);++i)
#define rep2(i,a,b) for(int i=(a);i<=(b);++i)
char buffer[1001][1001];
enum Direction
{
	UP = 1,
	DOWN = 2,
	LEFT = 3,
	RIGHT = 4
};
class Drawable
{
protected:
	int width, height;
	int centerX;
	Drawable *parent;
public:
	Drawable(Drawable *par = 0)
	{
		parent = par;
	}
	virtual ~Drawable(){}
	virtual void calSize() = 0;
	virtual void draw(int ix, int iy) = 0;
	virtual bool moveDir(Direction id) = 0;
	virtual bool leftMost() = 0;
	virtual bool rightMost() = 0;
	virtual bool moveHome() = 0;
	virtual bool moveEnd() = 0;
	virtual bool insert(Drawable *obj) = 0;
	virtual bool addRow() = 0;
	virtual bool addCol() = 0;
	inline int getHeight()
	{
		return height;
	}
	inline int getWidth()
	{
		return width;
	}
	inline int getUpperHeight()
	{
		return centerX - 1;
	}
	inline int getLowerHeight()
	{
		return height - centerX;
	}
	inline Drawable *getParent()
	{
		return parent;
	}
	inline void setParent(Drawable *par)
	{
		parent = par;
	}
};
class Character :public Drawable
{
private:
	char c;
public:
	Character(Drawable *par) :Drawable(par)
	{
		c = 0;
	}
	Character(char ic, Drawable *par) :Drawable(par)
	{
		c = ic;
	}
	virtual ~Character(){}
	virtual void calSize()
	{
		height = 1; centerX = 1;
		width = c == 0 ? 0 : c == '-' ? 3 : 1;
	}
	virtual bool moveDir(Direction id){ return false; }
	virtual bool leftMost(){ return false; }
	virtual bool rightMost(){ return false; }
	virtual bool moveHome(){ return false; }
	virtual bool moveEnd(){ return false; }
	virtual bool insert(Drawable *obj){ return false; }
	virtual bool addRow(){ return false; }
	virtual bool addCol(){ return false; }
	virtual void draw(int ix, int iy)
	{
		if (c == 0)return;
		if (c == '-')
		{
			buffer[ix][iy] = buffer[ix][iy + 2] = ' ';
			buffer[ix][iy + 1] = c;
		}
		else buffer[ix][iy] = c;
	}
};
class Sequence :public Drawable
{
private:
	vector<Drawable*> list;
	int cursor;
	bool cursorInside;
	bool insideCursor(Direction);
	bool outsideCursor(Direction);
public:
	Sequence(Drawable* par) :Drawable(par)
	{
		cursor = 0;
		cursorInside = false;
	}
	virtual ~Sequence()
	{
		rep2(i, 0, (int)list.size() - 1)
		{
			delete list[i];
		}
	}
	virtual void calSize()
	{
		width = 0;
		int upsize = 0, lowsize = 0;
		rep2(i, 0, (int)list.size() - 1)
		{
			list[i]->calSize();
			width += list[i]->getWidth();
			upsize = max(upsize, list[i]->getUpperHeight());
			lowsize = max(lowsize, list[i]->getLowerHeight());
		}
		height = upsize + lowsize + 1;
		centerX = upsize + 1;
	}
	virtual bool moveDir(Direction id)
	{
		return (insideCursor(id) || outsideCursor(id));
	}
	virtual bool leftMost()
	{
		cursor = 0;
		cursorInside = false;
		return true;
	}
	virtual bool rightMost()
	{
		cursor = list.size();
		cursorInside = false;
		return true;
	}
	virtual bool moveHome()
	{
		if (cursorInside)return list[cursor]->moveHome();
		return leftMost();
	}
	virtual bool moveEnd()
	{
		if (cursorInside)return list[cursor]->moveEnd();
		return rightMost();
	}
	virtual bool insert(Drawable *obj)
	{
		if (cursorInside)return list[cursor]->insert(obj);
		list.insert(list.begin() + cursor, obj);
		moveDir(RIGHT);
		obj->setParent(this);
		return true;
	}
	virtual void draw(int ix, int iy)
	{
		int tx = ix + centerX - 1;
		int ty = iy;
		rep2(i, 0, (int)list.size() - 1)
		{
			list[i]->draw(tx - list[i]->getUpperHeight(), ty);
			ty += list[i]->getWidth();
		}
	}
	virtual bool addRow()
	{
		if (cursorInside)return  list[cursor]->addRow();
		return false;
	}
	virtual bool addCol()
	{
		if (cursorInside)return  list[cursor]->addCol();
		return false;
	}
};
class Fraction :public Drawable
{
private:
	Drawable *u, *d;
	bool cursorUp;
public:
	Fraction(Drawable *par) :Drawable(par)
	{
		u = new Sequence(this);
		d = new Sequence(this);
		cursorUp = true;
	}
	virtual ~Fraction()
	{
		delete u;
		delete d;
	}
	virtual void calSize()
	{
		u->calSize();
		d->calSize();
		width = max(u->getWidth(), d->getWidth()) + 2;
		height = u->getHeight() + d->getHeight() + 1;
		centerX = u->getHeight() + 1;
	}
	virtual bool moveDir(Direction id)
	{
		if (cursorUp)
		{
			if (u->moveDir(id))return true;
			if (id == DOWN)
			{
				cursorUp = false;
				return d->leftMost();
			}
		}
		else
		{
			if (d->moveDir(id))return true;
			if (id == UP)
			{
				cursorUp = true;
				return u->leftMost();
			}
		}
		return false;
	}
	virtual bool leftMost()
	{
		cursorUp = true;
		return u->leftMost();
	}
	virtual bool rightMost()
	{
		cursorUp = true;
		return u->rightMost();
	}
	virtual bool moveHome()
	{
		return cursorUp ? u->moveHome() : d->moveHome();
	}
	virtual bool moveEnd()
	{
		return cursorUp ? u->moveEnd() : d->moveEnd();
	}
	virtual bool insert(Drawable *obj)
	{
		return cursorUp ? u->insert(obj) : d->insert(obj);
	}
	virtual void draw(int ix, int iy)
	{
		rep(j, width)
		{
			buffer[ix + centerX - 1][iy + j - 1] = '-';
		}
		u->draw(ix, iy + (width - u->getWidth()) / 2);
		d->draw(ix + centerX, iy + (width - d->getWidth()) / 2);
	}
	virtual bool addRow()
	{
		return cursorUp ? u->addRow() : d->addRow();
	}
	virtual bool addCol()
	{
		return cursorUp ? u->addCol() : d->addCol();
	}
};
class Matrix :public Drawable
{
private:
	vector< vector<Drawable *> >grid;
	int nx, ny;
	vector<int> upSize, downSize, colSize;
	int cursorX, cursorY;
public:
	Matrix(Drawable *par) :Drawable(par)
	{
		vector<Drawable*> tmp;
		tmp.push_back(new Sequence(this));
		grid.push_back(tmp);
		nx = ny = 1;
	}
	virtual ~Matrix()
	{
		rep2(i, 0, nx-1)
		{
			rep2(j, 0, ny-1)
			{
				delete grid[i][j];
			}
		}
	}
	virtual void calSize()
	{
		upSize.clear();
		downSize.clear();
		colSize.clear();
		upSize.resize(nx);
		downSize.resize(nx);
		colSize.resize(ny);
		height = nx - 1; width = ny + 1;
		rep2(i, 0, nx - 1)
		{
			rep2(j, 0, ny - 1)
			{
				grid[i][j]->calSize();
				upSize[i] = max(upSize[i], grid[i][j]->getUpperHeight());
				downSize[i] = max(downSize[i], grid[i][j]->getLowerHeight());
				colSize[j] = max(colSize[j], grid[i][j]->getWidth());
			}
		}
		rep2(i, 0, nx - 1)height += upSize[i] + downSize[i] + 1;
		rep2(j, 0, ny - 1)width += colSize[j];
		if (nx % 2)
		{
			centerX = nx / 2 + 1 + upSize[nx / 2];
			rep2(i, 0, nx / 2 - 1)
			{
				centerX += upSize[i] + downSize[i] + 1;
			}
		}
		else
		{
			centerX = nx / 2;
			rep2(i, 0, nx / 2 - 1)
			{
				centerX += upSize[i] + downSize[i] + 1;
			}
		}
	}
	virtual bool moveDir(Direction id)
	{
		if (grid[cursorX][cursorY]->moveDir(id))return true;
		if (id == UP)
		{
			if (cursorX > 0)return grid[--cursorX][cursorY]->leftMost();
		}
		else if (id == DOWN)
		{
			if (cursorX < nx - 1)return grid[++cursorX][cursorY]->leftMost();
		}
		else if (id == LEFT)
		{
			if (cursorY > 0)return grid[cursorX][--cursorY]->rightMost();
		}
		else if (id == RIGHT)
		{
			if (cursorY < ny - 1)return grid[cursorX][++cursorY]->leftMost();
		}
		return false;
	}
	virtual bool leftMost()
	{
		return grid[cursorX = (nx - 1) / 2][cursorY = 0]->leftMost();
	}
	virtual bool rightMost()
	{
		return grid[cursorX = (nx - 1) / 2][cursorY = ny - 1]->rightMost();
	}
	virtual bool moveHome()
	{
		return grid[cursorX][cursorY]->moveHome();
	}
	virtual bool moveEnd()
	{
		return grid[cursorX][cursorY]->moveEnd();
	}
	virtual bool insert(Drawable *obj)
	{
		return grid[cursorX][cursorY]->insert(obj);
	}
	virtual void draw(int ix, int iy)
	{
		int tx = ix;
		rep2(i, 0, nx - 1)
		{
			tx += upSize[i];
			int ty = iy + 1;
			buffer[tx][ty - 1] = '[';
			rep2(j, 0, ny - 1)
			{
				grid[i][j]->draw(tx - grid[i][j]->getUpperHeight(), ty + (colSize[j] - grid[i][j]->getWidth()) / 2);
				ty += colSize[j] + 1;
			}
			buffer[tx][ty - 1] = ']';
			tx += downSize[i] + 2;
		}
	}
	virtual bool addCol()
	{
		if (grid[cursorX][cursorY]->addCol())return true;
		++ny;
		rep2(i, 0, nx - 1)
		{
			grid[i].insert(grid[i].begin() + cursorY, new Sequence(this));
		}
		return true;
	}
	virtual bool addRow()
	{
		if (grid[cursorX][cursorY]->addRow())return true;
		++nx;
		vector<Drawable*> tmp;
		rep2(j, 0, ny - 1)
		{
			tmp.push_back(new Sequence(this));
		}
		grid.insert(grid.begin() + cursorX, tmp);
		return true;
	}
};
bool Sequence::insideCursor(Direction id)
{
	if (cursorInside)
	{
		if (list[cursor]->moveDir(id))return true;
		if (id == LEFT)
		{
			cursorInside = false;
			return true;
		}
		else if (id == RIGHT)
		{
			cursorInside = false;
			++cursor;
			return true;
		}
	}
	return false;
}
bool Sequence::outsideCursor(Direction id)
{
	if (!cursorInside)
	{
		if (id == LEFT&&cursor>0)
		{
			if (list[cursor - 1]->rightMost())
			{
				--cursor;
				cursorInside = true;
			}
			else
			{
				--cursor;
			}
			return true;
		}
		else if (id == RIGHT&&cursor<(int)list.size())
		{
			if (list[cursor]->leftMost())
			{
				cursorInside = true;
			}
			else
			{
				++cursor;
			}
			return true;
		}
	}
	return false;
}
class Scanner
{
private:
	Sequence root;
public:
	Scanner() :root(0)
	{

	}
	void init()
	{
		memset(buffer, ' ', sizeof buffer);
	}
	bool scan()
	{
		char input[10];
		if (!(cin >> input))return false;
		if (strcmp(input, "Fraction") == 0)
			root.insert(new Fraction(0));
		else if (strcmp(input, "Matrix") == 0)
			root.insert(new Matrix(0));
		else if (strcmp(input, "AddRow") == 0)
			root.addRow();
		else if (strcmp(input, "AddCol") == 0)
			root.addCol();
		else if (strcmp(input, "Right") == 0)
			root.moveDir(RIGHT);
		else if (strcmp(input, "Left") == 0)
			root.moveDir(LEFT);
		else if (strcmp(input, "Up") == 0)
			root.moveDir(UP);
		else if (strcmp(input, "Down") == 0)
			root.moveDir(DOWN);
		else if (strcmp(input, "Home") == 0)
			root.moveHome();
		else if (strcmp(input, "End") == 0)
			root.moveEnd();
		else
			root.insert(new Character(input[0], 0));

		return true;
	}
	void print()
	{
		root.calSize();
		root.draw(0, 0);
		int nx = root.getHeight(), ny = root.getWidth();
		int ty;
		rep2(ix, 0, nx - 1)
		{
			for (ty = ny; ty >= 0; --ty)if (buffer[ix][ty] != ' ')break;
			rep2(iy, 0, ty)putchar(buffer[ix][iy]);
			putchar('\n');
		}
	}
}scanner;

int main()
{
	scanner.init();
	while (scanner.scan());
	scanner.print();
	return 0;
}


